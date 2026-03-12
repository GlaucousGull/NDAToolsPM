#include "formchilddatavalidation.h"
#include "ui_formchilddatavalidation.h"

// 最大校验值计算长度
static const int kMaxCheckLength = 200000;

// 异步校验值计算阈值 （40000字符，超过此值使用异步计算
static const int kAsyncCheckSumThreshold = 40000;

FormChildDataValidation::FormChildDataValidation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormChildDataValidation)
{
    ui->setupUi(this);

    // 连接所有信号和槽
    connectSignals();

    ui->textEdit_inputText->setPlaceholderText("请输入要计算校验值的数据...");

    // 连接异步计算监控器的完成信号到槽函数
    connect(&checkSumWatcher, &QFutureWatcher<DataConverter::CheckSumResult>::finished,
            this, &FormChildDataValidation::onCheckSumFinished);

    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据校验] 数据校验工具启动")
                         .arg(timestamp);
    appendLog(logMsg);
}

FormChildDataValidation::~FormChildDataValidation()
{
    delete ui;
}

void FormChildDataValidation::on_pushButton_calculateCheckSums_clicked()
{
    if(!ui || !ui->pushButton_copyCheckSums || !ui->pushButton_calculateCheckSums
        ||!ui->lineEdit_crc16 || !ui->lineEdit_crc32 || !ui->lineEdit_md5
        || !ui->lineEdit_sha1 || !ui->lineEdit_sha256) {
        qWarning() << "FormChildDataValidation::on_pushButton_calculateCheckSums_clicked：UI or controls is null";
        return;
    }

    // 防重复点击：如果正在计算，直接返回，避免重复计算
    if(checkSumRunning) {
        return;
    }

    // 获取输入框中的数据
    QString input = ui->textEdit_inputText->toPlainText();

    if(input.isEmpty()) {
        showMessage(QStringLiteral("请输入要计算的校验值数据"), true);
        return;
    }

    if(input.length() > kMaxCheckLength) {
        showMessage(QStringLiteral("输入超过限制（大于 %1 字符)，请分批计算").arg(kMaxCheckLength), true);
        return;
    }

    // 判断是否使用异步计算模式
    if(input.length() > kAsyncCheckSumThreshold) {
        // 设置忙碌状态，禁用相关按钮，防止重复点击
        setCheckSumBusy(true);
        // 记录异步校验完成日志
        // 记录复制操作日志
        QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
        QString logMsg = QStringLiteral("[%1] [数据校验] 开始计算校验值，输入长度：%2 字符，使用异步计算")
                             .arg(timestamp)
                             .arg(input.length());
        appendLog(logMsg);

        auto future = QtConcurrent::run([input]() {
            return DataConverter::calculateCheckSums(input);
        });

        // 设置监控的异步任务
        checkSumWatcher.setFuture(future);

        return;
    }

    // 同步转换方式：数据量 < 40000 字符
    // 直接调用校验方法，立即获取结果
    DataConverter::CheckSumResult result = DataConverter::calculateCheckSums(input);

    // 根据大小写设置格式化并显示所有校验值结果
    // 如果选中大写，直接使用结果(DataConverter 返回的是大写）
    // 如果为选中大写，转换为小写显示
    bool isUpperCase = ui->checkBox_upperCaseCheck->isChecked();
    if(isUpperCase) {
        ui->lineEdit_crc16->setText(result.crc16);
        ui->lineEdit_crc32->setText(result.crc32);
        ui->lineEdit_md5->setText(result.md5);
        ui->lineEdit_sha1->setText(result.sha1);
        ui->lineEdit_sha256->setText(result.sha256);
    }else {
        ui->lineEdit_crc16->setText(result.crc16.toLower());
        ui->lineEdit_crc32->setText(result.crc32.toLower());
        ui->lineEdit_md5->setText(result.md5.toLower());
        ui->lineEdit_sha1->setText(result.sha1.toLower());
        ui->lineEdit_sha256->setText(result.sha256.toLower());
    }

    // 记录校验操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据校验] 开始计算校验值，输入长度：%2 字符，使用异步计算")
                         .arg(timestamp)
                         .arg(input.length());
    appendLog(logMsg);
}


void FormChildDataValidation::on_pushButton_copyCheckSums_clicked()
{

}

