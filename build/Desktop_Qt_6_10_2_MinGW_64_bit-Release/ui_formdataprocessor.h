/********************************************************************************
** Form generated from reading UI file 'formdataprocessor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMDATAPROCESSOR_H
#define UI_FORMDATAPROCESSOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <formchilddataconversion.h>
#include "formchilddatavalidation.h"

QT_BEGIN_NAMESPACE

class Ui_FormDataProcessor
{
public:
    QTabWidget *tabWidget_DataConversion;
    FormChildDataConversion *tab_DataConversion;
    FormChildDataValidation *tab_dataValidation;

    void setupUi(QWidget *FormDataProcessor)
    {
        if (FormDataProcessor->objectName().isEmpty())
            FormDataProcessor->setObjectName("FormDataProcessor");
        FormDataProcessor->resize(904, 564);
        tabWidget_DataConversion = new QTabWidget(FormDataProcessor);
        tabWidget_DataConversion->setObjectName("tabWidget_DataConversion");
        tabWidget_DataConversion->setGeometry(QRect(0, 0, 895, 551));
        tab_DataConversion = new FormChildDataConversion();
        tab_DataConversion->setObjectName("tab_DataConversion");
        tabWidget_DataConversion->addTab(tab_DataConversion, QString());
        tab_dataValidation = new FormChildDataValidation();
        tab_dataValidation->setObjectName("tab_dataValidation");
        tabWidget_DataConversion->addTab(tab_dataValidation, QString());

        retranslateUi(FormDataProcessor);

        tabWidget_DataConversion->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormDataProcessor);
    } // setupUi

    void retranslateUi(QWidget *FormDataProcessor)
    {
        FormDataProcessor->setWindowTitle(QCoreApplication::translate("FormDataProcessor", "Form", nullptr));
        tabWidget_DataConversion->setTabText(tabWidget_DataConversion->indexOf(tab_DataConversion), QCoreApplication::translate("FormDataProcessor", "\346\225\260\346\215\256\350\275\254\346\215\242", nullptr));
        tabWidget_DataConversion->setTabText(tabWidget_DataConversion->indexOf(tab_dataValidation), QCoreApplication::translate("FormDataProcessor", "\346\225\260\346\215\256\346\240\241\351\252\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormDataProcessor: public Ui_FormDataProcessor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMDATAPROCESSOR_H
