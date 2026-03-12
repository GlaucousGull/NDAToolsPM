QT       += core gui

# 网络模块：提供TCP/UDO套接字功能
QT += network
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dataconverter.cpp \
    errorhandler.cpp \
    formchilddataconversion.cpp \
    formchilddatavalidation.cpp \
    formdataprocessor.cpp \
    formtcpclient.cpp \
    formtcpserver.cpp \
    formudpclient.cpp \
    formudpserver.cpp \
    inputvalidator.cpp \
    main.cpp \
    mainwidget.cpp \
    network.cpp

HEADERS += \
    dataconverter.h \
    errorhandler.h \
    formchilddataconversion.h \
    formchilddatavalidation.h \
    formdataprocessor.h \
    formtcpclient.h \
    formtcpserver.h \
    formudpclient.h \
    formudpserver.h \
    inputvalidator.h \
    mainwidget.h \
    network.h

FORMS += \
    formchilddataconversion.ui \
    formchilddatavalidation.ui \
    formdataprocessor.ui \
    formtcpclient.ui \
    formtcpserver.ui \
    formudpclient.ui \
    formudpserver.ui \
    mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE += applogo.rc

RESOURCES += \
    images.qrc

# 自动生成部署脚本（Windows）
win32 {
    # 定义部署目标路径
    DEPLOY_DIR = $$OUT_PWD/deploy
    # 创建部署目录
    QMAKE_POST_LINK += mkdir -p $$DEPLOY_DIR && \
                       $$QMAKE_COPY $$OUT_PWD/$$TARGET.exe $$DEPLOY_DIR/ && \
                       echo "cd /d \"$$shell_path($$DEPLOY_DIR)\"" > $$DEPLOY_DIR/deploy.bat && \
                       echo "\"$$shell_path($$QMAKE_WINDEPLOYQT)\" $$TARGET.exe" >> $$DEPLOY_DIR/deploy.bat
}
