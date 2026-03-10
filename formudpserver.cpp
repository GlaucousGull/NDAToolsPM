#include "formudpserver.h"
#include "ui_formudpserver.h"

// 构造函数
FormUdpServer::FormUdpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormUdpServer)
{
    ui->setupUi(this);

    // 设置IP地址下拉框为可编辑
    ui->comboBox_UDPServerIP->setEditable(true);

    // 获取本机所有网络IP地址列表
    QList<QHostAddress> addressList = QNetworkInterface::allAddresses();

    // 创建IP地址字符串列表
    QStringList ipList;

    // 预分配列表容量
    ipList.reserve(addressList.size());

    for(const QHostAddress& address : addressList) {
        if(address.protocol() != QAbstractSocket::IPv4Protocol) {
            ipList.append(address.toString());
        }
    }

    // 批量添加IP地址到下拉框控件
    ui->comboBox_UDPServerIP->setUpdatesEnabled(false);

    ui->comboBox_UDPServerIP->addItems(ipList);

    ui->comboBox_UDPServerIP->setUpdatesEnabled(true);

    // 加载上次保存的配置：从QSettings 读取上次IP和端口
    {
        QSettings settings;
        const QString lastIp = settings.value("UDPServer/lastIp").toString();
        const int lastPort = settings.value("UDPServer/lastIp", 12345).toInt();

        // 恢复上次配置参数
        if(!lastIp.isEmpty()) {
            int index = ui->comboBox_UDPServerIP->findText(lastIp);
            if(index >= 0) {
                ui->comboBox_UDPServerIP->setCurrentIndex(index);
            }else {
                ui->comboBox_UDPServerIP->setEditText(lastIp);
            }
        }

        if(lastPort >= ui->spinBox_UDPServerPort->minimum()
        && lastPort <= ui->spinBox_UDPServerPort->maximum()) {
            ui->spinBox_UDPServerPort->setValue(lastPort);
        }
    }

    // 创建UDP服务器套接字
    udpServerSocket = new QUdpSocket(this);

    // 建立信号槽连接：将UDP套接字readyRead信号连接到数据读取槽函数
    connect(udpServerSocket, &QUdpSocket::readyRead, this, &FormUdpServer::udpServerREadPendingEDatagrams);

    // 控件固定尺寸策略
    ui->groupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->groupBox_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->listWidget_UDPServerListMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label_5->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->comboBox_UDPServerIP->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->spinBox_UDPServerPort->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_UDPServerClose->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_UDPServerStart->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if(ui->plainTextEdit_udpServerSendData) {
        ui->plainTextEdit_udpServerSendData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    if(ui->pushButton_UDPServerSendMsg) {
        ui->pushButton_UDPServerSendMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    // 设置列表控件属性：优化列表控件的显示和选择行为
    ui->listWidget_UDPServerListMsg->setUniformItemSizes(true);

    // 设置选项模式
    ui->listWidget_UDPServerListMsg->setSelectionMode(QAbstractItemView::SingleSelection);

    // 高DPI显示支持：为Qt5版本启动高DPI显示缩放和图标支持
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);  // Qt5:启动高DPI缩放
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);  // Qt5:启动高DPI位图
#endif
}

// 析构函数：清理资源，释放套接字和UI对象，确保资源正确释放
FormUdpServer::~FormUdpServer()
{
    qDebug() << "FormUdpServer::~FormUdpServer 析构函数开始";
    try {
        if(udpServerSocket) {
            udpServerSocket->disconnect();
            udpServerSocket->close();
            delete udpServerSocket;
            udpServerSocket = nullptr;
        }
        if(ui) {
            delete ui;
            ui = nullptr;
        }
    }catch(const std::exception& e) {
        qWarning() << "FormUdpServer::~FormUdpServer 析构发生异常";
    }catch(...) {
        qWarning() << "FormUdpServer::~FormUdpServer 析构发生未知异常";
    }
}

