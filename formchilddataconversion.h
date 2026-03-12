#ifndef FORMCHILDDATACONVERSION_H
#define FORMCHILDDATACONVERSION_H

/* 功能介绍：
 * 1、进制转换
 * 2、异步处理
 * 3、输入防抖
 * 4、日志记录
 * 5、统计信息
 */

#include <QWidget>

#include <QCloseEvent>
#include <QtConcurrent>
#include <QMessageBox>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QClipboard>
#include <QTimer>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QQueue>

#include "dataconverter.h"

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class FormChildDataConversion;
}

class FormChildDataConversion : public QWidget
{
    Q_OBJECT

public:
    explicit FormChildDataConversion(QWidget *parent = nullptr);
    ~FormChildDataConversion();

    // 保存日志（公共接口，提供主窗口调用）
    void saveLog();

private slots:


    void on_pushButton_converOperator_clicked();

    void on_pushButton_clearOperator_clicked();

    void on_pushButton_swapOperator_clicked();

    void on_pushButton_copyOperator_clicked();

    // 异步转换完成槽函数
    void onConversionFinished();

    // 输入文本变换槽函数
    void onInputTextChanged();

private:
    Ui::FormChildDataConversion *ui;

    // 转换运行状态标志
    bool conversionRunning = false;

    // 输入更新防抖定时器
    QTimer* inputUpdateTime;

    // 日志条目队列
    QQueue<QString> logEntries;

    // 统一消息提示函数
    void showMessage(const QString& message, bool isError = false);

    // 异步转换监视器
    QFutureWatcher<DataConverter::ConversionResult> conversionWatcher;

    // 设置转换忙状态
    void setConversionBusy(bool busy);

    // 展示转换结果或错误信息
    void showResult(const DataConverter::ConversionResult& result, QTextEdit* outputEdit);

    // 更新输入统计信息
    void updateInputInfo(const QString& text);

    // 更新输出统计信息
    void updateOutputInfo(const QString& text);

    // 复制文本到剪切板
    void copyToClipboard(const QString& text);

    // 连接所有信号和槽
    void connectSignals();

    // 追加日志条目
    void appendLog(const QString& message);

    // 裁剪日志队列
    void trimLog();

    // 保存纯文本编辑框内容到文件
    void savePlainTextEditToFile(QPlainTextEdit* plainTextEdit);

protected:
    // 窗口关闭事件
    void closeEvent(QCloseEvent* event) override;

};

#endif // FORMCHILDDATACONVERSION_H
