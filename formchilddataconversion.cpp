#include "formchilddataconversion.h"
#include "ui_formchilddataconversion.h"

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QStringConverter> // Qt6 字符串编码转化器
#else
#include <QTextCode>
#endif

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

// 最大转换长度限制
static const int kMaxConvertLength = 50000;

// 异步转换阈值
static const int kAsyncConversiontThreshold= 15000;

FormChildDataConversion::FormChildDataConversion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormChildDataConversion)
    , inputUpdateTime(new QTimer(this))
{
    ui->setupUi(this);

    // 初始化转换类型下拉框控件
    ui->comboBox_conversionType->addItem("十进制 -> 二进制", "decimal_to_binary");
    ui->comboBox_conversionType->addItem("二进制 -> 十进制", "binary_to_decimal");

    // 配置输入更新防抖动定时器
    inputUpdateTime->setSingleShot(true);   // 设置为单次触发模式
    inputUpdateTime->setInterval(300);      // 设置延迟时间为300ms

    // 连接定时器的 timeout 信号到 lambda 表达式
    connect(inputUpdateTime, &QTimer::timeout, this, [this]() {
        QString text = ui->textEdit_inputText->toPlainText();   // 获取输入文本
        updateInputInfo(text);
    });

    // 连接 UI 控件的信号到对应的槽函数
    connectSignals();

    // 连接异步转换监视器的 finished 信号到完成处理槽函数
    connect(&conversionWatcher, &QFutureWatcher<DataConverter::ConversionResult>::finished, this, &FormChildDataConversion::onConversionFinished);

    ui->textEdit_inputText->setPlaceholderText("请输入要转换的数据...");
    ui->textEdit_outputText->setPlaceholderText("转换结果将在这里显示...");

    // 初始化日志：记录启动信息
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    // 记录转换成功日志
    QString logMsg = QStringLiteral("[%1] [数据转换] 数据转换工具启动")
                         .arg(timestamp);
    appendLog(logMsg);
}

FormChildDataConversion::~FormChildDataConversion()
{
    delete ui;
}

void FormChildDataConversion::on_pushButton_converOperator_clicked()
{
    if(!ui || !ui->textEdit_inputText || !ui->textEdit_outputText) {
        qWarning() << "FormChildDataConversion::on_comboBox_conversionType_activated：UI or controls = null";
        return;
    }

    // 防止用户重复点击转换按钮，导致重复操作
    if(conversionRunning) {
        return;
    }

    // 获取输入数据
    QString input = ui->textEdit_inputText->toPlainText();

    // 输入验证-判空
    if(input.isNull()) {
        showMessage(QStringLiteral("请输入要转换的数据"), true);
        return;
    }

    // 获取转换类型
    // currentData() 获取返回的数据值("decimal_to_binary" 或 "binary_to_decimal")
    QString conversionType = ui->comboBox_conversionType->currentData().toString();
    // currentText() 获取返回的数据值("十进制 -> 二级制你hi" 或 "二进制 -> 十进制")
    QString conversionTypeName = ui->comboBox_conversionType->currentText();

    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    // 记录转换成功日志
    QString logMsg = QStringLiteral("[%1] [数据转换] 开始转换：%2，输出长度：%2 字符")
                         .arg(timestamp)
                         .arg(conversionTypeName)
                         .arg(input.length());

    appendLog(logMsg);

    if(input.length() > kAsyncConversiontThreshold) {
        // 异步转换模式：数据量 > 15000字符
        // 设置转换忙状态
        setConversionBusy(true);

        // 记录异步转换日志
        // 记录转换失败日志
        QString logMsg = QStringLiteral("[%1] [数据转换] 使用异步转换（输入长度超过阈值：%2")
                             .arg(timestamp)
                             .arg(kMaxConvertLength);
        appendLog(logMsg);

        // 使用 Qtconcurrent::run() 创建线程并在后台执行转换操作
        auto future = QtConcurrent::run([input, conversionType](){
            DataConverter::ConversionResult result;

            // 根据转换类型调用相应的转换方法
            if(conversionType == "decimal_to_binary") {
                result = DataConverter::decimalToBinary(input);
            }else {
                result = DataConverter::binaryToDecimal(input);
            }
            return result;
        });

        // 设置要监视的 Future，当转换完成时会触发 finished 信号
        conversionWatcher.setFuture(future);
        return; // 不等待结果
    }

    // 同步转换方式：数据量 < 50000字符
    // 直接调用转换方法，立即获取结果
    DataConverter::ConversionResult result;
    // 根据转换类型调用相应的转换方法
    if(conversionType == "decimal_to_binary") {
        result = DataConverter::decimalToBinary(input);
    }else {
        result = DataConverter::binaryToDecimal(input);
    }

    if(!result.success) {
        ui->textEdit_outputText->setPlaceholderText(result.data);
    }

    // 显示转换结果
    showResult(result, ui->textEdit_outputText);
}


