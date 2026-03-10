#include "formtcpclient.h"
#include "ui_formtcpclient.h"

// 构造函数：初始化UI、状态、样式并绑定信号
FormTcpClient::FormTcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTcpClient)
{
    ui->setupUi(this);
    // 设置ip下拉框为可编辑，允许手动输入ip
    ui->comboBox_TCPClientIP->setEditable(false);

    ui->pushButton_TCPClientDisconnect->setEnabled(false);
    ui->pushButton_TCPClientSendMsg->setEnabled(false);
    ui->plainTextEdit_TCPClientMsg->setReadOnly(true);
    ui->checkBox_TCPClientAtuoTesting->setEnabled(false);
    ui->plainTextEdit_TCPClientSendData->setPlainText("hello TCP server");

    ui->groupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->groupBox_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label_5->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->comboBox_TCPClientIP->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->spinBox_TCPClientPort->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->checkBox_TCPClientAtuoTesting->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->pushButton_TCPClientConnect->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_TCPClientDisconnect->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_TCPClientClose->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_TCPClientSendMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->plainTextEdit_TCPClientSendData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->plainTextEdit_TCPClientMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // QSS：统一浅色主题、字号与按钮/列表样式
    setStyleSheet(
        // 全局基础样式（所有控件继承）
        "QWidget {"
        "   background-color: #F3F4F6; /* 浅灰背景，护眼浅色 */"
        "   font-family: 'Microsoft YaHei', Arial, sans-serif; /* 统一字体 */"
        "   font-size: 12px; /* 基础字号 */"
        "   color: #1F2937; /* 深灰文字，易读 */"
        "}"

        // 分组框（GroupBox）样式（服务器配置区）
        "QGroupBox {"
        "   font-weight: bold; /* 标题加粗 */"
        "   font-size: 13px;"
        "   border: 1px solid #D1D5DB; /* 浅边框 */"
        "   border-radius: 6px; /* 圆角 */"
        "   margin-top: 8px; /* 标题间距 */"
        "   padding-top: 10px; /* 内部上边距 */"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px; /* 标题左偏移 */"
        "   padding: 0 8px 0 8px; /* 标题左右间距 */"
        "}"

        // 按钮样式（启动/停止按钮）
        "QPushButton {"
        "   background-color: #FFFFFF; /* 白色背景 */"
        "   border: 1px solid #9CA3AF; /* 浅边框 */"
        "   border-radius: 4px; /* 圆角 */"
        "   padding: 6px 12px; /* 内边距，按钮更饱满 */"
        "}"
        "QPushButton:hover {"
        "   background-color: #E5E7EB; /*  hover浅灰 */"
        "   border-color: #6B7280; /* 边框加深 */"
        "}"
        "QPushButton:disabled {"
        "   background-color: #F9FAFB; /* 禁用态浅灰 */"
        "   color: #9CA3AF; /* 禁用文字灰 */"
        "   border-color: #E5E7EB;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #D1D5DB; /* 按下态深色 */"
        "}"

        // 列表控件（ListWidget，日志显示区）
        "QListWidget {"
        "   background-color: #FFFFFF;"
        "   border: 1px solid #D1D5DB;"
        "   border-radius: 4px;"
        "   padding: 4px; /* 内部边距 */"
        "   alternate-background-color: #F9FAFB; /* 隔行变色 */"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #3B82F6; /* 选中项蓝色 */"
        "   color: #FFFFFF; /* 选中文字白色 */"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #EFF6FF; /* hover浅蓝 */"
        "}"

        // 下拉框（ComboBox，IP选择区）
        "QComboBox {"
        "   background-color: #FFFFFF;"
        "   border: 1px solid #D1D5DB;"
        "   border-radius: 4px;"
        "   padding: 4px 8px; /* 内边距 */"
        "   min-width: 120px; /* 最小宽度 */"
        "}"
        "QComboBox::drop-down {"
        "   border: none; /* 下拉箭头边框隐藏 */"
        "}"
        "QComboBox::down-arrow {"
        "   image: url(:/icons/arrow_down.png); /* 可选：替换下拉箭头图标，注释掉则用默认 */"
        "   width: 8px;"
        "   height: 8px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #FFFFFF;"
        "   border: 1px solid #D1D5DB;"
        "   selection-background-color: #3B82F6;"
        "}"

        // 数字输入框（SpinBox，端口选择区）
        "QSpinBox {"
        "   background-color: #FFFFFF;"
        "   border: 1px solid #D1D5DB;"
        "   border-radius: 4px;"
        "   padding: 4px 8px;"
        "   min-width: 80px;"
        "}"
        "QSpinBox::up-button, QSpinBox::down-button {"
        "   border: none; /* 上下箭头边框隐藏 */"
        "   background-color: #F3F4F6;"
        "}"

        // 文本框（可选：若有日志输入/显示文本框）
        "QTextEdit {"
        "   background-color: #FFFFFF;"
        "   border: 1px solid #D1D5DB;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "}"
    );

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);  // Qt5:启动高DPI缩放
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);  // Qt5:启动高DPI位图
#endif

    // qDebug() << "构造函数";

    {
        // 恢复最近一次连接的 IP/端口
        QSettings settings;  // 使用默认组织/应用存储
        const QString lastIp = settings.value("TCPClient/lastIp", "127.0.0.1").toString();
        const int lastPort = settings.value("TCPClient/lastPort", ui->spinBox_TCPClientPort->value()).toInt();


        int index = ui->comboBox_TCPClientIP->findText(lastIp); // 查找下拉是否已有改IP
        if(index >= 0) {
            ui->comboBox_TCPClientIP->setCurrentIndex(index);   // 已存在则选中
        }else {
            ui->comboBox_TCPClientIP->setCurrentIndex(index);   // 不存在则直接填入可编辑框
        }

        if(lastPort >=  ui->spinBox_TCPClientPort->minimum()    // 检验端口在允许范围内
            && lastPort <= ui->spinBox_TCPClientPort->maximum()) {
            ui->spinBox_TCPClientPort->setValue(lastPort);  // 恢复端口
        }
    }

    connect(&NetworkClient, &Network::connectionEstablished, this, [this](){  // 绑定“连接成功“信号
        ui->pushButton_TCPClientConnect->setEnabled(false);     // 禁用”连接“避免重复
        ui->pushButton_TCPClientDisconnect->setEnabled(true);   // 允许断开
        ui->pushButton_TCPClientSendMsg->setEnabled(true);      // 允许发送
        ui->plainTextEdit_TCPClientSendData->setEnabled(true);  // 启用输入框
        ui->checkBox_TCPClientAtuoTesting->setEnabled(true);    // 允许自动测试
        connected = true;                                       // 标记已连接

        qDebug() << "TCP连接成功";
        QString strTemp = QString("[%1] 连接服务器成功")
                              .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ui->plainTextEdit_TCPClientMsg->appendPlainText(strTemp);   // 追加日志（自动滚动到底部）

        trimLog();  // 日志裁剪
    });

    connect(&NetworkClient, &Network::connectionFailed, this, [this](const QString& errorString){  // 绑定“连接失败“信号
        ui->pushButton_TCPClientConnect->setEnabled(true); // 允许重新连接
        ui->pushButton_TCPClientDisconnect->setEnabled(false); // 禁用断开
        ui->pushButton_TCPClientSendMsg->setEnabled(false); // 禁用发送
        ui->plainTextEdit_TCPClientSendData->setEnabled(false); // 禁用输入框
        ui->checkBox_TCPClientAtuoTesting->setEnabled(false); // 禁用自动测试
        connected = false;   // 标记未连接

        qDebug() << "TCP连接成功";

        QString strTemp = QString("[%1] 连接服务器失败: %2")
                              .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), errorString);
        ui->plainTextEdit_TCPClientMsg->appendPlainText(strTemp);   // 追加日志（自动滚动到底部）

        trimLog();  // 日志裁剪
    });

    connect(&NetworkClient, &Network::dataReceived, this, [this](const QString& data){  // 绑定“收到数据“信号
        // 性能优化：appendPlainText 会自动移动到底部，不需要手动设置cursor
        QString strTemp = QString("\n[%1] 接收：%2")
                              .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), data);
        ui->plainTextEdit_TCPClientMsg->appendPlainText(strTemp);   // 追加日志（自动滚动到底部）

        trimLog();  // 日志裁剪
    });


}

