#include "formtcpserver.h"
#include "ui_formtcpserver.h"
#include "errorhandler.h" // 统一错误处理

// 功能：构造函数：初始化 UI、服务器实例、样式与信号
// 说明：恢复上次 IP/端口，填充本机 IPv4，下拉框与按钮初始状态，应用统一 QSS
FormTcpServer::FormTcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTcpServer)
{
    ui->setupUi(this);

    ui->comboBox_TCPServerIP->setEnabled(true);

    tcpServer = new QTcpServer(this); // 服务器实例，RAII绑定到父对象上，父对象可以手动控制服务器实例的销毁和自动销毁

    // 监听新连接信号
    connect(tcpServer, &QTcpServer::newConnection, this, &FormTcpServer::TcpServerConnectedFunc);

    ui->pushButton_TCPServerStop->setEnabled(false);    // 初始未运行时禁用“停止按钮”

    // 枚举本机 IPv4，填充下拉框
    QList<QHostAddress> addr_list = QNetworkInterface::allAddresses();

    for(const QHostAddress& address : addr_list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)    // 仅保留 IPv4
        {
            ui->comboBox_TCPServerIP->addItem(address.toString());  // 加入下拉框
        }
    }

    // 恢复上次使用的 IP 与 端口
    {
        // setting 是qt提供的持久化存储工具，
        QSettings settings;  // 使用默认组名/应用名保存配置
        const QString lastIp = settings.value("TCPServer/LastIp").toString();   // 上次IP
        const int lastPort = settings.value("TCPSever/lastPort", 12345).toInt(); // 上次端口（默认12345）

        if(!lastIp.isEmpty()) {
            int index = ui->comboBox_TCPServerIP->findText(lastIp);
            if(index >= 0) {
                ui->comboBox_TCPServerIP->setCurrentIndex(index);
            }
        }

        if(lastPort >= ui->spinBox_TCPServerPort->minimum() &&
            lastPort <= ui->spinBox_TCPServerPort->maximum()) { // 校验范围合法性
            ui->spinBox_TCPServerPort->setValue(lastPort);  //恢复端口
        }
    }

    ui->listWidget_TCPServerListMsg->setUniformItemSizes(true);     // 固定高度绘制，性能更好
    ui->listWidget_TCPServerListMsg->setSelectionMode(QAbstractItemView::SingleSelection); // 单选模式
    ui->pushButton_TCPServerClose->setIconSize(QSize(15, 15)); // 统一按钮图标尺寸
    ui->pushButton_TCPServerStop->setIconSize(QSize(15, 15));
    ui->pushButton_TCPServerStart->setIconSize(QSize(15, 15));
    if(ui->pushButton_TCPServerSendMsg) {       // 发送按钮存在时设置图标尺寸
        ui->pushButton_TCPServerSendMsg->setIconSize(QSize(15, 15));
    }

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, false); // Qt5 手动处理高 DPI
#endif

    // 控件固定尺寸策略
    ui->groupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->groupBox_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->listWidget_TCPServerListMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->comboBox_TCPServerIP->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->spinBox_TCPServerPort->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_TCPServerStart->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_TCPServerStop->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_TCPServerClose->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if(ui->plainTextEdit_TCPServerSendData) {
        ui->plainTextEdit_TCPServerSendData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    if(ui->pushButton_TCPServerSendMsg) {
        ui->pushButton_TCPServerSendMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

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
}


// 功能：析构函数，清理 socket、关闭服务器与UI
// 说明：主动断开/关闭所有 socket，防止资源悬挂：异常捕获避免析构抛出
FormTcpServer::~FormTcpServer()
{
    qDebug() << "FormTcpServer 析构函数开始"; // 记录析构起点
    try {
        for(auto client : tcpServerSocketList) {    // 遍历所有客户端
            if(client) {                            // 判空
                client->disconnect();               // 断开信号槽

                if(client->state() != QAbstractSocket::UnconnectedState) {  //若仍链接
                    client->abort();                                        // 立即中断
                }

                client->setParent(nullptr); // 接触父子关系
                delete client;              // 删除实例
            }
        }

        tcpServerSocketList.clear();                                  // 清空列表

        if(tcpServer) {     // 若服务器存在
            tcpServer->disconnect();    // 断开信号槽
            tcpServer->close();         // 关闭监听
        }

        tcpServer = nullptr;            // 置为空指针
        tcpServerSocket = nullptr;

        if(ui) {
            delete ui;
            ui = nullptr;
        }
    } catch(const std::exception& e) {
        qWarning() << "FormTcpServer 析构时发生异常：" << e.what(); // 捕获标准异常
    } catch(...) {
        qWarning() << "FormTcpServer 析构时发生未知异常！";          // 捕获未知异常
    }



    qDebug() << "FormTcpServer 析构函数结束。"; // 记录析构结束
}


// 功能：服务器主动群发输入框中的信息
// 说明：检验服务运行、文本非空且存储客户端，再将 UTF-8 字节广播给所有连接
void FormTcpServer::on_pushButton_TCPServerSendMsg_clicked()
{
    if(!ui->plainTextEdit_TCPServerSendData) { // 未找到输入框
        return;
    }

    if(!serverRunning) { // 服务未启动
        HANDLE_ERROR(ErrorHandler::NetworkError, ErrorHandler::Warning, "服务器未启动，无法发送消息。", this);
        return;
    }

    QString message = ui->plainTextEdit_TCPServerSendData->toPlainText().trimmed(); // 获取输入
    if(message.isEmpty()) { // 空内存
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "发送内容不能为空", this);
        return;
    }

    if(tcpServerSocketList.isEmpty()) { // 无连接客户端
        HANDLE_ERROR(ErrorHandler::NetworkError, ErrorHandler::Warning, "当前无客户端连接，无法发送测试消息！", this);
        return;
    }

    QByteArray data = message.toUtf8(); // 文本转 UTF-8
    for(QTcpSocket* client : std::as_const(tcpServerSocketList)) { // 群发消息
        if(client && client->state() == QAbstractSocket::ConnectedState) {
            client->write(data);
        }
    }
    QString timestamp = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    QString logEntry = QStringLiteral("\n[%1] Server send: %2\n").arg(timestamp, message); // 拼接日志

    appendColorLog(logEntry, QColor(0x008000));
}