// 启动/停止服务器按钮点击事件：切换UDP服务器的监听状态
/* 处理流程
*  验证输入IP和端口的有效性
*  启动监听
*  停止监听
*  更行按钮文本和运行状态
*  保存配置到QSettrings
*/
void FormUdpServer::on_pushButton_UDPServerStart_clicked()
{
    // 获取用户输入的IP地址
    QString ipAddress = ui->comboBox_UDPServerIP->currentText();

    // 将 IP 地址字符串转换位QHostAddress对象，用于验证和绑定操作
    QHostAddress hostAddress(ipAddress);

    // 获取端口号
    quint16 port = ui->spinBox_UDPServerPort->value();

    // 判断当前按钮状态：根据按钮文本判断是启动还是停止操作
    if(ui->pushButton_UDPServerStart->text() == "启动监听") {
        // 启动监听：当前按钮更改为“启动监听”，启动服务器监听
qDebug() << "FormUdpServer::on_pushButton_UDPServerStart_clicked 函数调用";
        // 验证输入IP地址格式
        auto ipValidation = InputValidator::validatorNetworkAddress(ipAddress);
        if(!ipValidation.isValid) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, ipValidation.errorMessage, this);
            return;
        }
qDebug() << "FormUdpServer::on_pushButton_UDPServerStart_clicked 函数调用";
        // 验证QHostAddress对象是否有效且为IPv4协议
        if(hostAddress.isNull() || hostAddress.protocol() != QAbstractSocket::IPv4Protocol) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "无效的IP地址", this);
        }

        // 验证端口号是否在有效范围内
        if(port < 1 || port > 65535) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "端口号必须在1-65546范围内", this);
            return;
        }

        // 验证UDP套接字是否已初始化
        if(!udpServerSocket) {
            HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "UDP套接字未初始化", this);
            return;
        }

        // 绑定ip地址和端口
        if(udpServerSocket->bind(hostAddress, port)) {
            ui->pushButton_UDPServerStart->setText("关闭监听");
            udpServerAppendStrItem(1, "UDP服务器启动监听成功", false);
            serverRunning = false;
            QSettings settings;
            settings.setValue("UDPServer/lastIp", hostAddress.toString());
            settings.setValue("UDPServer/lastPort", static_cast<int>(port));

            // 同步到磁盘
            settings.sync();
        }else {
            // 绑定失败
            if(udpServerSocket) {
                HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, udpServerSocket->errorString(), this);
            }else {
                HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "UDP套接字未初始化", this);
            }
        }
    }else {
        // 停止监听：当前按钮文本为“停止监听”，需要停止服务器监听
        if(udpServerSocket) {
            udpServerSocket->abort();
        }

        // 更新按钮文本：将按钮文本改回“启动监听”，表示当前已停止，下次点击将启动
        ui->pushButton_UDPServerStart->setText("启动监听");

        // 追加状态日志
        udpServerAppendStrItem(1, "UDP服务器已停止监听", false);

        // 更新运行状态标志
        serverRunning = false;
    }

}

// 关闭按钮点击事件，保存日志并退出应用程序
void FormUdpServer::on_pushButton_UDPServerClose_clicked()
{
    // 保存日志到文件
    saveListWidgetToFile(ui->listWidget_UDPServerListMsg);

    // 退出应用程序
    QCoreApplication::quit();
}

// 发送测试消息按钮点击事件：向最近连接的客户端发送测试消息
/* 处理流程：
 * 验证套接字和服务器状态
 * 验证是否有客户端地址
 * 获取并验证消息内容
 * 编码消息并发送
 * 记录发送日志
 */
void FormUdpServer::on_pushButton_UDPServerSendMsg_clicked()
{
    // 验证UDP套接字是否已初始化
    if(!udpServerSocket) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "UDP套接字未初始化，无法发送数据。", this);
        return;
    }

    // 验证服务器是否正在运行
    if(!udpServerSocket) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "请先启动服务器，监听后才可发送消息", this);
        return;
    }

    // 验证是否有客户端地址信息
    if(!m_lastClientAddress .isNull() || m_lastClientPort == 0) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "当前没有收到任何客户端消息，无法确定发送地址", this);
        return;
    }

    // 验证输入框控件是否存在
    if(ui->plainTextEdit_udpServerSendData) {
        return;
    }

    QString message = ui->plainTextEdit_udpServerSendData->toPlainText().trimmed();

    if(message.isEmpty()) {
        QMessageBox::warning(this, "提示", "发送小心内容不能为空！");
        ui->plainTextEdit_udpServerSendData->setFocus();
        return;
    }

    QByteArray data = message.toUtf8();

    // 发送数据报到客户端
    qint64 bytes = udpServerSocket->writeDatagram(data, m_lastClientAddress, m_lastClientPort);

    if(bytes < 0) {
        QMessageBox::warning(this, "错误", QString("发送失败：%1").arg(udpServerSocket->errorString()));
        return;
    }

    // 记录发送日志
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // 构建日志条目
    QString logEntry = QString("\n[%1] 服务器发送到 %2:%3\%4\n")
                           .arg(timeStamp, m_lastClientAddress.toString())
                           .arg(m_lastClientPort)
                           .arg(message);

    // 添加日志项到列表
    ui->listWidget_UDPServerListMsg->addItem(logEntry);

    // 自动滚动到底部
    ui->listWidget_UDPServerListMsg->scrollToBottom();
}

