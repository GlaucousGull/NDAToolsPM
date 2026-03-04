/********************************************************************************
** Form generated from reading UI file 'formtcpserver.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTCPSERVER_H
#define UI_FORMTCPSERVER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTcpServer
{
public:
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_5;
    QPushButton *pushButton_TCPServerClose;
    QPushButton *pushButton_TCPServerSendMsg;
    QPushButton *pushButton_TCPServerStop;
    QPushButton *pushButton_TCPServerStart;
    QSpinBox *spinBox_TCPServerPort;
    QLabel *label_2;
    QComboBox *comboBox_TCPServerIP;
    QLabel *label;
    QListWidget *listWidget_TCPServerListMsg;
    QGroupBox *groupBox;

    void setupUi(QWidget *FormTcpServer)
    {
        if (FormTcpServer->objectName().isEmpty())
            FormTcpServer->setObjectName("FormTcpServer");
        FormTcpServer->resize(904, 564);
        groupBox_2 = new QGroupBox(FormTcpServer);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(690, 0, 201, 551));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(10, 380, 181, 91));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 350, 151, 31));
        pushButton_TCPServerClose = new QPushButton(groupBox_2);
        pushButton_TCPServerClose->setObjectName("pushButton_TCPServerClose");
        pushButton_TCPServerClose->setGeometry(QRect(10, 300, 181, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/exit.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPServerClose->setIcon(icon);
        pushButton_TCPServerSendMsg = new QPushButton(groupBox_2);
        pushButton_TCPServerSendMsg->setObjectName("pushButton_TCPServerSendMsg");
        pushButton_TCPServerSendMsg->setGeometry(QRect(10, 490, 181, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/sendmsg.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPServerSendMsg->setIcon(icon1);
        pushButton_TCPServerStop = new QPushButton(groupBox_2);
        pushButton_TCPServerStop->setObjectName("pushButton_TCPServerStop");
        pushButton_TCPServerStop->setGeometry(QRect(10, 230, 181, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/images/stop.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPServerStop->setIcon(icon2);
        pushButton_TCPServerStart = new QPushButton(groupBox_2);
        pushButton_TCPServerStart->setObjectName("pushButton_TCPServerStart");
        pushButton_TCPServerStart->setGeometry(QRect(10, 160, 181, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/images/start.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPServerStart->setIcon(icon3);
        spinBox_TCPServerPort = new QSpinBox(groupBox_2);
        spinBox_TCPServerPort->setObjectName("spinBox_TCPServerPort");
        spinBox_TCPServerPort->setGeometry(QRect(10, 100, 181, 31));
        spinBox_TCPServerPort->setMinimum(0);
        spinBox_TCPServerPort->setMaximum(65535);
        spinBox_TCPServerPort->setValue(12345);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 71, 16));
        comboBox_TCPServerIP = new QComboBox(groupBox_2);
        comboBox_TCPServerIP->addItem(QString());
        comboBox_TCPServerIP->setObjectName("comboBox_TCPServerIP");
        comboBox_TCPServerIP->setGeometry(QRect(10, 40, 181, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 71, 20));
        listWidget_TCPServerListMsg = new QListWidget(FormTcpServer);
        listWidget_TCPServerListMsg->setObjectName("listWidget_TCPServerListMsg");
        listWidget_TCPServerListMsg->setGeometry(QRect(10, 20, 661, 521));
        groupBox = new QGroupBox(FormTcpServer);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 681, 551));
        groupBox->raise();
        groupBox_2->raise();
        listWidget_TCPServerListMsg->raise();

        retranslateUi(FormTcpServer);

        QMetaObject::connectSlotsByName(FormTcpServer);
    } // setupUi

    void retranslateUi(QWidget *FormTcpServer)
    {
        FormTcpServer->setWindowTitle(QCoreApplication::translate("FormTcpServer", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FormTcpServer", "\347\275\221\347\273\234\345\217\202\346\225\260\350\256\276\347\275\256\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("FormTcpServer", "\346\265\213\350\257\225\346\266\210\346\201\257\357\274\232", nullptr));
        pushButton_TCPServerClose->setText(QCoreApplication::translate("FormTcpServer", "\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
        pushButton_TCPServerSendMsg->setText(QCoreApplication::translate("FormTcpServer", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        pushButton_TCPServerStop->setText(QCoreApplication::translate("FormTcpServer", "\345\205\263\351\227\255\347\233\221\345\220\254", nullptr));
        pushButton_TCPServerStart->setText(QCoreApplication::translate("FormTcpServer", "\345\220\257\345\212\250\347\233\221\345\220\254", nullptr));
        label_2->setText(QCoreApplication::translate("FormTcpServer", "\346\234\254\345\234\260\344\270\273\346\234\272\347\253\257\345\217\243\357\274\232", nullptr));
        comboBox_TCPServerIP->setItemText(0, QCoreApplication::translate("FormTcpServer", "127.0.0.1", nullptr));

        label->setText(QCoreApplication::translate("FormTcpServer", "\346\234\254\345\234\260\344\270\273\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FormTcpServer", "\346\234\215\345\212\241\345\231\250\346\266\210\346\201\257\345\210\227\350\241\250\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormTcpServer: public Ui_FormTcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTCPSERVER_H