// 析构函数：释放UI，Network内部资源管理
FormTcpClient::~FormTcpClient()
{
    qDebug() << "FormTcpClient 析构函数开始";

    try {
        if(ui) {
            delete ui;
            ui = nullptr;
        }
    }catch(const std::bad_exception& e) {
        qWarning() << "FormTcpClient析构时发生异常：" << e.what();

    }catch(...) {
        qWarning() << "FormTcpClient析构时发生未知异常";
    }

    qDebug() << "FormTcpClient 析构函数结束";
}

// 发送连接：验证IP/端口，保存最近配置并请求连接
void FormTcpClient::on_pushButton_TCPClientConnect_clicked()
{
    try {
        if(!ui->pushButton_TCPClientConnect) {  // 防止按钮被禁用时误触
            qDebug() << "connection button is disabled, ignoring click";
            return;
        }

        connected = false; // 重置连接状态，等待结果
        QString ipAddress = ui->comboBox_TCPClientIP->currentText();    // 获取目标ip
        int port = ui->spinBox_TCPClientPort->value();                  // 获取目标端口

        auto ipValidation = InputValidator::validatorNetworkAddress(ipAddress); // 校验ip
        if(!ipValidation.isValid) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning,
                         ipValidation.errorMessage, this);  // ip校验失败，弹出警告
            ui->comboBox_TCPClientIP->setFocus();   // 聚焦便于修改
            return;
        }

        auto portVaildation = InputValidator::validatorPort(port);              // 校验port
        if(!portVaildation.isValid) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning,
                         portVaildation.errorMessage, this);    // port校验失败，弹出警告
            ui->spinBox_TCPClientPort->setFocus();  // 聚焦
            return;
        }

        // 记录配置信息
        LOG_INFO("TCP客户端", QString("尝试连接到 %1:%2").arg(ipAddress, port));

        {   // 持久化最新IP/端口
            QSettings settings;
            settings.setValue("TCPClient/lastIp", ipAddress);
            settings.setValue("TCPClient/lastPort", port);
            settings.sync();        // 立即同步到磁盘，确保数据保存
        }

        ui->pushButton_TCPClientConnect->setEnabled(false); // 警用连接按钮
        ui->pushButton_TCPClientDisconnect->setEnabled(true);   // 允许断开

        NetworkClient.ClientConnectToServer(ipAddress, port);   // 发起连接

        QString strTemp = QString("[%1] 正在连接到 %2：%3......")
                              .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))  // %1 时间
                              .arg(ipAddress)                                                    // %2 IP地址
                              .arg(QString::number(port));                                       // %3 端口（显式转字符串）

        ui->plainTextEdit_TCPClientMsg->appendPlainText(strTemp);   // appendPlainText 自动滚动到底部

    } catch(std::exception& e) {
        LOG_ERROR("TCP客户端", QString("连接时发生异常：%1").arg(e.what()));
        HANDLE_ERROR(ErrorHandler::UnknowError, ErrorHandler::Critical, QString("连接时发生异常：%1").arg(e.what()), this);
        ui->pushButton_TCPClientConnect->setEnabled(true);
        ui->pushButton_TCPClientDisconnect->setEnabled(false);
    } catch(...) {
        LOG_ERROR("TCP客户端", QString("连接时发生未知异常：%1"));
        HANDLE_ERROR(ErrorHandler::UnknowError, ErrorHandler::Critical, QString("连接时发生未知异常：%1"), this);
        ui->pushButton_TCPClientConnect->setEnabled(true);
        ui->pushButton_TCPClientDisconnect->setEnabled(false);
    }
}

