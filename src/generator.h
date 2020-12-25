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

typedef struct type1
{
    int ASYN1;
    int ASYN2;
    int PAYLOAD;
    int Signal;
    int SignalValue;
    int Power;
    int PowerValue;
    int Delta1;
    int Delta2;
    int Delta3;
    int Theta1;
    int Theta2;
    int Theta3;
    int LowAlpha1;
    int LowAlpha2;
    int LowAlpha3;
    int HighAlpha1;
    int HightAlpha2;
    int HightAlpha3;
    int LowBeta1;
    int LowBeta2;
    int LowBeta3;
    int HighBeta1;
    int HighBeta2;
    int HighBeta3;
    int LowGamma1;
    int LowGamma2;
    int LowGamma3;
    int MiddleGamma1;
    int MiddleGamma2;
    int MiddleGamma3;
    int Attention;
    int AttentionValue;
    int Meditation;
    int MeditationValue;
    int checksum;
} type1;

class Generator : public QThread
{
    Q_OBJECT
public:
    Generator();
    ~Generator();

    int getNum(int max);//[0,max)
    int getNum();

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