// 功能：停止监听并断开所有客户端
// 说明：关闭服务器监听，断开并清空所有 socke，复位按钮状态
void FormTcpServer::on_pushButton_TCPServerStop_clicked()
{
    if(!serverRunning) { // 若未启动，提示返回
        appendColorLog("[Server not running]", QColor(0x666666));
        return;
    }

    tcpServer->close(); // 停止监听
    for(int i = 0; i < tcpServerSocketList.size(); i++) {
        QTcpSocket* client = tcpServerSocketList.at(i);
        if(client) {
            client->disconnect();   // 断开信号槽
            client->close();         // 关闭socket
            client->deleteLater();  // 释放socket
        }
    }

    tcpServerSocketList.clear();    // 清空列表
    appendColorLog("[Prompt:Disconnect to client connections.]\n", QColor(0x666666));
    ui->pushButton_TCPServerStart->setEnabled(true);    // 启用“启动按钮”
    ui->pushButton_TCPServerStop->setEnabled(false);    // 禁用“停止按钮”
    serverRunning = false;   // 标记停止
}

// 功能：关闭窗口前保存日志退出
void FormTcpServer::on_pushButton_TCPServerClose_clicked()
{
    saveListWidgetToFile(ui->listWidget_TCPServerListMsg); // 退出前保存日志到文件
    QCoreApplication::instance()->quit();   // 触发应用退出
}


// 功能：启动监听，校验 IP/端口并持久化配置
// 说明：防止重复启动，基础和发行校验后嗲用 listen：成功则记忆配置并更新按钮状态
void FormTcpServer::on_pushButton_TCPServerStart_clicked()
{
    QHostAddress address(ui->comboBox_TCPServerIP->currentText());  //读取选中 IP
    int port = ui->spinBox_TCPServerPort->value();

    // serverRunning = true;
    if(serverRunning) { // 若已在运行
        appendColorLog("[Server already running]", QColor(0x666666));    // 提示用户
        return; // 直接返回
    }

    if(!CheckIpAddrIsVaild(address.toString())) { // IP 校验失败
        HANDLE_ERROR(ErrorHandler::ValidationError,ErrorHandler::Warning, "Invalid IP address", this);
        return;
    }

    if(port < 1 || port > 65535) { // 端口范围校验
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "Invalid port", this);
        return;
    }

    if(tcpServer->listen(address, port)) { // 尝试开始监听
        appendColorLog("[Server started successfullly]", QColor(0x666666)); // 成功提示
        ui->pushButton_TCPServerStart->setEnabled(false);   // 禁用“启动按钮”
        ui->pushButton_TCPServerStop->setEnabled(true);     // 启用“停止按钮”
        serverRunning = true;   // 标记运行中

        QSettings settings; // 保存当前配置
        settings.setValue("TCPServer/LastIp", address.toString());  // 记忆IP
        settings.setValue("TCPSever/lastPort", port);    // 记忆端口
    }else { // 启动监听失败
        appendColorLog(QString("[Failed to start server] : %1").arg(tcpServer->errorString()), QColor(0xCC0000));
    }
}


// 功能：在日志列表追加彩色行
void FormTcpServer::appendColorLog(const QString& text, const QColor& color)
{
    // 去掉头尾行并把内部换行压成空格，避免 QListWidget...
    QString sanitized = text;
    sanitized.replace('\n', ' ');
    sanitized = sanitized.simplified();
    if(sanitized.isEmpty()) return;

    ui->listWidget_TCPServerListMsg->addItem(sanitized);

    trimLog();  // 防止日志过长导致 UI 卡顿
    int row = ui->listWidget_TCPServerListMsg->count() - 1;
    if(row >= 0) {
        if(QListWidgetItem* item = ui->listWidget_TCPServerListMsg->item(row)) {
            item->setBackground(color);
            ui->listWidget_TCPServerListMsg->setCurrentRow(row); // 滚动到最新
        }
    }
}

