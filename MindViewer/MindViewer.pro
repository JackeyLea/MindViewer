QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Windows平台配置
DEFINES += QWT_DLL
win32:{
    CONFIG(debug,debug | release){
        INCLUDEPATH += C:\vcpkg\installed\x64-windows\include\qwt
        LIBS += -LC:\vcpkg\installed\x64-windows\debug\lib -lqwtd
    }
    CONFIG(release, debug | release){
        INCLUDEPATH += C:\vcpkg\installed\x64-windows\include\qwt
        LIBS += -LC:\vcpkg\installed\x64-windows\lib -lqwt
    }
}

#Linux下头文件以及库文件
unix:{
    INCLUDEPATH += /usr/include/qwt

    LIBS += -lqwt-qt5
}

SOURCES += \
    dataparser.cpp \
    main.cpp \
    mainwidget.cpp \
    retriver.cpp \
    simulator.cpp

HEADERS += \
    dataparser.h \
    icd.h \
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