// 断开连接：关闭socket并重置UI
void FormTcpClient::on_pushButton_TCPClientDisconnect_clicked()
{
    NetworkClient.DisconnectFromHost();     // 主动断开连接

    ui->pushButton_TCPClientConnect->setEnabled(true);
    ui->pushButton_TCPClientDisconnect->setEnabled(false);
    ui->pushButton_TCPClientSendMsg->setEnabled(false);
    ui->checkBox_TCPClientAtuoTesting->setEnabled(false);
    ui->plainTextEdit_TCPClientSendData->setEnabled(false);

    connected = false;

    ui->plainTextEdit_TCPClientMsg->appendPlainText("\n[promp:disconnect from server");
}

// 关闭窗口/退出程序
void FormTcpClient::on_pushButton_TCPClientClose_clicked()
{
    savePlainTextEditToFile(ui->plainTextEdit_TCPClientMsg);
    QCoreApplication::quit();       // 触发应用退出
}

// 自动测试开关：勾选则启用定时发送，取消则恢复手动
void FormTcpClient::on_checkBox_TCPClientAtuoTesting_checkStateChanged()
{
    bool isAutoTesting = ui->checkBox_TCPClientAtuoTesting->isChecked();  // 读取复选框状态
    if(isAutoTesting) { // 是否启动自动测试
        if(!connected) {    // 必须已连接服务器
            HANDLE_ERROR(ErrorHandler::NetworkError, ErrorHandler::Warning,
                         "未连接服务器，无法开始自动测试", this);
            ui->checkBox_TCPClientAtuoTesting->setChecked(false);   // 状态回退，不勾选
            return;
        }

        // 已连接服务器，从QPlainTextEdit控件获取文本消息
        QString message = ui->plainTextEdit_TCPClientSendData->toPlainText().trimmed();
        if(message.isEmpty()) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning,
                         "发送内容模板不能为空，无法开启自动测试", this);
            ui->checkBox_TCPClientAtuoTesting->setChecked(false);   // 状态回退，不勾选
            return;
        }

        // 设置自动测试消息内容
        NetworkClient.setAutoTestMessage(message);
        NetworkClient.StartTimerOutFunc();  // 启动定时器自动发送
        ui->plainTextEdit_TCPClientSendData->setEnabled(false); // 禁用手动输入
        ui->pushButton_TCPClientSendMsg->setEnabled(false);     // 禁用手动发送
    }else {
        NetworkClient.StopTimerOutFunc();   // 关闭自动测试
        enableCommunicationControls(true);   // 重启启用手动输入
    }
}

