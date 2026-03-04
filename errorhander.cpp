#include "errorhander.h"

ErrorHandler::ErrorHandler(QObject *parent)
    : QObject{parent}
{}

ErrorHandler::~ErrorHandler()
{
    if(logStream) {
        delete logStream;   // 先删除流，在关闭文件
    }
    if(logFile) {
        logFile->close();   // 确保落盘
        delete logFile;
    }
}