// 读取并处理收到的数据报：当UDP套接字有数据可读时自动调用
void FormUdpServer::udpServerREadPendingEDatagrams()
{
    if(!serverRunning) {
        return;
    }

    if(!udpServerSocket) {
        qWarning() << "FormUDPServer::udpServerREadPendingEDatagrams: udpServerSocket is null";
        return;
    }

    while(udpServerSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        qint64 datagramSize = udpServerSocket->pendingDatagramSize();
        if(datagramSize <= 0) {
            break;  // 无效数据报大小，退出循环
        }

        datagram.resize(static_cast<int>(datagramSize));
        QHostAddress clientAddress;
        quint16 clientPort;

        qint64 bytesRead = udpServerSocket->readDatagram(datagram.data(),
                                                         datagram.size(), &clientAddress, &clientPort);
        if(bytesRead == -1) {
            qWarning() << "读取UDP数据报失败：" << udpServerSocket->errorString();
            continue;
        }

        m_lastClientAddress = clientAddress;
        m_lastClientPort = clientPort;

        udpServerAppendStrItem(0, QString::fromUtf8(datagram), false);

        QByteArray response = QString("[Server reply:%1").arg(QString::fromUtf8(datagram)).toUtf8();
        udpServerSocket->writeDatagram(response, clientAddress, clientPort);
    }
}

// 追加日志项到列表：将消息或状态信息追加到日志列表控件
void FormUdpServer::udpServerAppendStrItem(int type, const QString& strData, bool clear)
{
    Q_UNUSED(clear);

    QString timestamp = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    QString processedDate = strData;
    processedDate.replace("\r", "").replace("\n", "");

    QString logEntry = QString("\n[%1] %2\n%3\n")
                           .arg(timestamp, type == 0 ? "接收数据" : "服务器状态", processedDate);

    // 性能优化：批量更新UI
    ui->listWidget_UDPServerListMsg->setUpdatesEnabled(false);
    ui->listWidget_UDPServerListMsg->addItem(logEntry);
    trimLog();
    ui->listWidget_UDPServerListMsg->setUpdatesEnabled(true);

    // 自动滚动到底部，显示最新消息
    int lastRow = ui->listWidget_UDPServerListMsg->count() - 1;
    if(lastRow == 0) {
        QListWidgetItem* item = ui->listWidget_UDPServerListMsg->item(lastRow);
        if(item) {
            ui->listWidget_UDPServerListMsg->scrollToItem(item, QAbstractItemView::PositionAtBottom);
            ui->listWidget_UDPServerListMsg->setCurrentRow(lastRow);
        }
    }
}

// 日志裁剪函数：当日志列表项数超过阈值时，删除前部项以控制内存使用
void FormUdpServer::trimLog(int keepRows, int trimStep)
{
    static const int kKeepDefault = 1000;
    static const int kTrimDefault = 200;

    // 确定实际保留行数
    const int targetkeep = keepRows > 0 ? keepRows : kKeepDefault;
    const int step = trimStep > 0 ? trimStep : kTrimDefault;

    int count = ui->listWidget_UDPServerListMsg->count();

    if(count <= targetkeep + step) {
        return;
    }

    int removeCount = count - targetkeep;

    // 批量删除时禁用UI更新，减少重绘次数
    if(removeCount > 10) {
        ui->listWidget_UDPServerListMsg->setUpdatesEnabled(false);
        ui->listWidget_UDPServerListMsg->update(); // 手动触发一次重绘，展示最终结果
    }

    // 创建等待删除项列表：用于存储需要删除的列表项指针
    QList<QListWidgetItem*> itemsToDelete;

    // 遍历并移除前部项：从列表开头
    for(int i = 0; i < removeCount; i++) {
        QListWidgetItem* item = ui->listWidget_UDPServerListMsg->takeItem(0);
        if(item) {
            itemsToDelete.append(item);
        }
    }

    // 批量删除项对象：释放所有等待删除项占用的内存
    qDeleteAll(itemsToDelete);
}

