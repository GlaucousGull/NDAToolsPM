#include "Network.h"

// 构造函数：初始化网络客户端对象，创建套接字和定时器，建立信号槽
Network::Network(QObject *parent)
    : QObject{parent}
    // , socket(nullptr)
    , timer(nullptr)
    , testMessageCount(0)
    , autoTestMessage("")
    , receiveBuffer("")
    , performanceTimer()
    , bufferMutex()
{
    // 在堆上创建QTcpSocket对象
    socket = new QTcpSocket(this);

    // 在对上创建QTimer对象
    timer = new QTimer(this);

    // 为接收缓冲区预先分配空间
    receiveBuffer.reserve(8192);

    // 设置套接字选项
    setSocketOptions();

    // 处理建立信号槽连接
    connect(socket, &QTcpSocket::disconnected, this, &Network::ClientDisconnectFunc, Qt::QueuedConnection);
    connect(socket, &QTcpSocket::readyRead, this, &Network::ReadserverMsg, Qt::QueuedConnection);
    connect(socket, &QTcpSocket::connected, this, &Network::onConnected, Qt::QueuedConnection);

    // 旧式语法
    connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)), Qt::QueuedConnection);

    connect(timer, &QTimer::timeout, this, &Network::StartTimerOutFunc, Qt::DirectConnection);

    // 设置定时类型为精确定时器
    timer->setTimerType(Qt::PreciseTimer);

}

// 析构函数：清理资源，停止定时器并断开套接字连接
Network::~Network()
{
    qDebug() << "Network 析构函数开始";

    try {
        if(timer) {
            timer->stop();
            timer->disconnect();
        }
        if(socket) {
            socket->disconnect();
            if(socket->state() != QAbstractSocket::UnconnectedState) {
                socket->disconnectFromHost();
                if(socket->state() != QAbstractSocket::UnconnectedState) {
                    socket->abort();
                }
            }
        }

    }catch(const std::exception& e) {
        qDebug() << "Network 析构时发生异常" << e.what();
    }catch(...) {
        qDebug() << "Network 析构时发生未知异常";
    }

    qDebug() << "Network析构函数完成";
}

// 客户端连接到服务器：尝试建立TCP连接到指定的服务器和端口
bool Network::ClientConnectToServer(QString ServerIpAddress, int ServerPort)
{
    // 获取套接字当前状态：用于判断是否需要先断开已有连接
    QAbstractSocket::SocketState currentState = socket->state();    // 获取当前套接字状态

    // 检查套接字处于连接中或已连接状态，如果是，需要处理已有连接
    if(currentState == QAbstractSocket::ConnectingState || currentState == QAbstractSocket::ConnectedState) {
        // 检查是否已连接到相同的服务器地址和端口：如果相同则直接返回成功（复用已有连接）
        if(socket->peerAddress().toString() == ServerIpAddress
            && socket->peerPort() == ServerPort) {
            qDebug() << "alerady connected to" << ServerIpAddress << ":" << ServerPort;
            return true;
        }

        // 如果已径连接到不同的地址，先断开当前连接然后建立新连接
        qDebug() << "Disconnecting from current connection before connecting to new address";

        // 请求断开当前连接，优雅断开，等待未发送数据完成（异步操作）
        socket->disconnectFromHost();

        // 检查断开操作后的状态：如果仍未断开（可能在阻塞状态），强制中断
        if(socket->state() != QAbstractSocket::UnconnectedState) {
            socket->abort();    // 立即强制关闭套接字
        }
    }

    // 最终状态检查：确保套接字处于未连接状态才发起新连接
    if(socket->state() != QAbstractSocket::UnconnectedState) {
        qWarning() << "socket is not in unconnected state, aborting connenction";
        return false;   // 返回false，表示连接请求失败
    }

    // 发起连接：调用socket的connectToHost方法，尝试连接到指定的服务器地址和端口
    qDebug() << "connecting to" << ServerIpAddress << ":" << ServerPort;

    // 异步连接：connectToHost是异步操作，不会阻塞，连接结果通过connected或error0ccured信号通知
    socket->connectToHost(ServerIpAddress, ServerPort);

    // 返回成功：表示连接已经连接
    return true;
}

