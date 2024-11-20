#######################
### \author Jackey Lea
### \date 2024-10-29
### \brief 单元测试
### \note Qt 6.8.0
### \note VS2022
#######################
QT += core gui widgets
QT += testlib
QT += serialport

CONFIG += c++17 cmdline
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../MindViewer/qwt.pri)

SOURCES += \
        main.cpp \
        mindviewertest.cpp \
        ../MindViewer/simulator.cpp \
        ../MindViewer/dataparser.cpp \
        ../MindViewer/retriver.cpp \
        ../MindViewer/localfile.cpp \
        ../MindViewer/mainwidget.cpp \
        ../MindViewer/curve.cpp \
        ../MindViewer/indicator.cpp

HEADERS += \
    mindviewertest.h \
    ../MindViewer/simulator.h \
    ../MindViewer/dataparser.h \
    ../MindViewer/retriver.h \
    ../MindViewer/localfile.h \
    ../MindViewer/mainwidget.h \
    ../MindViewer/curve.h \
    ../MindViewer/indicator.h

FORMS += \
    ../MindViewer/retriver.ui \
    ../MindViewer/mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

