#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    // 窗口关闭事件，保存所有子窗口的日志
    void closeEvent(QCloseEvent* event);

private:
    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H
