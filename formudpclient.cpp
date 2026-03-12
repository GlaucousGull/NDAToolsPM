#include "formudpclient.h"
#include "ui_formudpclient.h"

FormUdpClient::FormUdpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormUdpClient)
{
    ui->setupUi(this);

    // 下拉框控件可编辑
    ui->comboBox_UDPClientIP->setEditable(true);

    // 固定窗口大小
    setFixedSize(width(), height());

    // 发送数据编辑框控件预设默认文本，便于快速测试
    ui->plainTextEdit_UDPServerSendData->setPlainText("hello UDP Server");

    // 日志列表设为制度，避免用户更改，并显示提示文字引导操作
    ui->plainTextEdit_UDPClientMsg->setReadOnly(true);
    ui->plainTextEdit_UDPClientMsg->setPlainText("Prompt: please enter data and click to send test.");

    ui->plainTextEdit_UDPClientMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->plainTextEdit_UDPServerSendData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->pushButton_UDPClientSendMsg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->label_5->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->label_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->groupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->groupBox_2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

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

    // 设置发送按钮上图标的显示尺寸
    ui->pushButton_UDPClientSendMsg->setIconSize(QSize(16, 16));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);  // Qt5:启动高DPI缩放
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);  // Qt5:启动高DPI位图
#endif


    {
        // 恢复最近一次连接的 IP/端口
        QSettings settings;  // 使用默认组织/应用存储
        const QString lastIp = settings.value("UDPClient/lastIp", "127.0.0.1").toString();
        const int lastPort = settings.value("UDPClient/lastPort", ui->spinBox_UDPClientPort->value()).toInt();


        int index = ui->comboBox_UDPClientIP->findText(lastIp); // 查找下拉是否已有改IP
        if(index >= 0) {
            ui->comboBox_UDPClientIP->setCurrentIndex(index);   // 已存在则选中
        }else {
            ui->comboBox_UDPClientIP->setCurrentIndex(index);   // 不存在则直接填入可编辑框
        }

        if(lastPort >=  ui->spinBox_UDPClientPort->minimum()    // 检验端口在允许范围内
            && lastPort <= ui->spinBox_UDPClientPort->maximum()) {
            ui->spinBox_UDPClientPort->setValue(lastPort);  // 恢复端口
        }
    }
}

FormUdpClient::~FormUdpClient()
{
    qDebug() << "FormUdpClient::~FormUdpClient 析构函数开始";
    try {
        if(UDPClientSocket) {
            qDebug() << "正在关闭UDP客户端套接字...";

            UDPClientSocket->disconnect();
            UDPClientSocket->close();

            // 将父对象置空，避免delete时Qt父子关系导致重复删除或异常
            UDPClientSocket->setParent(nullptr);
            delete UDPClientSocket;
            UDPClientSocket = nullptr;
            qDebug() << "UDP客户端套接字已关闭";
        }else {
            qDebug() << "UDP客户端套接字为空";
        }
        if(ui) {
            qDebug() << "UI正在删除....";
            delete ui;
            ui = nullptr;
            qDebug() << "UI已删除";
        }

    }catch(const std::exception& e){
        qWarning() << "FormUdpClient::~FormUdpClient 析构时发生异常：" << e.what();
    }catch(...) {
        qWarning() << "FormUdpClient::~FormUdpClient 析构时发生未知异常";

    }

    qDebug() << "FormUdpClient::~FormUdpClient 析构函数结束";
}

// 发送消息槽函数：懒创建UDP套接字并连接readyRead：校验IP/端口，编码为UTF-8发送数据
// 保存本次IP/端口到QSettings：在日志框追加发送记录并执行trimLog
void FormUdpClient::on_pushButton_UDPClientSendMsg_clicked()
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    // 判断socket是否初始化
    if(!UDPClientSocket) {
        // 套接字为初始化创建，即可开始初始化工作
        UDPClientSocket = new QUdpSocket(this);
        connect(UDPClientSocket, &QUdpSocket::readyRead, this, &FormUdpClient::ReadSeverDatagramFunc);
        socketReady = true;
    }

    // 读取用户输入的IP和端口
    QString strIpAddress = ui->comboBox_UDPClientIP->currentText();
    int port = ui->spinBox_UDPClientPort->value();

    // 使用InputValidator校验ip/端口，非法则弹出窗口警告
    auto ipValidation = InputValidator::validatorIPAddress(strIpAddress);
    if(!ipValidation.isValid) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, ipValidation.errorMessage, this);
        return;
    }

    //
    if(port < 1 || port > 65535) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "端口需要在1-65535范围内", this);
    }

    // 将字符串转化为QHostAddress
    QHostAddress hostAddress(strIpAddress);
    if(hostAddress.isNull() || hostAddress.protocol() != QAbstractSocket::IPv4Protocol) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "无效的IP地址", this);
        return;
    }

    // 获取发送框控件内容并去除收首位空白，空白内容不允许发送
    QString message = ui->plainTextEdit_UDPServerSendData->toPlainText().trimmed();
    if(message.isEmpty()) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "发送内容不能为空", this);
        return;
    }

    // 防御性检查
    if(!UDPClientSocket) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning, "UDP套接字未初始化", this);
        return;
    }

    //将QString转化为UTF-8字节数组，并调用writeDatagram发送到指定地址和窗口
    QByteArray data = message.toUtf8();
    qint64 bytesWriteen = UDPClientSocket->writeDatagram(data, hostAddress, port);
    if(bytesWriteen < 0) {
        HANDLE_ERROR(ErrorHandler::ValidationError, ErrorHandler::Warning,
                     QString("发送失败：%1").arg(UDPClientSocket->errorString()), this);
        return;
    }

    // 将本次使用的IP和端口写入QSettings，下次打开界面时自动恢复
    {
        QSettings settings;
        settings.setValue("UDPClient/lastIp", strIpAddress);
        settings.setValue("UDPClient/lastPort", static_cast<int>(port));
        settings.sync();
    }

    // 在日志列表追加一行
    ui->plainTextEdit_UDPClientMsg->appendPlainText(QString("\n%1\nSending：%2").arg(timestamp, message));

    trimLog();
}

