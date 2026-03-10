#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // 注册SocketError类型（包含警告中的多余括号，匹配Qt的识别）
    // qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
#if 1
    // 开启信号槽调试：连接失败会输出详细原因
    qputenv("QT_DEBUG_PLUGINS", "0"); // 关闭插件调试（避免干扰）
    qSetMessagePattern("%{time} %{type} %{message}");
    qInstallMessageHandler(nullptr); // 恢复默认日志处理器

    // 关键：开启信号槽连接调试
    qDebug() << "=== 信号槽连接调试开启 ===";
    QApplication a(argc, argv);
#endif
    MainWidget w;
    w.show();
    return a.exec();
}