// 客户端发送文本消息到服务器：将UTF-8编码的字符串发送到服务器
void Network::ClientSendMsgToServer(const QString& StrData)
{
    // 验证套接字有效且处于已连接状态
    if(!socket || socket->state() != QAbstractSocket::ConnectedState) {
        // 套接字无效或未连接，输出警告信息并返回
        qWarning() << "socket not connected, cannot send data";
        return;
    }

    // 编码转换：将Unicode字符串(QString)转换为UTF-8编码的字节数组(QByteArray)
    QByteArray data = StrData.toUtf8();

    // 发送数据：将字节数组写入套接字，发送到服务器
    ClientSendBytesToServer(data);
}

// 客户端发送原始字节数据到服务器：直接发送字节数据，不进行编码转化
void Network::ClientSendBytesToServer(const QByteArray& data)
{
    // 验证套接字有效且处于已连接状态
    if(!socket || socket->state() != QAbstractSocket::ConnectedState) {
        // 套接字无效或未连接，输出警告信息并返回
        qWarning() << "socket not connected, cannot send data";
        return;
    }

    // 发送数据：将字节数组写入套接字，发送到服务器
    const qint64 bytesWriteLen = socket->write(data);

    // 第二次检查：判断数据是否写入失败
    if(bytesWriteLen < 0) {
        qWarning() << "write failed:" << socket->errorString();
        return;
    }

    // 成功写入数据，需要更新统计信息
    if(bytesWriteLen > 0) {
        QMutexLocker locker(&bufferMutex);  // 构造QMutexLocker对象，传入bufferMutex指针，自动加锁
        // 更新发送字节统计
        statisticalInformation.bytesSent += bytesWriteLen;
    }
}

// 设置套接字选项：配置TCP套接字的性能参数和连接参数
void Network::setSocketOptions()
{
    // 验证套接字指针是否有效
    if(!socket) {
        return;
    }

    // 设置低延迟
    socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    // 设置保活心跳
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);

    // 设置读取缓冲区大小：设置套接字内部读取缓冲区的大小（16KB）
    socket->setReadBufferSize(16384);

    // 设置发送缓冲区大小：设置套接字发送缓冲区的代下(32KB)
    socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 32768);

    // 设置接收缓冲区大小：设置套接字缓冲区的代销(32KB)
    socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 32768);
}

// 获取连接统计信息：返回当前连接的统计数据（只读访问）
Network::ConnectionsStats Network::getConnectionStats() const
{
    struct ConnectionsStats stats;
    return stats;
}

// 主动断开连接：由外部调用，主动断开与服务器TCP连接
void Network::DisconnectFromHost()
{
    // 验证套接字指针是否有效
    if(!timer) {
        qWarning() << "Network::DisconnectFromHost: timer is null";
        return;
    }

    // 请示断开连接
    socket->disconnectFromHost();
}

// 读取服务器消息：当socket有数据可读时自动调用
void Network::ReadserverMsg()
{
    // 验证套接字有效且处于已连接状态
    if(!socket || socket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << "socket not ready, skip read";
        return;
    }

    QMutexLocker locker(&bufferMutex);
    const qint64 bytesAvailable = socket->bytesAvailable(); // 获取缓冲区字节数

    // 验证是否有数据可读（数据有效性检查）
    if(bytesAvailable <= 0) {
        return;
    }

    static const qint64 kMaxBytes = 1024 * 1024;

    // 限流保护，丢弃超过阈值的数据包（防止内存溢出攻击）
    if(bytesAvailable > kMaxBytes) {
        qWarning() << "Too much incoming data, drop packet of size" << bytesAvailable;
        socket->read(bytesAvailable);
        return;
    }

    // 动态调整接收缓冲区容量：根据数据大小预分配内存，避免频繁重新分配
    if(receiveBuffer.capacity() < bytesAvailable) {
        // 扩展缓冲区容量
        receiveBuffer.reserve(bytesAvailable * 2);
    }

    // 读取所有可用数据
    receiveBuffer = socket->readAll();

    // 编码转换
    StrTempData = QString::fromUtf8(receiveBuffer);

    // 解锁
    locker.unlock();

    // 发出数据接收信号：通知外部对象已接收到数据，触发后续处理逻辑
    emit dataReceived(StrTempData);

#ifdef QT_DEBUG
    static qint64 totalBytesReceived = 0;
    totalBytesReceived += bytesAvailable;
    qDebug() << "Received" << bytesAvailable << "bytes. total:" << totalBytesReceived;
#endif
}

