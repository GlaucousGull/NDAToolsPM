/********************************************************************************
** Form generated from reading UI file 'formudpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUDPCLIENT_H
#define UI_FORMUDPCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormUdpClient
{
public:
    QGroupBox *groupBox;
    QPlainTextEdit *plainTextEdit_UDPClientMsg;
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit_UDPServerSendData;
    QLabel *label_5;
    QPushButton *pushButton_UDPClientSendMsg;
    QSpinBox *spinBox_UDPClientPort;
    QLabel *label_2;
    QComboBox *comboBox_UDPClientIP;
    QLabel *label;
    QPushButton *pushButton_UDPClientClose;

    void setupUi(QWidget *FormUdpClient)
    {
        if (FormUdpClient->objectName().isEmpty())
            FormUdpClient->setObjectName("FormUdpClient");
        FormUdpClient->resize(888, 554);
        groupBox = new QGroupBox(FormUdpClient);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 681, 551));
        plainTextEdit_UDPClientMsg = new QPlainTextEdit(groupBox);
        plainTextEdit_UDPClientMsg->setObjectName("plainTextEdit_UDPClientMsg");
        plainTextEdit_UDPClientMsg->setGeometry(QRect(10, 20, 661, 521));
        groupBox_2 = new QGroupBox(FormUdpClient);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(690, 0, 201, 551));
        plainTextEdit_UDPServerSendData = new QPlainTextEdit(groupBox_2);
        plainTextEdit_UDPServerSendData->setObjectName("plainTextEdit_UDPServerSendData");
        plainTextEdit_UDPServerSendData->setGeometry(QRect(10, 380, 181, 91));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 350, 151, 31));
        pushButton_UDPClientSendMsg = new QPushButton(groupBox_2);
        pushButton_UDPClientSendMsg->setObjectName("pushButton_UDPClientSendMsg");
        pushButton_UDPClientSendMsg->setGeometry(QRect(10, 490, 181, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/sendmsg.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_UDPClientSendMsg->setIcon(icon);
        spinBox_UDPClientPort = new QSpinBox(groupBox_2);
        spinBox_UDPClientPort->setObjectName("spinBox_UDPClientPort");
        spinBox_UDPClientPort->setGeometry(QRect(10, 100, 181, 31));
        spinBox_UDPClientPort->setMaximum(65535);
        spinBox_UDPClientPort->setValue(12345);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 80, 71, 16));
        comboBox_UDPClientIP = new QComboBox(groupBox_2);
        comboBox_UDPClientIP->addItem(QString());
        comboBox_UDPClientIP->setObjectName("comboBox_UDPClientIP");
        comboBox_UDPClientIP->setGeometry(QRect(10, 40, 181, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 71, 20));
        pushButton_UDPClientClose = new QPushButton(groupBox_2);
        pushButton_UDPClientClose->setObjectName("pushButton_UDPClientClose");
        pushButton_UDPClientClose->setGeometry(QRect(10, 160, 181, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/exit.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_UDPClientClose->setIcon(icon1);

        retranslateUi(FormUdpClient);

        QMetaObject::connectSlotsByName(FormUdpClient);
    } // setupUi

    void retranslateUi(QWidget *FormUdpClient)
    {
        FormUdpClient->setWindowTitle(QCoreApplication::translate("FormUdpClient", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FormUdpClient", "\345\256\242\346\210\267\347\253\257\346\266\210\346\201\257\345\210\227\350\241\250\357\274\232", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FormUdpClient", "\347\275\221\347\273\234\345\217\202\346\225\260\350\256\276\347\275\256\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("FormUdpClient", "\346\265\213\350\257\225\346\266\210\346\201\257\357\274\232", nullptr));
        pushButton_UDPClientSendMsg->setText(QCoreApplication::translate("FormUdpClient", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("FormUdpClient", "\350\277\234\347\250\213\344\270\273\346\234\272\347\253\257\345\217\243\357\274\232", nullptr));
        comboBox_UDPClientIP->setItemText(0, QCoreApplication::translate("FormUdpClient", "127.0.0.1", nullptr));

        label->setText(QCoreApplication::translate("FormUdpClient", "\350\277\234\347\250\213\344\270\273\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        pushButton_UDPClientClose->setText(QCoreApplication::translate("FormUdpClient", "\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormUdpClient: public Ui_FormUdpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUDPCLIENT_H
