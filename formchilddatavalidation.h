#ifndef FORMCHILDDATAVALIDATION_H
#define FORMCHILDDATAVALIDATION_H

#include <QWidget>
#include <QCloseEvent>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QMessageBox>

#include <QClipboard>
#include <QCheckBox>
#include <QFutureWatcher>
#include <QTimer>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QQueue>
#include <QFileInfo>
#include <QtConcurrent>
#include <QDebug>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QStringConverter> // Qt6 字符串编码转化器
#else
#include <QTextCode>
#endif

#include "dataconverter.h"

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class FormChildDataValidation;
}

class FormChildDataValidation : public QWidget
{
    Q_OBJECT

public:
    explicit FormChildDataValidation(QWidget *parent = nullptr);
    ~FormChildDataValidation();

    void saveLog();
private slots:
    // 计算校验值
    void on_pushButton_calculateCheckSums_clicked();
    // 拷贝校验值
    void on_pushButton_copyCheckSums_clicked();

private:
    // 连接信号槽
    void connectSignals();

    // 复制文本到剪切板
    void copyToClipboard(const QString& text);

    // 显示消息提示
    void showMessage(const QString& message, bool isError = false);

    // 设置校验计算忙碌状态
    void setCheckSumBusy(bool busy);

    // 追加日志到日志队列
    void appendLog(const QString& message);

    // 校验计算是否正在运行的标志（true = 正在计算，false=空闲）
    bool checkSumRunning = false;

    // 异步校验计算任务监视器
    QFutureWatcher<DataConverter::CheckSumResult> checkSumWatcher;

    // 日志条目队列
    QQueue<QString> logEntries;

protected:
    // 窗口关闭事件
    void closeEvent(QCloseEvent* event) override;

    // 大小写复选框状态变化槽函数
    void onUpperCaseToggled(bool enabled);

    // 异步校验计算完成槽函数
    void onCheckSumFinished();
private:
    Ui::FormChildDataValidation *ui;
};

#endif // FORMCHILDDATAVALIDATION_H