void FormChildDataConversion::on_pushButton_clearOperator_clicked()
{
    if(!ui || !ui->textEdit_inputText || !ui->textEdit_outputText) {
        qWarning() << "FormChildDataConversion::on_pushButton_clearOperator_clicked：UI or controls = null";
        return;
    }

    // 清空输入和输出文本框
    ui->textEdit_inputText->clear();
    ui->textEdit_outputText->clear();

    // 更新统计信息
    updateInputInfo("");
    updateOutputInfo("");

    // 记录清理操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据转换] 清空数据")
                         .arg(timestamp);

    appendLog(logMsg);
}


void FormChildDataConversion::on_pushButton_swapOperator_clicked()
{
    if(!ui || !ui->textEdit_inputText || !ui->textEdit_outputText) {
        qWarning() << "FormChildDataConversion::on_pushButton_swapOperator_clicked：UI or controls = null";
        return;
    }

    // 获取输入和输出文本框的【实际内容】
    QString inputText = ui->textEdit_inputText->toPlainText();
    QString outputText = ui->textEdit_outputText->toPlainText();

    // ===== 核心修复：交换实际内容（而非占位符）=====
    // 错误：setPlaceholderText → 改占位符；正确：setPlainText → 改实际显示的文本
    ui->textEdit_inputText->setPlainText(outputText);
    ui->textEdit_outputText->setPlainText(inputText);

    // （可选）如果需要同时交换占位符（比如原本有自定义占位符），可加这两行
    // ui->textEdit_inputText->setPlaceholderText(ui->textEdit_outputText->placeholderText());
    // ui->textEdit_outputText->setPlaceholderText(ui->textEdit_inputText->placeholderText());

    // 更新信息（传入交换后的实际内容，逻辑正确）
    updateInputInfo(outputText);
    updateOutputInfo(inputText);

    // 记录交换操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据转换] 交换输入输出")
                         .arg(timestamp);

    appendLog(logMsg);
}

void FormChildDataConversion::on_pushButton_copyOperator_clicked()
{
    if(!ui || !ui->textEdit_inputText || !ui->textEdit_outputText) {
        qWarning() << "FormChildDataConversion::on_pushButton_copyOperator_clicked：UI or controls = null";
        return;
    }

    // 获取输出文本框的内容
    QString outputText = ui->textEdit_outputText->toPlainText().trimmed();


    // 判空
    if(outputText.isEmpty()) {
        showMessage(QStringLiteral("没有可复制的内容"), true);
        return;
    }

    copyToClipboard(outputText);

    // 记录复制操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据转换] 复制结果")
                         .arg(timestamp);

    appendLog(logMsg);
    showMessage(QStringLiteral("复制成功！"), false); // 增加成功提示
}

// 保存日志（公共接口，提供主窗口调用）
void FormChildDataConversion::saveLog()
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
        out << Qt::endl; // 修复：去掉括号，Qt::endl是枚举不是函数
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
    qDebug() << "数据转换工具日志已保存至：" << fileName;

    // 清空日志条目
    logEntries.clear();

    // 仅窗口可见时弹窗提示
    if(this->isVisible()) {
        QMessageBox::information(this, QStringLiteral("成功"), successMsg);
    }
}

