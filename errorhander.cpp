#include "errorhander.h"

#include <QStandardPaths>   // 获取平台通用的可写目录
#include <QDir>             // 目录操作（创建路径等）
#include <QApplication>     // 退出应用，应用信息

ErrorHandler::ErrorHandler(QObject *parent)
    : QObject{parent}
{}

ErrorHandler::~ErrorHandler()
{
    if(logStream) {
        delete logStream;   // 先删除流，在关闭文件
    }
    if(logFile) {
        logFile->close();   // 确保落盘
        delete logFile;
    }
}

// 功能：获取全局单例，首次调用时创建并初始化日志
ErrorHandler& ErrorHandler::instance()
{
    static ErrorHandler instance;
    return instance;
}

// 功能：弹出消息框并记录日志
void ErrorHandler::handleError(ErrorType type, ErrorLevel level, const QString& message, QWidget* parent)
{
    // 先写日志，context 取自错误类型
    QString context = errorTypeToString(type);
    logError(context, message, level);

    // 根据日志界别弹出消息框
    QMessageBox::Icon icon;
    QString title;

    switch (level) { // 映射级别到UI图标与标题
#define XX(item, description, image) \
    case item: \
            icon = image; \
            title = QString(description); \
            break;

        XX(Info,     "信息",     QMessageBox::Information);
        XX(Warning,  "警告",     QMessageBox::Warning);
        XX(Critical, "错误",     QMessageBox::Critical);
        XX(Fatal,    "严重错误", QMessageBox::Critical);

#undef XX

    default:
        icon = QMessageBox::NoIcon; // 给默认值，避免未初始化
        title = "未知级别";
        break;
    }

    // 以父窗口作为归属，避免顶层无父导致窗口乱序
    QMessageBox msgBox(parent);
    msgBox.setIcon(icon);   // 设置图标
    msgBox.setWindowTitle(title); // 设置标题
    msgBox.setText(message);    // 主要文本
    msgBox.setStandardButtons(QMessageBox::Ok); // 仅确认按钮
    msgBox.exec();

    // Fatal 级别：记录后直接请示退出应用
    if(level == Fatal) {
        QApplication::quit();
    }
}

// 功能：仅记录日志（不弹窗），包含时间/级别/来源
void ErrorHandler::logError(const QString& context, const QString& error, ErrorLevel level)
{
    // 日志关闭或流未初始化时直接返回
    if(!loggingEnabled || !logStream) {
        return;
    }

    QMutexLocker locker(&logMutex);     // 保护日志写入的互斥
    rolloverIfNeeded_unlocked();        // 按大小判断是否滚动
    reopenForToday_unlocked();          // 按日期判断是否切换

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 当前时间
    QString levelStr = errorLevelToString(level);   // 级别文本

    // 统一日志格式：[时间][级别][来源] 内容
    QString logMessage = QStringLiteral("[%1][%2][%3] %4").arg(timestamp, levelStr, context, error);

    writeToLog(logMessage); // 持锁写入
}

// 功能：设置/切换日志文件路径（追加），后续按日期/大小自动流动
void ErrorHandler::setLogFile(const QString& filename)
{
    //
    QMutexLocker locker(&logMutex); // 切换文件也需要互斥保护

    // 若已有流/文件，先释放
    if(logStream) {
        delete logStream;
        logStream = nullptr;
    }
    if(logFile) {
        logFile->close();
        delete logFile;
        logFile = nullptr;
    }

    // 尝试打开新的日志文件
    logFile = new QFile(filename);
    if(logFile->open(QIODevice::WriteOnly | QIODevice::Append)) {
        logStream = new QTextStream(logFile); // 绑定文件流
        currentLogPath = filename;  // 记录当前路径
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
        logStream->setCodec("UTF-8");   // Qt5 设置编码
#else
        logStream->setEncoding(QStringConverter::Utf8);  // Qt6 设置编码
#endif
    }else {
        delete logFile;
        logFile = nullptr;
        qWarning() << "无法打开日志文件: " << filename;
    }
}

// 功能：在持锁状态下写入日志行并刷新
void ErrorHandler::writeToLog(const QString& message)
{
    if(logStream) { // 仅在流可用是写入
        *logStream << message << Qt::endl;  // Qt::endl 刷新缓冲区
        logStream->flush(); // 在显式刷新，确保立即落盘
    }
}

// 功能：错误来源枚举转换字符串
QString ErrorHandler::errorTypeToString(ErrorType type)
{
    switch (type) {
#define XX(item, val) \
    case item: \
        return val; \
        break;

    XX(NetworkError, "网络错误");
    XX(ValidationError, "验证错误");
    XX(FileError, "文件错误");
    XX(ConfigError, "配置错误");
#undef XX
    default:
        return "未知错误";  // 兜底操作，避免空字符串
        break;
    }
}

// 功能：错误级别枚举转换字符串
QString ErrorHandler::errorLevelToString(ErrorLevel level)
{
    switch (level) {
#define XX(item, val) \
    case item: \
            return val; \
            break;

        XX(Info, "信息");
        XX(Warning, "警告");
        XX(Critical, "错误");
        XX(Fatal, "致命");
#undef XX
    default:
        return "未知级别";  // 兜底操作，避免空字符串
        break;
    }
}

// 功能：按大小滚动日志文件
void ErrorHandler::rolloverIfNeeded_unlocked(qint64 maxBytes)
{
    if(currentLogPath.isEmpty() || !logFile) return; // 未初始化则跳过
    QFileInfo info(*logFile); // 查询当前大小
    if(info.size() < maxBytes) return;  // 为超过阈值则不滚动

    // 生成带时间戳的滚动文件名
    QString timeSuffix = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString rolled = currentLogPath;
    rolled.replace(".log", QString("_%1.log").arg(timeSuffix));

    logStream->flush(); // 刷新缓冲
    logFile->close();   // 关闭当前文件
    QFile::rename(currentLogPath, rolled); // 重命名为历史文件

    // 释放久指针
    delete logStream;
    delete logFile;
    logStream = nullptr;
    logFile = nullptr;

    setLogFile(currentLogPath); // 重新创建一个同名新文件
}

// 功能：按日期切换日志（需要先持锁）
void ErrorHandler::reopenForToday_unlocked()
{
    if(currentLogPath.isEmpty()) return; // 未初始化则跳过
    QString today = QDate::currentDate().toString("yyyyMMdd"); // 今日日期
    if(currentLogPath.contains(today)) return; // 已时今日文件则不切换

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath); // 确保目录存在
    QString newPath = QStringLiteral("%1NDATools_%2.log").arg(appDataPath, today); // 新日期文件

    logStream->flush(); // 刷新当前文件
    logFile->close();   // 关闭当前文件

    // 释放久指针
    delete logStream;
    delete logFile;
    logStream = nullptr;
    logFile = nullptr;

    setLogFile(newPath); // 打开新文件
}

// 功能：开启/关闭日志落盘
void ErrorHandler::setLosggingEnabled(bool enabled)
{
    loggingEnabled = enabled;
}

// 功能：初始化，切换当前日志，创建目录与文件
void ErrorHandler::initializeLogFile()
{
    // 日志目录：平台
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath);

    // 日志文件名：按日期分片，比如:NDATools_20260101.log
    QString logFileName = QStringLiteral("%1/NADTools_%2.log").arg(appDataPath, QDate::currentDate().toString("yyyyMMdd"));

    setLogFile(logFileName);    // 打开/切换日志文件

    // 写入启动标记，便于分割进程启动
    if(logStream) {
        writeToLog("===NDATools 启动 ===");
    }
}

