// 保存日志（公共接口，提供主窗口调用）
void FormChildDataValidation::saveLog()
{
    // ===== 1. 前置校验：日志为空直接返回（核心逻辑修复）=====
    if(logEntries.isEmpty()) {
        qDebug() << "FormChildDataConversion::saveLog：日志条目为空，无需保存";
        return;
    }

    // ===== 2. 构建日志文件路径（确保目录存在）=====
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if(!QDir().mkpath(appDataPath)) {
        qWarning() << "FormChildDataConversion::saveLog：无法创建目录" << appDataPath;
        if(this->isVisible()) {
            QMessageBox::critical(this, QStringLiteral("错误"),
                                  QStringLiteral("无法创建日志目录：%1").arg(appDataPath));
        }
        return;
    }

    // 构建文件路径（简化写法，避免冗余）
    QString fileName = QDir(appDataPath).filePath(QStringLiteral("DataConversionLogFile.txt"));

    // ===== 3. 确定文件打开模式 =====
    bool fileExists = QFile::exists(fileName);
    QIODevice::OpenMode openMode = QIODevice::Text; // 基础模式：文本模式
    if(fileExists) {
        openMode |= QIODevice::Append; // 追加模式
    } else {
        openMode |= QIODevice::WriteOnly; // 新建模式
    }

    // ===== 4. 打开文件并写入日志（核心逻辑）=====
    QFile file(fileName);
    if(!file.open(openMode)) { // 打开失败：错误处理
        QString errorMsg = QStringLiteral("无法打开日志文件：%1（%2）").arg(fileName, file.errorString());
        qWarning() << "FormChildDataConversion::saveLog：" << errorMsg;
        if(this->isVisible()) {
            QMessageBox::critical(this, QStringLiteral("错误"), errorMsg);
        }
        return;
    }

    // 打开成功：写入日志
    QTextStream out(&file);
    // 设置UTF-8编码（兼容Qt5/Qt6）
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#else
    out.setEncoding(QStringConverter::Utf8);
#endif

    // 追加模式：写入分隔符+时间戳
    if(fileExists) {
        QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
        out << "\n" << QStringLiteral("==========") << timestamp << QStringLiteral("==========");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        out << endl;
#else
        out << Qt::endl;
#endif
    }

    // 批量写入所有日志条目（性能优化）
    for(const QString& entry : logEntries) {
        out << entry;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        out << endl;
#else
        out << Qt::endl;
#endif
    }

    // ===== 5. 收尾处理（成功逻辑）=====
    file.close(); // 显式关闭（可选，RAII会自动处理）
    QString successMsg = QStringLiteral("日志保存至：%1").arg(fileName);
    qDebug() << "数据校验工具日志已保存至：" << fileName;

    // 清空日志条目
    logEntries.clear();

    // 仅窗口可见时弹窗提示
    if(this->isVisible()) {
        QMessageBox::information(this, QStringLiteral("成功"), successMsg);
    }
}

// 连接信号槽
void FormChildDataValidation::connectSignals()
{
    if(!ui || !ui->pushButton_copyCheckSums || !ui->pushButton_calculateCheckSums
        || !ui->lineEdit_crc16 || !ui->lineEdit_crc32 || !ui->lineEdit_md5
        || !ui->lineEdit_sha1 || !ui->lineEdit_sha256) {
        qWarning() << "FormChildDataValidation::connectSignals：UI or controls is null";
        return;
    }

    // 连接复制按钮的点击信号到lambda表达式
    connect(ui->pushButton_copyCheckSums, &QPushButton::clicked, [this]() {
        if(!ui || !ui->pushButton_copyCheckSums || !ui->pushButton_calculateCheckSums
            ||!ui->lineEdit_crc16 || !ui->lineEdit_crc32 || !ui->lineEdit_md5
            || !ui->lineEdit_sha1 || !ui->lineEdit_sha256) {
            qWarning() << "FormChildDataValidation::connectSignals：UI or controls is null";
            return;
        }

        // 将所有校验值格式化为多行文本，便于复制和查看
        QString allHahses = QStringLiteral("CRC16: %1\nRCR32: %2\nMD5:$3\nSHA1: %4\nSAH256: %5")
                                .arg(ui->lineEdit_crc16->text())
                                .arg(ui->lineEdit_crc32->text())
                                .arg(ui->lineEdit_md5->text())
                                .arg(ui->lineEdit_sha1->text())
                                .arg(ui->lineEdit_sha256->text());

        // 调用复制函数，将格式化后的文本复制到剪切板
        copyToClipboard(allHahses);
    });

    // 连接大小写复选框的状态变化信号到槽函数
    connect(ui->checkBox_upperCaseCheck, &QCheckBox::toggled, this, &FormChildDataValidation::onUpperCaseToggled);
}

// 复制文本到剪切板
void FormChildDataValidation::copyToClipboard(const QString& text)
{
    // 获取系统剪切板对象
    QClipboard* clipboard = QApplication::clipboard();

    // 将文本设置到剪切板
    clipboard->setText(text);

    // 显示复制成功提示
    showMessage(QStringLiteral("已复制到剪切板"));

    // 记录复制操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据校验] 复制结果到剪切板，长度：%2 字符")
                         .arg(timestamp)
                         .arg(text.length());

    appendLog(logMsg);
}

