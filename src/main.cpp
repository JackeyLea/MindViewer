#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("MindViewer"));
    w.setWindowIcon(QIcon(":/resources/icons/mind.svg"));
    w.show();
    return a.exec();
}
