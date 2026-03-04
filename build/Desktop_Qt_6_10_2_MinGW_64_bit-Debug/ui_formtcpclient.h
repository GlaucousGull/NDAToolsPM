/********************************************************************************
** Form generated from reading UI file 'formtcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTCPCLIENT_H
#define UI_FORMTCPCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTcpClient
{
public:
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_5;
    QPushButton *pushButton_TCPClientClose;
    QPushButton *pushButton_TCPClientSendMsg;
    QPushButton *pushButton_TCPClientDisconnect;
    QPushButton *pushButton_TCPClientConnect;
    QSpinBox *spinBox_TCPClientPort;
    QLabel *label_2;
    QComboBox *comboBox_TCPClientIP;
    QLabel *label;
    QCheckBox *checkBox_TCPClientAtuoTesting;
    QGroupBox *groupBox;
    QPlainTextEdit *plainTextEdit_TCPClientMsg;

    void setupUi(QWidget *FormTcpClient)
    {
        if (FormTcpClient->objectName().isEmpty())
            FormTcpClient->setObjectName("FormTcpClient");
        FormTcpClient->resize(904, 564);
        groupBox_2 = new QGroupBox(FormTcpClient);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(690, 0, 201, 551));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(10, 380, 181, 91));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 350, 151, 31));
        pushButton_TCPClientClose = new QPushButton(groupBox_2);
        pushButton_TCPClientClose->setObjectName("pushButton_TCPClientClose");
        pushButton_TCPClientClose->setGeometry(QRect(10, 300, 181, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/exit.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPClientClose->setIcon(icon);
        pushButton_TCPClientSendMsg = new QPushButton(groupBox_2);
        pushButton_TCPClientSendMsg->setObjectName("pushButton_TCPClientSendMsg");
        pushButton_TCPClientSendMsg->setGeometry(QRect(100, 490, 91, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/sendmsg.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPClientSendMsg->setIcon(icon1);
        pushButton_TCPClientDisconnect = new QPushButton(groupBox_2);
        pushButton_TCPClientDisconnect->setObjectName("pushButton_TCPClientDisconnect");
        pushButton_TCPClientDisconnect->setGeometry(QRect(10, 230, 181, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/images/disconnect.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPClientDisconnect->setIcon(icon2);
        pushButton_TCPClientConnect = new QPushButton(groupBox_2);
        pushButton_TCPClientConnect->setObjectName("pushButton_TCPClientConnect");
        pushButton_TCPClientConnect->setGeometry(QRect(10, 160, 181, 41));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/images/connect.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_TCPClientConnect->setIcon(icon3);
        spinBox_TCPClientPort = new QSpinBox(groupBox_2);
        spinBox_TCPClientPort->setObjectName("spinBox_TCPClientPort");
        spinBox_TCPClientPort->setGeometry(QRect(10, 100, 181, 31));
        spinBox_TCPClientPort->setMaximum(65535);
        spinBox_TCPClientPort->setValue(12345);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 71, 16));
        comboBox_TCPClientIP = new QComboBox(groupBox_2);
        comboBox_TCPClientIP->addItem(QString());
        comboBox_TCPClientIP->setObjectName("comboBox_TCPClientIP");
        comboBox_TCPClientIP->setGeometry(QRect(10, 40, 181, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 71, 20));
        checkBox_TCPClientAtuoTesting = new QCheckBox(groupBox_2);
        checkBox_TCPClientAtuoTesting->setObjectName("checkBox_TCPClientAtuoTesting");
        checkBox_TCPClientAtuoTesting->setGeometry(QRect(10, 490, 81, 31));
        groupBox = new QGroupBox(FormTcpClient);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 681, 551));
        plainTextEdit_TCPClientMsg = new QPlainTextEdit(groupBox);
        plainTextEdit_TCPClientMsg->setObjectName("plainTextEdit_TCPClientMsg");
        plainTextEdit_TCPClientMsg->setGeometry(QRect(10, 20, 661, 521));

        retranslateUi(FormTcpClient);

        QMetaObject::connectSlotsByName(FormTcpClient);
    } // setupUi

    void retranslateUi(QWidget *FormTcpClient)
    {
        FormTcpClient->setWindowTitle(QCoreApplication::translate("FormTcpClient", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FormTcpClient", "\347\275\221\347\273\234\345\217\202\346\225\260\350\256\276\347\275\256\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("FormTcpClient", "\346\265\213\350\257\225\346\266\210\346\201\257\357\274\232", nullptr));
        pushButton_TCPClientClose->setText(QCoreApplication::translate("FormTcpClient", "\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
        pushButton_TCPClientSendMsg->setText(QCoreApplication::translate("FormTcpClient", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        pushButton_TCPClientDisconnect->setText(QCoreApplication::translate("FormTcpClient", "\346\226\255\345\274\200\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_TCPClientConnect->setText(QCoreApplication::translate("FormTcpClient", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        label_2->setText(QCoreApplication::translate("FormTcpClient", "\350\277\234\347\250\213\344\270\273\346\234\272\347\253\257\345\217\243\357\274\232", nullptr));
        comboBox_TCPClientIP->setItemText(0, QCoreApplication::translate("FormTcpClient", "127.0.0.1", nullptr));

        label->setText(QCoreApplication::translate("FormTcpClient", "\350\277\234\347\250\213\344\270\273\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        checkBox_TCPClientAtuoTesting->setText(QCoreApplication::translate("FormTcpClient", "\350\207\252\345\212\250\345\214\226\346\265\213\350\257\225", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FormTcpClient", "\345\256\242\346\210\267\347\253\257\346\266\210\346\201\257\345\210\227\350\241\250\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormTcpClient: public Ui_FormTcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTCPCLIENT_H
