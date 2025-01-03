#######################
### \author Jackey Lea
### \date 2020-12-26
### \brief 主程序
### \note Qt 6.8.0
### \note VS2022
#######################

QT     += core gui widgets
QT     += serialport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(qwt.pri)

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/curve.cpp \
    src/dataparser.cpp \
    src/indicator.cpp \
    src/localfile.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/retriver.cpp \
    src/simulator.cpp

HEADERS += \
    include/curve.h \
    include/dataparser.h \
    include/icd.h \
    include/indicator.h \
    include/localfile.h \
    include/mainwidget.h \
    include/retriver.h \
    include/simulator.h

FORMS += \
    ui/mainwidget.ui \
    ui/retriver.ui

RESOURCES += \
    resource.qrc

####################
# 程序信息
####################
# 可执行文件名称
TARGET = MindViewer
# 版本信息
VERSION = 1.0.0
# 图标
RC_ICONS = resource/icon/mind.ico
# 公司名称
QMAKE_TARGET_COMPANY = "食铁兽"
# 产品名称
QMAKE_TARGET_PRODUCT = "MindViewer"
# 文件说明
QMAKE_TARGET_DESCRIPTION="Qt 6.8.1 (64bit) with MSVC 2022"
# 版权信息
QMAKE_TARGET_COPYRIGHT="Copyright 2020-2024 blog.jackeylea.com.All rights reserved."
# 语言 中文（简体）
RC_LANG = 0x0004
####################
# 程序信息结束
####################

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