// 启动定时器超时功能：启动自动测试模式，定时向服务器发送测试消息
void Network::StartTimerOutFunc()
{
    // 验证套接字指针是否有效
    if(!socket) {
        qWarning() << "Network::StartTimerOutFunc: socket = null";
        return;
    }

    // 验证定时器指针是否有效
    if(!timer) {
        qWarning() << "Network::StartTimerOutFunc: timer = null";
        return;
    }

    // 验证套接字是否处于已连接状态
    if(socket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << "Network::StartTimerOutFunc: socket non connectedstate";
        timer->stop();
        return;
    }

    // 原子递增消息计数：线程安全的递增自动测试消息总集数，并获取递增前的只
    const int currentCount = testMessageCount.fetch_add(1);

    QString messageToSend;

    if(!autoTestMessage.isEmpty()) {
        messageToSend = autoTestMessage;
        if(messageToSend.contains("%1")) {  // 检查需要发送的消息字符串是否包含占位符
            messageToSend = messageToSend.arg(currentCount);    // 包含占位符，将占位符替换为当前实际消息数
        }
    }else {
        messageToSend = QStringLiteral("\n[Prompt:client automatic testing(%1)]").arg(currentCount);
    }

    // 发送消息到服务器
    ClientSendMsgToServer(messageToSend);

    // 确保定时器运行
    if(!timer->isActive()) {
        timer->start(1500);
    }
}

// 设置自动测试消息：设置自动测试模式下要发送的消息内容
void Network::setAutoTestMessage(const QString& message)
{
    autoTestMessage = message;

}

// 停止定时超时功能：停止自动测试模式，取消定时发送
void Network::StopTimerOutFunc()
{
    if(timer) { // 判空，避免野指针
        timer->stop(); // 关键：停止定时器（这是Qt官方的停止方法）
        qDebug() << "自动测试定时器已停止";
    }

    testMessageCount.store(0);  // 测试消息计数重置为 0
    performanceTimer.invalidate(); // 性能定时器失效（而非start，start是重启）
}

// 当客户端断开连接回调：当套接字断开时自动调用
void Network::ClientDisconnectFunc(void)
{
    // 验证套接字指针是否有效
    if(!timer) {
        qWarning() << "Network::ClientDisconnectFunc: timer is null";
        return;
    }

    // 停止自动测试定时器
    timer->stop();
}

// 连接建立回调：当socket成功连接到服务器时自动调用
void Network::onConnected()
{
    emit connectionEstablished();
}

// 套接字错误处理回调：当socket发生错误时自动调用
void Network::onSocketError(QAbstractSocket::SocketError error)
{
    QString errorString;
    switch (error) {
#define XX(item, description) \
    case item: \
        errorString = description; \
        break;

        XX(QAbstractSocket::ConnectionRefusedError, "连接被拒绝");
        XX(QAbstractSocket::RemoteHostClosedError, "远程主机关闭连接");
        XX(QAbstractSocket::HostNotFoundError, "主机未找到");
        XX(QAbstractSocket::SocketTimeoutError, "连接超时");
        XX(QAbstractSocket::NetworkError, "网络错误");
    default:
        errorString = socket->errorString();
        break;
    }

    emit connectionFailed(errorString);
}

























