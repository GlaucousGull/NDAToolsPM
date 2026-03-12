#include "formdataprocessor.h"
#include "ui_formdataprocessor.h"

FormDataProcessor::FormDataProcessor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDataProcessor)
{
    ui->setupUi(this);
}

FormDataProcessor::~FormDataProcessor()
{
    delete ui;
}
