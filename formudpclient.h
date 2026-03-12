#ifndef FORMUDPCLIENT_H
#define FORMUDPCLIENT_H

// UDP客户端界面类：FormUdpClient，用于向UDP服务器发送数据报
// 接受服务器响应：并在界面中记录、裁剪收发日志。UDP套接字采用懒创建模式

// Qt核心与网络
#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>

#include <QDateTime>
#include <QSettings>
#include <QTextCursor>
#include <QStandardPaths>
#include <QDir>

// 公共模块
#include "errorhandler.h"
#include "inputvalidator.h"

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class FormUdpClient;
}

class FormUdpClient : public QWidget
{
    Q_OBJECT

public:
    explicit FormUdpClient(QWidget *parent = nullptr);
    ~FormUdpClient();

private slots:
    // 发送消息
    void on_pushButton_UDPClientSendMsg_clicked();

    // 关闭按钮
    void on_pushButton_UDPClientClose_clicked();

private:
    // 套接字就绪标志
    bool socketReady = false;

    // 日志裁剪
    void trimLog(int keepBlocks = 1000, int trimStep = 200);

    // 窗口关闭时保存日志并接受关闭
    void closeEvent(QCloseEvent* event) override;

public:
    // 将指定QPlainTextEdit的全部日志记录到文本文件中，追加模式，UTF-8
    void savePlainTextEditToFile(QPlainTextEdit* plainTextEdit);

    // 保存当前界面日志到文件
    void saveLog();

    // UDP 客户端套接字指针，初始化为nullptr;
    QUdpSocket* UDPClientSocket = nullptr;

    // 发送目标地址缓存，可选用途
    QHostAddress* m_UDPClientHostAddrress;

public Q_SLOTS:
    // 读取服务器返回的数据报并加载到日志框，有readyRead信号除法
    void ReadSeverDatagramFunc();
private:
    Ui::FormUdpClient *ui;
};

#endif // FORMUDPCLIENT_H
