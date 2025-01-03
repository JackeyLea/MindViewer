## MindViewer

神念科技（neurosky）脑波模块TGAM图像化显示工具

***写代码5年了，以软件架构和系统设计角度对软件进行重构***

官方说明手册翻译：<a href="https://blog.jackeylea.com/tgam/translation-of-tgam-development-doc" target="_blank">TGAM开发手册翻译</a>

TGAM连接及测试：<a href="https://blog.jackeylea.com/tgam/setup-and-installation-of-tgam-module" target="_blank">神念科技TGAM模块组装测试</a>

本软件开发流程和使用介绍：<a href="https://blog.jackeylea.com/qt/mindviewer-tgam-module-graphic-application" target="_blank">MindViewer-TGAM模块数据图形化软件</a>

配置好TGAM模块，连接好蓝牙，然后打开本软件读取端口数据就可以看见数据显示了。

### 配置

Qt 6.8.1 + VS 2022 64bit + QWT6.3.0(build with vcpkg)

## 编译

1. 下载vcpkg，使用vcpkg安装qwt库
2. 安装Qt 6.8.1
3. 安装VS2022
4. 使用QtCreator打开工程并编译

### 说明

- 在官方的API中没有给出眨眼（blink）/走神程度的接口，所以其一直为0
- TGAM模块是每秒发送512个数据包，也就是每2毫秒有一个数据包