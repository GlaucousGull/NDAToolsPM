/********************************************************************************
** Form generated from reading UI file 'formchilddataconversion.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCHILDDATACONVERSION_H
#define UI_FORMCHILDDATACONVERSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormChildDataConversion
{
public:
    QGroupBox *groupBox;
    QComboBox *comboBox_conversionType;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit_inputText;
    QLabel *label_4;
    QLabel *label_outputInfo;
    QPushButton *pushButton_converOperator;
    QPushButton *pushButton_clearOperator;
    QPushButton *pushButton_swapOperator;
    QPushButton *pushButton_copyOperator;
    QTextEdit *textEdit_outputText;
    QLabel *label_inputInfo;

    void setupUi(QWidget *FormChildDataConversion)
    {
        if (FormChildDataConversion->objectName().isEmpty())
            FormChildDataConversion->setObjectName("FormChildDataConversion");
        FormChildDataConversion->resize(880, 540);
        groupBox = new QGroupBox(FormChildDataConversion);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 871, 511));
        comboBox_conversionType = new QComboBox(groupBox);
        comboBox_conversionType->setObjectName("comboBox_conversionType");
        comboBox_conversionType->setGeometry(QRect(70, 10, 141, 31));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 61, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 61, 31));
        textEdit_inputText = new QTextEdit(groupBox);
        textEdit_inputText->setObjectName("textEdit_inputText");
        textEdit_inputText->setGeometry(QRect(10, 80, 851, 181));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 260, 61, 31));
        label_outputInfo = new QLabel(groupBox);
        label_outputInfo->setObjectName("label_outputInfo");
        label_outputInfo->setGeometry(QRect(720, 260, 141, 31));
        pushButton_converOperator = new QPushButton(groupBox);
        pushButton_converOperator->setObjectName("pushButton_converOperator");
        pushButton_converOperator->setGeometry(QRect(10, 470, 81, 31));
        pushButton_clearOperator = new QPushButton(groupBox);
        pushButton_clearOperator->setObjectName("pushButton_clearOperator");
        pushButton_clearOperator->setGeometry(QRect(120, 470, 81, 31));
        pushButton_swapOperator = new QPushButton(groupBox);
        pushButton_swapOperator->setObjectName("pushButton_swapOperator");
        pushButton_swapOperator->setGeometry(QRect(230, 470, 81, 31));
        pushButton_copyOperator = new QPushButton(groupBox);
        pushButton_copyOperator->setObjectName("pushButton_copyOperator");
        pushButton_copyOperator->setGeometry(QRect(340, 470, 81, 31));
        textEdit_outputText = new QTextEdit(groupBox);
        textEdit_outputText->setObjectName("textEdit_outputText");
        textEdit_outputText->setGeometry(QRect(10, 285, 851, 181));
        label_inputInfo = new QLabel(groupBox);
        label_inputInfo->setObjectName("label_inputInfo");
        label_inputInfo->setGeometry(QRect(720, 50, 141, 31));

        retranslateUi(FormChildDataConversion);

        QMetaObject::connectSlotsByName(FormChildDataConversion);
    } // setupUi

    void retranslateUi(QWidget *FormChildDataConversion)
    {
        FormChildDataConversion->setWindowTitle(QCoreApplication::translate("FormChildDataConversion", "Form", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("FormChildDataConversion", "\350\275\254\346\215\242\347\261\273\345\236\213\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("FormChildDataConversion", "\350\276\223\345\205\245\346\225\260\346\215\256\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("FormChildDataConversion", "\350\276\223\345\207\272\346\225\260\346\215\256\357\274\232", nullptr));
        label_outputInfo->setText(QCoreApplication::translate("FormChildDataConversion", "\345\255\227\347\254\246\346\225\260\357\274\2320\357\274\214\345\255\227\350\212\202\346\225\2600", nullptr));
        pushButton_converOperator->setText(QCoreApplication::translate("FormChildDataConversion", "\350\275\254\346\215\242\346\223\215\344\275\234", nullptr));
        pushButton_clearOperator->setText(QCoreApplication::translate("FormChildDataConversion", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        pushButton_swapOperator->setText(QCoreApplication::translate("FormChildDataConversion", "\344\272\244\346\215\242\350\276\223\345\205\245\350\276\223\345\207\272", nullptr));
        pushButton_copyOperator->setText(QCoreApplication::translate("FormChildDataConversion", "\345\244\215\345\210\266\347\273\223\346\236\234", nullptr));
        label_inputInfo->setText(QCoreApplication::translate("FormChildDataConversion", "\345\255\227\347\254\246\346\225\260\357\274\2320\357\274\214\345\255\227\350\212\202\346\225\260\357\274\2320", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormChildDataConversion: public Ui_FormChildDataConversion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCHILDDATACONVERSION_H
