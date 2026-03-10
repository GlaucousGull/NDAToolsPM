#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "formtcpclient.h"
#include "formtcpserver.h"
#include "formudpclient.h"
#include "formudpserver.h"

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

// 窗口关闭事件，保存所有子窗口的日志
void MainWidget::closeEvent(QCloseEvent* event)
{
    // // 保存TCP服务器日志
    // if(ui->tab_TCPServer) {
    //     ui->tab_TCPServer();
    // }

    // // 保存TCP客户端日志
    // if(ui->tab_TCPClient) {
    //     ui->tab_TCPClientr->saveLog();
    // }
    // // 保存UDP服务器日志
    // if(ui->tab_UDPServer) {
    //     ui->tab_UDPServer->saveLog();
    // }
    // // 保存UDP客户端日志
    // if(ui->tab_UDPClient) {
    //     ui->tab_UDPClient->saveLog();
    // }


}
