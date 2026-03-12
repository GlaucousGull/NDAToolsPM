/********************************************************************************
** Form generated from reading UI file 'formchilddatavalidation.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCHILDDATAVALIDATION_H
#define UI_FORMCHILDDATAVALIDATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormChildDataValidation
{
public:
    QGroupBox *groupBox;
    QLabel *label_inputInfo;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit_crc16;
    QLineEdit *lineEdit_crc32;
    QLabel *label_4;
    QLineEdit *lineEdit_md5;
    QLabel *label_5;
    QLineEdit *lineEdit_sha1;
    QLabel *label_6;
    QLineEdit *lineEdit_sha256;
    QGroupBox *groupBox_3;
    QTextEdit *textEdit_inputText;
    QPushButton *pushButton_calculateCheckSums;
    QPushButton *pushButton_copyCheckSums;
    QCheckBox *checkBox_upperCaseCheck;

    void setupUi(QWidget *FormChildDataValidation)
    {
        if (FormChildDataValidation->objectName().isEmpty())
            FormChildDataValidation->setObjectName("FormChildDataValidation");
        FormChildDataValidation->resize(880, 540);
        groupBox = new QGroupBox(FormChildDataValidation);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 0, 871, 521));
        label_inputInfo = new QLabel(groupBox);
        label_inputInfo->setObjectName("label_inputInfo");
        label_inputInfo->setGeometry(QRect(690, 10, 141, 31));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 250, 851, 261));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 41, 31));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 41, 31));
        lineEdit_crc16 = new QLineEdit(groupBox_2);
        lineEdit_crc16->setObjectName("lineEdit_crc16");
        lineEdit_crc16->setGeometry(QRect(50, 20, 791, 31));
        lineEdit_crc32 = new QLineEdit(groupBox_2);
        lineEdit_crc32->setObjectName("lineEdit_crc32");
        lineEdit_crc32->setGeometry(QRect(50, 70, 791, 31));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 120, 41, 21));
        lineEdit_md5 = new QLineEdit(groupBox_2);
        lineEdit_md5->setObjectName("lineEdit_md5");
        lineEdit_md5->setGeometry(QRect(50, 120, 791, 31));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 41, 31));
        lineEdit_sha1 = new QLineEdit(groupBox_2);
        lineEdit_sha1->setObjectName("lineEdit_sha1");
        lineEdit_sha1->setGeometry(QRect(50, 170, 791, 31));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 220, 41, 31));
        lineEdit_sha256 = new QLineEdit(groupBox_2);
        lineEdit_sha256->setObjectName("lineEdit_sha256");
        lineEdit_sha256->setGeometry(QRect(50, 220, 791, 31));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 0, 851, 251));
        textEdit_inputText = new QTextEdit(groupBox_3);
        textEdit_inputText->setObjectName("textEdit_inputText");
        textEdit_inputText->setGeometry(QRect(10, 20, 831, 181));
        pushButton_calculateCheckSums = new QPushButton(groupBox_3);
        pushButton_calculateCheckSums->setObjectName("pushButton_calculateCheckSums");
        pushButton_calculateCheckSums->setGeometry(QRect(10, 210, 101, 31));
        pushButton_copyCheckSums = new QPushButton(groupBox_3);
        pushButton_copyCheckSums->setObjectName("pushButton_copyCheckSums");
        pushButton_copyCheckSums->setGeometry(QRect(160, 210, 101, 31));
        checkBox_upperCaseCheck = new QCheckBox(groupBox_3);
        checkBox_upperCaseCheck->setObjectName("checkBox_upperCaseCheck");
        checkBox_upperCaseCheck->setGeometry(QRect(310, 210, 101, 31));
        groupBox_3->raise();
        label_inputInfo->raise();
        groupBox_2->raise();

        retranslateUi(FormChildDataValidation);

        QMetaObject::connectSlotsByName(FormChildDataValidation);
    } // setupUi

    void retranslateUi(QWidget *FormChildDataValidation)
    {
        FormChildDataValidation->setWindowTitle(QCoreApplication::translate("FormChildDataValidation", "Form", nullptr));
        groupBox->setTitle(QString());
        label_inputInfo->setText(QCoreApplication::translate("FormChildDataValidation", "\345\255\227\347\254\246\346\225\260\357\274\2320\357\274\214\345\255\227\350\212\202\346\225\260\357\274\2320", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FormChildDataValidation", "\346\240\241\351\252\214\345\200\274\347\273\223\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("FormChildDataValidation", "CRC16", nullptr));
        label_3->setText(QCoreApplication::translate("FormChildDataValidation", "CRC32", nullptr));
        label_4->setText(QCoreApplication::translate("FormChildDataValidation", "MD5", nullptr));
        label_5->setText(QCoreApplication::translate("FormChildDataValidation", "SHA1", nullptr));
        label_6->setText(QCoreApplication::translate("FormChildDataValidation", "SHA256\357\274\232", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("FormChildDataValidation", "\350\276\223\345\205\245\346\225\260\346\215\256", nullptr));
        pushButton_calculateCheckSums->setText(QCoreApplication::translate("FormChildDataValidation", "\350\256\241\347\256\227\346\240\241\351\252\214\345\200\274", nullptr));
        pushButton_copyCheckSums->setText(QCoreApplication::translate("FormChildDataValidation", "\345\244\215\345\210\266\346\211\200\346\234\211\346\240\241\351\252\214\345\200\274", nullptr));
        checkBox_upperCaseCheck->setText(QCoreApplication::translate("FormChildDataValidation", "\345\244\247\345\206\231\346\230\276\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormChildDataValidation: public Ui_FormChildDataValidation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCHILDDATAVALIDATION_H
