#ifndef FORMDATAPROCESSOR_H
#define FORMDATAPROCESSOR_H

#include <QWidget>

namespace Ui {
class FormDataProcessor;
}

class FormDataProcessor : public QWidget
{
    Q_OBJECT

public:
    explicit FormDataProcessor(QWidget *parent = nullptr);
    ~FormDataProcessor();

private:
    Ui::FormDataProcessor *ui;
};

#endif // FORMDATAPROCESSOR_H
