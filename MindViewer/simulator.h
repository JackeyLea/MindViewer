/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 用于产生测试数据
///
////////////////////////////////////////////

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QtMath>
#include <QTimer>
#include <QVector>

class Simulator : public QObject
{
    Q_OBJECT
public:
    Simulator();
    ~Simulator();

    QByteArray getOne(uchar mn, int max);//输入为modulename,max
    QByteArray getRaw(bool noise=false);//
    QByteArray getEEG(bool noise=false);

signals:
    void sigNewPkg(QByteArray ba);

private:
    QTimer *timer;
    bool isStop;

    int i=0;
};

#endif // SIMULATOR_H
