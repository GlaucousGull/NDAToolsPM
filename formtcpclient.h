#ifndef FORMTCPCLIENT_H
#define FORMTCPCLIENT_H

// TCP协议客户端界面类声明
// 主要职责：发起/断开TCP链接，发送消息，自动化测试切换，日志显示与裁剪

#include <QWidget>

#include <QMessageBox>          // 弹窗提示
#include <QRegularExpression>   // 正则校验
#include <QString>              // 文本处理
#include <QDateTime>            // 时间戳
#include <QSettings>            // 持久化最近配置
#include <QTextCursor>          // 文本光标
#include <QPlainTextEdit>       // 纯文本编辑框
#include <QFile>                // 文件操作
#include <QTextStream>          // 文本流
#include <QCloseEvent>          // 关闭事件

#include <QStandardPaths>       // 获取配置文件目录
#include <QDir>                 // 目录操作

#include "network.h"           // 自定义网络通信封装（连接/收发）
#include "errorhandler.h"       // 统一错误处理/提示
#include "inputvalidator.h"     // 输入校验工具（IP/端口等）

namespace Ui {
class FormTcpClient;
}

class FormTcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit FormTcpClient(QWidget *parent = nullptr);
    ~FormTcpClient();

private slots:
    // 发送连接：验证IP/端口，保存最近配置并请求连接
    void on_pushButton_TCPClientConnect_clicked();

    // 断开连接：关闭socket并重置UI
    void on_pushButton_TCPClientDisconnect_clicked();

    // 关闭窗口/退出程序
    void on_pushButton_TCPClientClose_clicked();

    // 自动测试开关：勾选则启用定时发送，取消则恢复手动
    void on_checkBox_TCPClientAtuoTesting_checkStateChanged();

    // 发送消息：需要已连接并消息不能为空
    void on_pushButton_TCPClientSendMsg_clicked();

private:
    Ui::FormTcpClient *ui;

    bool connected = false; // 当前连接状态标记
    Network NetworkClient;  // 网通通信核心对象，封装socket行为

    void trimLog(int keepBlocks = 1000, int trimStep = 200);    // 日志裁剪：保留行数/超限删除步长
    bool checkIPAddrIsVaild(QString strIPAddress);              // IP合法性校验（保留旧接口）
    void enableCommunicationControls(bool enable);               // 批量控制与连接相关的UI

    void closeEvent(QCloseEvent* event) override;               // 窗口关闭事件，保存日志并接受关闭

public:
    // 保存日志文本到文件
    void savePlainTextEditToFile(QPlainTextEdit* plainTextEdit);

    // 保存日志
    void saveLog();
};

#endif // FORMTCPCLIENT_H
