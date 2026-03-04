#ifndef FORMTCPCLIENT_H
#define FORMTCPCLIENT_H

#include <QWidget>

namespace Ui {
class FormTcpClient;
}

class FormTcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit FormTcpClient(QWidget *parent = nullptr);
    ~FormTcpClient();

private slots:
    void on_pushButton_TCPClientConnect_clicked();

private:
    Ui::FormTcpClient *ui;
};

#endif // FORMTCPCLIENT_H
