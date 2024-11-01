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

const int Size = 27;
const int CurvCnt = 9;

class Curve : public QFrame
{
public:
    Curve();

protected:
    virtual void paintEvent(QPaintEvent *event) QWT_OVERRIDE;

private:
    void drawCurves(QPainter*painter);
    void populate();
    void shiftDown(QRect& rect, int offset) const;

    QwtPlotCurve m_curves[CurvCnt];

    QwtScaleMap xMap;
    QwtScaleMap yMap;

    double xval[Size];
    double yval[Size];
};

#endif // CURVE_H