// 显示消息提示
void FormChildDataValidation::showMessage(const QString& message, bool isError)
{
    if(isError) {
        // 错误消息：显示消息框
        QMessageBox::warning(this, QStringLiteral("错误"), message);
    }else {
        // 普通消息：输出到调式控制台
        qDebug() << message;
    }
}

// 设置校验计算忙碌状态
void FormChildDataValidation::setCheckSumBusy(bool busy)
{
    // 设置校验计算运行状态标志
    checkSumRunning = busy;

    // 根据忙碌状态启用/禁用计算按钮
    // busy=true 时禁用，busy = false 时启用
    ui->pushButton_calculateCheckSums->setEnabled(!busy);

    ui->pushButton_copyCheckSums->setEnabled(!busy);
}

// 追加日志到日志队列
void FormChildDataValidation::appendLog(const QString& message)
{
    logEntries.enqueue(message);

    qDebug() << "数据校验工具日志：" << message;

    while(logEntries.size() > 1000) {
        logEntries.dequeue();
    }
}

// 窗口关闭事件
void FormChildDataValidation::closeEvent(QCloseEvent* event)
{
    saveLog();
    event->accept();
}

// 大小写复选框状态变化槽函数
void FormChildDataValidation::onUpperCaseToggled(bool enabled)
{
    if(!ui || !ui->pushButton_copyCheckSums || !ui->pushButton_calculateCheckSums
        ||!ui->lineEdit_crc16 || !ui->lineEdit_crc32 || !ui->lineEdit_md5
        || !ui->lineEdit_sha1 || !ui->lineEdit_sha256) {
        qDebug() << "FormChildDataValidation::onUpperCaseToggled：UI orcontrols = null";
        return;
    }

    // 仅在已有校验值结果时执行转换操作（检查CRC16是否为空作为判断条件）
    // 如果所有校验值都为空，不执行任何操作
    if(!ui->lineEdit_crc16->text().isEmpty()) {
        if(enabled) {
            // 复选框选中：将所有校验值转换为大写
            ui->lineEdit_crc16->setText(ui->lineEdit_crc16->text().toUpper());
            ui->lineEdit_crc32->setText(ui->lineEdit_crc32->text().toUpper());
            ui->lineEdit_md5->setText(ui->lineEdit_md5->text().toUpper());
            ui->lineEdit_sha1->setText(ui->lineEdit_sha1->text().toUpper());
            ui->lineEdit_sha256->setText(ui->lineEdit_sha256->text().toUpper());
        }else {
            // 复选框选中：将所有校验值转换为小写
            ui->lineEdit_crc16->setText(ui->lineEdit_crc16->text().toLower());
            ui->lineEdit_crc32->setText(ui->lineEdit_crc32->text().toLower());
            ui->lineEdit_md5->setText(ui->lineEdit_md5->text().toLower());
            ui->lineEdit_sha1->setText(ui->lineEdit_sha1->text().toLower());
            ui->lineEdit_sha256->setText(ui->lineEdit_sha256->text().toLower());
        }
    }

    // 记录异步校验完成日志
    // 记录复制操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据校验] 异步校验值计算完成")
                         .arg(timestamp);

    appendLog(logMsg);
}

// 异步校验计算完成槽函数
void FormChildDataValidation::onCheckSumFinished()
{
    if(!ui || ui->lineEdit_crc16 || ui->lineEdit_crc32 || ui->lineEdit_md5
        || ui->lineEdit_sha1 || ui->lineEdit_sha256) {
        qDebug() << "FormChildDataValidation::onCheckSumFinished：UI orcontrols = null";
        setCheckSumBusy(false);
        return;
    }

    // 接触忙碌状态，启用计算按钮和复制按钮
    setCheckSumBusy(false);

    // 获取异步计算结果（从 QFutureWatcher 中获取）
    // result() 方法会等待异步任务完成并返回结果
    auto result = checkSumWatcher.result();

    // 获取大小写设置状态
    bool isUpperCase = ui->checkBox_upperCaseCheck->isChecked();

    // 根据大小写设置格式化并显示所有校验值结果
    // 如果选中大写，直接使用结果(DataConverter 返回的是大写）
    // 如果为选中大写，转换为小写显示
    if(isUpperCase) {
        ui->lineEdit_crc16->setText(result.crc16);
        ui->lineEdit_crc32->setText(result.crc32);
        ui->lineEdit_md5->setText(result.md5);
        ui->lineEdit_sha1->setText(result.sha1);
        ui->lineEdit_sha256->setText(result.sha256);
    }else {
        ui->lineEdit_crc16->setText(result.crc16.toLower());
        ui->lineEdit_crc32->setText(result.crc32.toLower());
        ui->lineEdit_md5->setText(result.md5.toLower());
        ui->lineEdit_sha1->setText(result.sha1.toLower());
        ui->lineEdit_sha256->setText(result.sha256.toLower());
    }

    showMessage(QStringLiteral("校验值计算完成"));


}

