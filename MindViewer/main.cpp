#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setWindowTitle(QObject::tr("MindViewer"));
    w.setWindowIcon(QIcon(":/resource/icon/mind.svg"));
    w.show();
    return a.exec();
}