// 异步转换完成槽函数
void FormChildDataConversion::onConversionFinished()
{
    if(!ui || !ui->textEdit_outputText) {
        qWarning() << "FormChildDataConversion::onConversionFinished：UI or outputTextEdit = null";
        setConversionBusy(false);
        return ;
    }

    // 设置转换状态为false（启动相关按钮）
    setConversionBusy(false);

    // 获取异步转换结果
    auto result = conversionWatcher.result();

    // 记录异步转换工具完成日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据转换] 异步转换完成").arg(timestamp);
    appendLog(logMsg);

    showResult(result, ui->textEdit_outputText);
}

// 输入文本变换槽函数
void FormChildDataConversion::onInputTextChanged()
{
    if(!inputUpdateTime) {
        qWarning() << "FormChildDataConversion::onInputTextChanged：outputTextEdit = null";
        setConversionBusy(false);
        return ;
    }

    // 停止当前的防抖定时器，避免每次输入到更新数据
    inputUpdateTime->stop();
    inputUpdateTime->start();
}

// 统一消息提示函数
void FormChildDataConversion::showMessage(const QString& message, bool isError)
{
    if(isError) {
        // 错误消息：显示消息框
        QMessageBox::warning(this, QStringLiteral("错误"), message);
    }else {
        // 普通消息：输出到调式控制台
        qDebug() << message;
    }
}

// 设置转换忙状态
void FormChildDataConversion::setConversionBusy(bool busy)
{
    conversionRunning = true;

    // 根据 busy 状态启用/禁用相关按钮
    // !busy 表示：如果 busy 为真，则 !busy 为false，按钮被禁用
    //            如果 busy 为假，则 !bysy 为 true，按钮被启用

    ui->pushButton_converOperator->setEnabled(!busy);
    ui->pushButton_clearOperator->setEnabled(!busy);
    ui->pushButton_swapOperator->setEnabled(!busy);
    ui->pushButton_copyOperator->setEnabled(!busy);
}

// 展示转换结果或错误信息
void FormChildDataConversion::showResult(const DataConverter::ConversionResult& result, QTextEdit* outputEdit)
{
    if(!outputEdit) {
        qWarning() << "FormChildDataConversion::showResult：outputEdit = null";
        return;
    }

    // 复用时间戳，避免重复创建 QDateTime 对象
    const QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));

    if(result.success) {
        // 转换成功：设置【实际内容】，清空占位符
        outputEdit->setPlainText(result.data);          // 关键：结果写入实际内容，不是占位符
        outputEdit->setPlaceholderText("");             // 清空占位符，避免干扰
        updateOutputInfo(result.data);                  // 更新输出统计信息
        showMessage(QStringLiteral("转换成功"));

        // 记录转换成功日志（补充输入/输出长度，方便排查）
        const QString logMsg = QStringLiteral("[%1] [数据转换] 转换成功，输出长度：%2 字符")
                                   .arg(timestamp)
                                   .arg(result.data.length());
        appendLog(logMsg);
    } else {
        // 转换失败：清空实际内容，错误信息放占位符
        outputEdit->setPlainText("");                   // 清空实际内容
        outputEdit->setPlaceholderText(result.errorMessage); // 错误提示放占位符
        updateOutputInfo("");                           // 更新统计信息
        showMessage(result.errorMessage, true);         // 显示错误提示

        // 记录转换失败日志
        const QString logMsg = QStringLiteral("[%1] [数据转换] 转换失败：%2")
                                   .arg(timestamp)
                                   .arg(result.errorMessage);
        appendLog(logMsg);
    }
}

// 更新输入统计信息
void FormChildDataConversion::updateInputInfo(const QString& text)
{
    if(!ui || !ui->label_inputInfo) {
        return;
    }

    QString info = DataConverter::getDataInfo(text);
    ui->label_inputInfo->setText(info);
}

