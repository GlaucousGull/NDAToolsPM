#include "formtcpserver.h"
#include "ui_formtcpserver.h"

FormTcpServer::FormTcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTcpServer)
{
    ui->setupUi(this);
}

FormTcpServer::~FormTcpServer()
{
    delete ui;
}

void FormTcpServer::on_pushButton_TCPServerSendMsg_clicked()
{

}


void FormTcpServer::on_pushButton_TCPServerStop_clicked()
{

}


void FormTcpServer::on_pushButton_TCPServerClose_clicked()
{

}


void FormTcpServer::on_pushButton_TCPServerStart_clicked()
{

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
    connect(tcpServerSocket, &QTcpSocket::readyRead, this, &FormTcpServer::ClientDisconnectedFunc);  // 数据可读
    connect(tcpServerSocket, &QTcpSocket::disconnected, this, &FormTcpServer::ClientDisconnectedFunc);  // 数据可读

    QString strPort = QString::number(tcpServerSocket->peerPort());

    appendColorLog("\n[Prompt:New client connection.]\n", QColor(0xFF666666)); // 记录连接日志

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
    appendColorLog(msg, QColor(0xFF666666));
}

// 功能读取所有可用数据并计数、展示日志
void FormTcpServer::ReadAllDataFunc()
{
    if(QTcpSocket* client = qobject_cast<QTcpSocket*>(sender())) { // 获取触发的客户端
        QByteArray data = client->readAll();    // 读取全部可用数据
        QString message = QString::fromUtf8(data);  // 按 UTF-8转字符串

        QString timestamp = QDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss"); // 记录时间
        QString logEntry = QStringLiteral("\n[%1] Received:%2\n").arg(timestamp, message);  // 拼接日志
        appendColorLog(logEntry, QColor(0xFF666666));

        QString response = "Server response: " + message;   // 回显字符串
        client->write(response.toUtf8());   // 发送客户端
    }
}












