// 裁剪日志行数，避免空间过大 超限时将删除最早的行
// keepRows:期望保留行数
// trimStep:每次删除行数
void FormTcpServer::trimLog(int keepRows, int trimStep)
{
    static const int kKeepDefault = 1000;   // 默认保留行
    static const int kTrimDefault = 200;    // 默认删除步长
    const int targetKeep = keepRows > 0 ? keepRows : kKeepDefault;  // 实际保留行
    const int step = trimStep > 0 ? trimStep : kTrimDefault;    // 实际步长

    int count = ui->listWidget_TCPServerListMsg->count();   // 当前行数
    if(count <= targetKeep + step) // 未超限则返回
        return;
    int removeCount = count - targetKeep;   // 需要删除的行数
    for(int i = 0; i < removeCount; i++) {  // 从顶部删除
        delete ui->listWidget_TCPServerListMsg->takeItem(0);
    }
}

// 功能：检验 IP 字符串是否合法
bool FormTcpServer::CheckIpAddrIsVaild(QString strIpAddress)
{
    QHostAddress addr;  // 临时地址对象
    return addr.setAddress(strIpAddress) && addr.protocol() == QAbstractSocket::IPv4Protocol;   // 仅接受 IPv4
}

// 功能：将列表控件内部保存到文件（追加或覆盖由实现决定）
// 参数：listWdiget 日志列表指针
void FormTcpServer::saveListWidgetToFile(QListWidget* listWidget)
{
    QFile file("TCPServerLogFile.txt"); // 固定文件名，追加/覆盖由 open 模式决定
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){  // 覆盖写入
        QTextStream out(&file); // 写文件流
        for(int i = 0; i < listWidget->count(); i++) {  // 遍历列表项
            QListWidgetItem* item = listWidget->item(i);    // 获取第 i 项
            if(item) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                out << item->text() << endl;
#else
                out << item->text() << Qt::endl;
#endif
            }
        }
        file.close();
        QMessageBox::information(this, "成功", "日志已保存至 TCPServerLogFile.txt");
    }else {
        QMessageBox::critical(this, "失败", "保存失败：" + file.errorString());
    }
}

// 功能：窗口关闭事件：保存日志、清理资源
void FormTcpServer::closeEvent(QCloseEvent* event)
{
    saveListWidgetToFile(ui->listWidget_TCPServerListMsg);
    event->accept();
}

// 功能：处理新客户端连接，记录并更新列表
void FormTcpServer::TcpServerConnectedFunc()
{
    tcpServerSocket = tcpServer->nextPendingConnection();   // 获取最新待处理连接
    if(!tcpServerSocketList.contains(tcpServerSocket)) {     // 若列表未包含
        tcpServerSocketList.append(tcpServerSocket);    //记录到列表，避免重复
    }
    connect(tcpServerSocket, &QTcpSocket::readyRead, this, &FormTcpServer::ReadAllDataFunc);     // 数据可读
    connect(tcpServerSocket, &QTcpSocket::disconnected, this, &FormTcpServer::ClientDisconnectedFunc);  // 数据可读

    QString strPort = QString::number(tcpServerSocket->peerPort());

    appendColorLog("\n[Prompt:New client connection.]\n", QColor(0x666666)); // 记录连接日志

    receivedMessageCount = 0;   // 重置计数
}


// 功能：处理新客户端断开，清理列表与 UI 状态
void FormTcpServer::ClientDisconnectedFunc()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender()); // 获取断开方
    if(client) {
        tcpServerSocketList.removeOne(client);  // 从列表中移除
        client->deleteLater();  // 异步移除
    }

    QString msg = QString("\n[Prompt:Client disconnected.]");
    appendColorLog(msg, QColor(0x666666));
}

// 功能：读取所有可用数据并计数、展示日志
void FormTcpServer::ReadAllDataFunc()
{
    if(QTcpSocket* client = qobject_cast<QTcpSocket*>(sender())) { // 获取触发的客户端
        QByteArray data = client->readAll();    // 读取全部可用数据
        QString message = QString::fromUtf8(data);  // 按 UTF-8转字符串

        QString timestamp = QDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss"); // 记录时间
        QString logEntry = QStringLiteral("\n[%1] Received:%2\n").arg(timestamp, message);  // 拼接日志
        appendColorLog(logEntry, QColor(0x666666));

        QString response = "Server response: " + message;   // 回显字符串
        client->write(response.toUtf8());   // 发送客户端
    }
}

// 保存所有日志
void FormTcpServer::saveLog()
{

}










































