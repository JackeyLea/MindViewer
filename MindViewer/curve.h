///////////////
/// \author JackeyLea
/// \date 2024-11-01
/// \note 折线类
///////////////

#ifndef CURVE_H
#define CURVE_H

#include <QwtScaleMap>
#include <QwtPlotCurve>
#include <QwtSymbol>
#include <QwtMath>

#include <QPainter>
#include <QFrame>

#include "icd.h"

const int rawCnt = 500;
const int eegCnt = 250;
const int Size = 27;
const int CurvCnt = 9;

class Curve : public QFrame
{
public:
    Curve(QWidget *parent = nullptr);

    void updateData(_eegPkt pkt);

    void clear();

protected:
    virtual void paintEvent(QPaintEvent *event) QWT_OVERRIDE;

private:
    void drawCurves(QPainter*painter);
    void populate();
    void shiftDown(QRect& rect, int offset) const;

    //范围
    QwtScaleMap rawXMap;
    QwtScaleMap rawYMap;
    QwtScaleMap eegXMap;
    QwtScaleMap eegYMap;

    QVector<double> rawx;//坐标轴
    QVector<double> eegx;//坐标轴

    QVector<double> dataRaw;

    QVector<double> dataDelta;
    QVector<double> dataTheta;
    QVector<double> dataLowAlpha;
    QVector<double> dataHighAlpha;
    QVector<double> dataLowBeta;
    QVector<double> dataHighBeta;
    QVector<double> dataLowGamma;
    QVector<double> dataMidGamma;

    QwtPlotCurve curveRaw;
    QwtPlotCurve curve[8];//分别为 delta theta lowalpha highalpha lowbeta highbeta lowgamma midgamma
};

#endif // CURVE_H
