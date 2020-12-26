#ifndef GENERATOR_H
#define GENERATOR_H

#include <QThread>
#include <QByteArray>
#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <QTimer>
#include <QVector>
#include <QMutex>

class Generator : public QThread
{
    Q_OBJECT
public:
    Generator();
    ~Generator();

    int getNum(int max);//[0,max)
    int getNum();//[0,256)

    QByteArray getRaw();
    QByteArray getEEG();

    void stopNow();

protected:
    void run();

signals:
    void sendData(QByteArray ba);

private:
    QTimer *timer;
    QMutex mutex;
    bool isStop;
};

#endif // GENERATOR_H