// 窗口关闭事件处理函数：当窗口关闭时自动调用，保存日志并接收关闭
void FormUdpServer::closeEvent(QCloseEvent* event)
{
    // 保存日志
    saveLog();

    // 接受关闭事件：允许窗口关闭，窗口将正常关闭
    event->accept();
}


// 保存日志列表到文本文件：将QListWidget中的所有项保存到文件
void FormUdpServer::saveListWidgetToFile(QListWidget* listWidget)
{
    // ===== 步骤1：参数校验（核心前置）=====
    if(!listWidget) {
        qWarning() << "FormUdpServer::saveListWidgetToFile: listWidget is null";
        return;
    }

    // ===== 步骤2：构建日志文件路径（确保目录存在）=====
    // 获取应用程序可写的日志目录
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    // 确保目录存在（不存在则创建）
    QDir appDir;
    if(!appDir.mkpath(appDataPath)) {
        qWarning() << "FormUdpServer::saveListWidgetToFile: 无法创建日志目录：" << appDataPath;
        return;
    }
    // 拼接完整文件路径
    QString fileName = appDir.filePath("UDPServerLogfile.txt");

    // ===== 步骤3：确定文件打开模式（新建/追加）=====
    bool fileExists = QFile::exists(fileName);
    QIODevice::OpenMode openMode = QIODevice::Text; // 基础模式：文本模式
    if(fileExists) {
        openMode |= QIODevice::Append; // 文件存在：追加模式
    } else {
        openMode |= QIODevice::WriteOnly; // 文件不存在：新建写入模式
    }

    // ===== 步骤4：打开文件并写入内容（核心逻辑）=====
    QFile file(fileName);
    if(!file.open(openMode)) { // 打开失败直接返回
        qWarning() << "FormUdpServer::saveListWidgetToFile: 无法打开日志文件：" << file.errorString();
        return;
    }

    // 创建文本流并设置UTF-8编码（兼容Qt5/Qt6）
    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#else
    out.setEncoding(QStringConverter::Utf8);
#endif

    // ===== 步骤5：追加模式下写入分隔符（区分不同批次日志）=====
    if(fileExists) { // 只有追加模式才写分隔符
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        out << "\n==========" << timestamp << "==========";
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        out << endl; // Qt5：endl是函数，自动换行+刷新
#else
        out << Qt::endl; // Qt6：枚举常量，换行+刷新
#endif
    }

    // ===== 步骤6：遍历列表项，逐行写入文件 =====
    int itemCount = listWidget->count();
    if(itemCount == 0) {
        out << "当前无日志内容" << Qt::endl;
    } else {
        for(int i = 0; i < itemCount; ++i) {
            // 正确获取列表项文本（核心修复：itemWidget是自定义控件，item才是文本项）
            QListWidgetItem* item = listWidget->item(i);
            if(item && !item->text().isEmpty()) {
                out << item->text(); // 写入列表项文本
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                out << endl; // 每项换行
#else
                out << Qt::endl;
#endif
            }
        }
    }

    // ===== 步骤7：关闭文件（释放资源）=====
    file.close();
    qDebug() << "UDP服务器日志已保存到：" << fileName;

    // ===== 步骤8：弹窗提示（仅当窗口可见时）=====
    if(this->isVisible()) {
        QMessageBox::information(this, // 修复：Information → information（大小写错误）
                                 "成功",
                                 QString("日志已保存至 %1").arg(fileName));
    }else {
        // 文件打开是啊比：输出警告信息，记录错误原因
        qWarning() << "UDP服务器日志保存是啊比：" << file.errorString();

        // 显示错误信息框：如果窗口可见，显示错误提示
        if(this->isVisible()) {
            QMessageBox::critical(this, "错误", "保存失败：" + file.errorString());
        }
    }
}

// 保存日志函数：保存当前界面的日志列表到文件
void FormUdpServer::saveLog()
{
    // 检查UI对象和列表控件是否存在
    if(ui && ui->listWidget_UDPServerListMsg) {
        saveListWidgetToFile(ui->listWidget_UDPServerListMsg);
    }
}
