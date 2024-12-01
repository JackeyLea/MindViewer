#include "mainwidget.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //判断分辨率
    QRect resolution = QApplication::primaryScreen()->geometry();

    MainWidget w;
    if(resolution.width()<1080 || resolution.height()<720){
        QMessageBox::warning(&w,QMessageBox::tr("警告"),QMessageBox::tr("屏幕过小，无法完全显示界面"));
        return -1;
    }
    w.setWindowTitle(QObject::tr("MindViewer"));
    w.setWindowIcon(QIcon(":/resource/icon/mind.svg"));
    w.setStyleSheet(getQSS());//加载样式表
    w.show();
    return a.exec();
}
