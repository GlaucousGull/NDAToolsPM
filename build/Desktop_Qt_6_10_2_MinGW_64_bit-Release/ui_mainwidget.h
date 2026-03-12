/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "formdataprocessor.h"
#include "formtcpclient.h"
#include "formtcpserver.h"
#include "formudpclient.h"
#include "formudpserver.h"

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    FormTcpServer *tab_TCPServer;
    FormTcpClient *tab_TCPClient;
    FormUdpServer *tab_UDPServer;
    FormUdpClient *tab_UDPClient;
    FormDataProcessor *tab_DataExchange;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(900, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/logo.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWidget->setWindowIcon(icon);
        centralwidget = new QWidget(MainWidget);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 961, 880));
        tab_TCPServer = new FormTcpServer();
        tab_TCPServer->setObjectName("tab_TCPServer");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/server.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tabWidget->addTab(tab_TCPServer, icon1, QString());
        tab_TCPClient = new FormTcpClient();
        tab_TCPClient->setObjectName("tab_TCPClient");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/images/client.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tabWidget->addTab(tab_TCPClient, icon2, QString());
        tab_UDPServer = new FormUdpServer();
        tab_UDPServer->setObjectName("tab_UDPServer");
        tabWidget->addTab(tab_UDPServer, icon1, QString());
        tab_UDPClient = new FormUdpClient();
        tab_UDPClient->setObjectName("tab_UDPClient");
        tabWidget->addTab(tab_UDPClient, icon2, QString());
        tab_DataExchange = new FormDataProcessor();
        tab_DataExchange->setObjectName("tab_DataExchange");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/images/sendmsg.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tabWidget->addTab(tab_DataExchange, icon3, QString());
        MainWidget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWidget);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 18));
        MainWidget->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWidget);
        statusbar->setObjectName("statusbar");
        MainWidget->setStatusBar(statusbar);

        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QMainWindow *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "TCP/UDP\345\215\217\350\256\256\347\275\221\347\273\234\350\260\203\350\257\225\345\212\251\346\211\213 v0.1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_TCPServer), QCoreApplication::translate("MainWidget", "TCP\346\234\215\345\212\241\345\231\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_TCPClient), QCoreApplication::translate("MainWidget", "TCP\345\256\242\346\210\267\347\253\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_UDPServer), QCoreApplication::translate("MainWidget", "UDP\346\234\215\345\212\241\345\231\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_UDPClient), QCoreApplication::translate("MainWidget", "UDP\345\256\242\346\210\267\347\253\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_DataExchange), QCoreApplication::translate("MainWidget", "\346\225\260\346\215\256\350\275\254\346\215\242\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
