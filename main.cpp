#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setWindowTitle(QObject::tr("MindViewer"));
    w.setWindowIcon(QIcon(":/resource/icon/mind.svg"));
    w.setStyleSheet(getQSS());//加载样式表
    w.show();
    return a.exec();
}
