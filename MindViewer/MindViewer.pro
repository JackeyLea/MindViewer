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

#Windows平台配置
DEFINES += QWT_DLL
win32:{
    CONFIG(debug,debug | release){
        INCLUDEPATH += D:\qwt\include
        LIBS += -LD:\qwt\lib -lqwtd
    }
    CONFIG(release, debug | release){
        INCLUDEPATH += D:\qwt\include
        LIBS += -LD:\qwt\lib -lqwt
    }
}

#Linux下头文件以及库文件
unix:{
    INCLUDEPATH += /usr/include/qwt

    LIBS += -lqwt-qt5
}

SOURCES += \
    curve.cpp \
    dataparser.cpp \
    indicator.cpp \
    localfile.cpp \
    main.cpp \
    mainwidget.cpp \
    retriver.cpp \
    simulator.cpp

HEADERS += \
    curve.h \
    dataparser.h \
    icd.h \
    indicator.h \
    localfile.h \
    mainwidget.h \
    retriver.h \
    simulator.h

FORMS += \
    mainwidget.ui \
    retriver.ui

RESOURCES += \
    resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
