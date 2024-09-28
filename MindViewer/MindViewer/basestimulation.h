/////////////////////////
///
/// \author Jackey Lea
/// \date 2024-09-28
/// \note 数据激励的基类
///

#ifndef BASESTIMULATION_H
#define BASESTIMULATION_H

#include <QObject>
#include <QByteArray>

class BaseStimulation : public QObject
{
public:
    BaseStimulation(){}

    ~BaseStimulation(){}

protected:
    void sigNewFrame(QByteArray ba);
};

#endif // BASESTIMULATION_H