// 日志裁剪
void FormUdpClient::trimLog(int keepBlocks, int trimStep)
{
    static const int kKeepDefault = 1000;       //默认保留数
    static const int kTrimDefault = 200;        // 默认删除步长
    const int targetKeep = keepBlocks > 0 ? keepBlocks : kKeepDefault;  // 获取实际bolck数
    const int step = trimStep > 0 ? trimStep : kTrimDefault;    // 获取实际步长

    auto doc = ui->plainTextEdit_UDPClientMsg->document();   //获取文档对象
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

// 窗口关闭时保存日志并接受关闭
void FormUdpClient::closeEvent(QCloseEvent* event)
{
    saveLog();
    event->accept();
}

// 将指定QPlainTextEdit的全部日志记录到文本文件中，追加模式，UTF-8
void FormUdpClient::savePlainTextEditToFile(QPlainTextEdit* plainTextEdit)
{
    if(!plainTextEdit) {
        qWarning() << "FormUdpClient::savePlainTextEditToFile: plainTextEdit = null";
    }

    // 获取配置文件所在目录（与QSetstrings配置文件同一目录）
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath); // 确保目录存在

    // 使用固定文件名，追加模式
    QString filename = QDir(appDataPath).filePath("UDPClientLogFile.txt");

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

// 保存当前界面日志到文件
void FormUdpClient::saveLog()
{
    if(ui && ui->plainTextEdit_UDPClientMsg) {
        savePlainTextEditToFile(ui->plainTextEdit_UDPClientMsg);
    }
}

// 读取服务器返回的数据报并加载到日志框，有readyRead信号除法
void FormUdpClient::ReadSeverDatagramFunc()
{
    if(!UDPClientSocket) {
        return;
    }

    // 循环处理缓冲区中所有等待读取的数据报，直到没有更多数据
    while(UDPClientSocket->hasPendingDatagrams()) {
        // 获取当前队首数据报的大小，用于预分配缓冲区
        qint64 datagramSize = UDPClientSocket->pendingDatagramSize();
        if(datagramSize <= 0) {
            break;
        }

        // 分配大块内存，用于接收数据，并准备接接收发送方的地址与端口
        QByteArray data;
        data.resize(datagramSize);
        QHostAddress senderAddress;
        quint16 senderPort = 0;

        // 从套接字读取一个数据报到data，并可选地得到发送方地址与端口
        qint64 bytesRead = UDPClientSocket->readDatagram(data.data(), data.size(), &senderAddress, &senderPort);

        if(bytesRead < -1) {
            qWarning() << "读取UDP数据报失败：" << UDPClientSocket->errorString();
            continue;
        }

        // 若实际读取字节数小于预分配大小，缩小data避免末尾未初始化数据参与解码
        if(bytesRead < datagramSize) {
            data.resize(bytesRead);
        }

        // 生成当前时间戳：并按UTF-8将数据解码为QString
        QString timestamp = QDateTime::currentDateTime().toString("yyyy=MM-dd hh:mm:ss");
        QString payload = QString::fromUtf8(data);

        // 在日志列表中日志
        ui->plainTextEdit_UDPClientMsg->appendPlainText(QString("\n%1\nReceive:%2").arg(timestamp, payload));
    }

    // 接收一批数据后统一做一次日志裁剪，防止块数过多导致的卡顿
    trimLog();

}

// 关闭按钮
void FormUdpClient::on_pushButton_UDPClientClose_clicked()
{
    savePlainTextEditToFile(ui->plainTextEdit_UDPClientMsg);
    QCoreApplication::quit();
}

