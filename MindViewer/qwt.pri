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