// 发送消息：需要已连接并消息不能为空
void FormTcpClient::on_pushButton_TCPClientSendMsg_clicked()
{
    QString message = ui->plainTextEdit_TCPClientSendData->toPlainText().trimmed(); // 获取去空白的输入
    if(message.isEmpty()) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "发送内容不能为空", this);
        return;
    }

    if(!connected) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "未连接服务器，无法发送", this);
        return;
    }

    NetworkClient.ClientSendMsgToServer(message);   // 发送消息

    QString timeStamp = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");   // 时间戳
    QString logEntry = QString("\n[%1]\n客户端发送:%2").arg(timeStamp, message); // 发送日志
    ui->plainTextEdit_TCPClientMsg->appendPlainText(logEntry);      // 追加日志

    if(!NetworkClient.StrTempData.isEmpty()) {  // 如果底层有附加日志：继续追加
        ui->plainTextEdit_TCPClientMsg->appendPlainText(NetworkClient.StrTempData);
    }

    trimLog();      // 裁剪日志
}


// 日志裁剪：保留行数/超限删除步长
void FormTcpClient::trimLog(int keepBlocks, int trimStep)
{
    static const int kKeepDefault = 1000;       //默认保留数
    static const int kTrimDefault = 200;        // 默认删除步长
    const int targetKeep = keepBlocks > 0 ? keepBlocks : kKeepDefault;  // 获取实际bolck数
    const int step = trimStep ? trimStep > 0 : kTrimDefault;    // 获取实际步长

    auto doc = ui->plainTextEdit_TCPClientMsg->document();   //获取文档对象
    int currentblockCount = doc->blockCount(); // 当前block数

    auto max = [](int a, int b) -> bool {
        return a > b;
    };

    // 计算需删除行数：当且仅当日志行数超出保留阈值时，才执行裁剪操作
    int removeBlocks = max(0, currentblockCount - targetKeep - step);
    QTextCursor cursor(doc);                    // 创建光标
    cursor.movePosition(QTextCursor::Start);    // 移动到开头
    for(int i = 0; i < removeBlocks; i++) {     // 选取前 N 个block
        cursor.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
    }

    cursor.removeSelectedText();    // 删除选取文本
    if(!cursor.atEnd()) {
        cursor.deleteChar();            // 删除残留换行
    }
}

// IP合法性校验（保留旧接口）
bool FormTcpClient::checkIPAddrIsVaild(QString strIPAddress)
{
    QRegularExpression ipRegex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");
    return ipRegex.match(strIPAddress).hasMatch();  // 匹配成员
}

// 批量控制与连接相关的UI
void FormTcpClient::enableCommunicationControls(bool enable)
{
    ui->pushButton_TCPClientConnect->setEnabled(!enable);       // 启用通信时禁用“连接服务器按钮”按钮
    ui->pushButton_TCPClientDisconnect->setEnabled(enable);     // 启用/禁用“断开服务器”按钮
    ui->pushButton_TCPClientSendMsg->setEnabled(enable);        // 启动/禁止发送按钮
    ui->checkBox_TCPClientAtuoTesting->setEnabled(enable);      // 启用/禁用自动测试
    ui->plainTextEdit_TCPClientSendData->setEnabled(enable);    // 启用/禁用输入框
}

// 窗口关闭事件，保存日志并接受关闭
void FormTcpClient::closeEvent(QCloseEvent* event)
{
    saveLog();
    event->accept();
}

// 保存日志文本到文件
void FormTcpClient::savePlainTextEditToFile(QPlainTextEdit* plainTextEdit)
{
    if(!plainTextEdit) {
        qWarning() << "FormTcpClient::savePlainTextEditToFile: plainTextEdit = null";
    }

    // 获取配置文件所在目录（与QSetstrings配置文件同一目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath); // 确保目录存在

    // 使用固定文件名，追加模式
    QString filename = QDir(appDataPath).filePath("TCPClientLogFile.txt");

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

// 保存日志
void FormTcpClient::saveLog()
{
    if(ui && ui->plainTextEdit_TCPClientMsg) {
        savePlainTextEditToFile(ui->plainTextEdit_TCPClientMsg);
    }
}




















