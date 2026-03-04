/********************************************************************************
** Form generated from reading UI file 'formudpserver.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUDPSERVER_H
#define UI_FORMUDPSERVER_H

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

class Ui_FormUdpServer
{
public:
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_5;
    QPushButton *pushButton_UDPServerClose;
    QPushButton *pushButton_UDPServerSendMsg;
    QPushButton *pushButton_UDPServerStop;
    QPushButton *pushButton_UDPServerStart;
    QSpinBox *spinBox_UDPServerPort;
    QLabel *label_2;
    QComboBox *comboBox_UDPServerIP;
    QLabel *label;
    QGroupBox *groupBox;
    QListWidget *listWidget_UDPServerListMsg;

    void setupUi(QWidget *FormUdpServer)
    {
        if (FormUdpServer->objectName().isEmpty())
            FormUdpServer->setObjectName("FormUdpServer");
        FormUdpServer->resize(904, 564);
        groupBox_2 = new QGroupBox(FormUdpServer);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(690, 0, 201, 551));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(10, 380, 181, 91));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 350, 151, 31));
        pushButton_UDPServerClose = new QPushButton(groupBox_2);
        pushButton_UDPServerClose->setObjectName("pushButton_UDPServerClose");
        pushButton_UDPServerClose->setGeometry(QRect(10, 300, 181, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/exit.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_UDPServerClose->setIcon(icon);
        pushButton_UDPServerSendMsg = new QPushButton(groupBox_2);
        pushButton_UDPServerSendMsg->setObjectName("pushButton_UDPServerSendMsg");
        pushButton_UDPServerSendMsg->setGeometry(QRect(10, 490, 181, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/sendmsg.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_UDPServerSendMsg->setIcon(icon1);
        pushButton_UDPServerStop = new QPushButton(groupBox_2);
        pushButton_UDPServerStop->setObjectName("pushButton_UDPServerStop");
        pushButton_UDPServerStop->setGeometry(QRect(10, 230, 181, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/images/stop.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_UDPServerStop->setIcon(icon2);
        pushButton_UDPServerStart = new QPushButton(groupBox_2);
        pushButton_UDPServerStart->setObjectName("pushButton_UDPServerStart");
        pushButton_UDPServerStart->setGeometry(QRect(10, 160, 181, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/images/start.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_UDPServerStart->setIcon(icon3);
        spinBox_UDPServerPort = new QSpinBox(groupBox_2);
        spinBox_UDPServerPort->setObjectName("spinBox_UDPServerPort");
        spinBox_UDPServerPort->setGeometry(QRect(10, 100, 181, 31));
        spinBox_UDPServerPort->setMinimum(0);
        spinBox_UDPServerPort->setMaximum(65535);
        spinBox_UDPServerPort->setValue(12345);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 71, 16));
        comboBox_UDPServerIP = new QComboBox(groupBox_2);
        comboBox_UDPServerIP->addItem(QString());
        comboBox_UDPServerIP->setObjectName("comboBox_UDPServerIP");
        comboBox_UDPServerIP->setGeometry(QRect(10, 40, 181, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 71, 20));
        groupBox = new QGroupBox(FormUdpServer);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 681, 551));
        listWidget_UDPServerListMsg = new QListWidget(groupBox);
        listWidget_UDPServerListMsg->setObjectName("listWidget_UDPServerListMsg");
        listWidget_UDPServerListMsg->setGeometry(QRect(10, 20, 661, 521));

        retranslateUi(FormUdpServer);

        QMetaObject::connectSlotsByName(FormUdpServer);
    } // setupUi

    void retranslateUi(QWidget *FormUdpServer)
    {
        FormUdpServer->setWindowTitle(QCoreApplication::translate("FormUdpServer", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FormUdpServer", "\347\275\221\347\273\234\345\217\202\346\225\260\350\256\276\347\275\256\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("FormUdpServer", "\346\265\213\350\257\225\346\266\210\346\201\257\357\274\232", nullptr));
        pushButton_UDPServerClose->setText(QCoreApplication::translate("FormUdpServer", "\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
        pushButton_UDPServerSendMsg->setText(QCoreApplication::translate("FormUdpServer", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        pushButton_UDPServerStop->setText(QCoreApplication::translate("FormUdpServer", "\345\205\263\351\227\255\347\233\221\345\220\254", nullptr));
        pushButton_UDPServerStart->setText(QCoreApplication::translate("FormUdpServer", "\345\220\257\345\212\250\347\233\221\345\220\254", nullptr));
        label_2->setText(QCoreApplication::translate("FormUdpServer", "\346\234\254\345\234\260\344\270\273\346\234\272\347\253\257\345\217\243\357\274\232", nullptr));
        comboBox_UDPServerIP->setItemText(0, QCoreApplication::translate("FormUdpServer", "127.0.0.1", nullptr));

        label->setText(QCoreApplication::translate("FormUdpServer", "\346\234\254\345\234\260\344\270\273\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FormUdpServer", "\346\234\215\345\212\241\345\231\250\346\266\210\346\201\257\345\210\227\350\241\250\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormUdpServer: public Ui_FormUdpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUDPSERVER_H
