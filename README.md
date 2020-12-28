# MindViewer

官方说明手册翻译：<a href="https://feater.top/about/2275/">TGAM开发手册翻译</a>

TGAM连接及测试：<a href="https://feater.top/linux/2353/">神念科技TGAM模块组装测试</a>

本软件开发流程和使用介绍：<a href="https://feater.top/series/qt/2354/">MindViewer-TGAM模块数据图形化软件</a>

神念科技脑波模块TGAM图像化显示工具

配置好TGAM模块，连接好蓝牙，然后打开本软件读取端口数据就可以看见数据显示了。

每秒钟接近600个点，不想使用qcharts（听说性能不是很好），绘图部分使用qwt库。

Qt/qwt6.1.3/qserialport

绘图效果：<img src="https://image.feater.top/mindviewer_result.png?imageView2/0/q/75|watermark/2/text/ZmVhdGVyLnRvcA==/font/5a6L5L2T/fontsize/800/fill/I0ZGMDAwMA==/dissolve/100/gravity/SouthWest/dx/10/dy/10" alt="result"></img>