// 更新输出统计信息
void FormChildDataConversion::updateOutputInfo(const QString& text)
{
    if(!ui || !ui->label_inputInfo) {
        return;
    }

    QString info = DataConverter::getDataInfo(text);
    ui->label_outputInfo->setText(info);
}

// 复制文本到剪切板
void FormChildDataConversion::copyToClipboard(const QString& text)
{
    // 获取系统剪切板对象
    QClipboard* clipboard = QApplication::clipboard();

    // 将文本设置到剪切板
    clipboard->setText(text);

    // 显示复制成功提示
    showMessage(QStringLiteral("已复制到剪切板"));

    // 记录复制操作日志
    QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    QString logMsg = QStringLiteral("[%1] [数据转换] 复制结果到剪切板，长度：%2 字符")
                            .arg(timestamp)
                            .arg(text.length());

    appendLog(logMsg);
}

// 连接所有信号和槽
void FormChildDataConversion::connectSignals()
{
    if(!ui || !ui->textEdit_inputText) {
        qWarning() << "FormChildDataConversion::connectSignals：UI or textEdit_inputText = null";
        return;
    }

    // 连接输出文本变化的信号到防抖动处理函数
    connect(ui->textEdit_inputText, &QTextEdit::textChanged, this, &FormChildDataConversion::onInputTextChanged);
}

// 追加日志条目
void FormChildDataConversion::appendLog(const QString& message)
{
    // 将日志消息添加到日志队列的末尾（FIFO结构）
    logEntries.enqueue(message);

    qDebug() << "数据转换工具日志：" << message;

    // 保持日志队列在合理的大小范围内，防止内存占用过大
    while(logEntries.size() > 1000) {
        logEntries.dequeue(); // 删除队首日志
    }
}

// 裁剪日志队列
void FormChildDataConversion::trimLog()
{

}

// 保存纯文本编辑框内容到文件
void FormChildDataConversion::savePlainTextEditToFile(QPlainTextEdit* plainTextEdit)
{
    if(!plainTextEdit) {
        qWarning() << "FormTcpClient::savePlainTextEditToFile: plainTextEdit = null";
    }

    // 获取配置文件所在目录（与QSetstrings配置文件同一目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath); // 确保目录存在

    // 使用固定文件名，追加模式
    QString filename = QDir(appDataPath).filePath("DataConversionLogFile.txt");

    // 检查文件是否存在，决定追加模式还是创建并加入文件
    bool fileExits = QFile::exists(filename);
    QIODevice::OpenMode openMode = fileExits ?
                                       (QIODevice::Append | QIODevice::Text)
                                             :(QIODevice::WriteOnly | QIODevice::Text);

    QFile file(filename);
    if(file.open(openMode)) {
        QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        out.setCodec("UTF-8");   // Qt6 设置编码格式
#else
        out.setEncoding(QStringConverter::Utf8);
#endif

        // 如果是追加模式,先写分隔符和时间戳
        if(fileExits) {
            QString timestamp = QDateTime::currentDateTime().toString("yyy-MM-dd hh:mm:ss");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            out << "\n" << "=====-=" << timestamp << "=======" << endl;
#else
            out << "\n" << "=======" << timestamp << "=======" << Qt::endl;
#endif
        }

        // 写入文本内容
        out << plainTextEdit->toPlainText();
        file.close();
        qDebug() << "TCP客户端日志保存到：" << filename;

        // 注意：窗口关闭时不显示信息框：避免阻塞
        if(this->isVisible()) {
            QMessageBox::information(this, "成功", QString("日志已保存到 %1").arg(filename));
        }
    }else {
        qDebug() << "TCP客户端日志保存失败: " << file.errorString();
        if(this->isVisible()) {
            QMessageBox::critical(this, "错误", "保存失败：" + file.errorString());
        }
    }
}

// 窗口关闭事件
void FormChildDataConversion::closeEvent(QCloseEvent* event)
{
    saveLog();
    event->accept();
}







