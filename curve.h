///////////////
/// \author JackeyLea
/// \date 2024-11-01
/// \note 折线类
///////////////

#ifndef CURVE_H
#define CURVE_H

#include "qwt_scale_map.h"
#include "qwt_plot_curve.h"
#include "qwt_symbol.h"
#include "qwt_math.h"

#include <QPainter>
#include <QFrame>

#include "icd.h"

const int rawCnt = 500;//原始数据可视范围点数量
const int eegCnt = 250;//EEG可视范围点数量
const int CurvCnt = 9;//折线数量

class Curve : public QFrame
{
public:
    /// 构造函数
    /// \brief Curve
    /// \param parent
    ///
    explicit Curve(QWidget *parent = nullptr);

    /// 更新缓存区
    /// \brief updateData
    /// \param pkt
    ///
    void updateData(const _eegPkt pkt);

    /// 清空缓存区数据
    /// \brief clear
    ///
    void clear();

protected:
    /// 界面绘图
    /// \brief paintEvent
    /// \param event
    ///
    virtual void paintEvent(QPaintEvent *event) QWT_OVERRIDE;

private:
    /// 绘制折线
    /// \brief drawCurves
    /// \param painter
    ///
    void drawCurves(QPainter*painter);

    /// 折线（颜色、线宽）属性设置
    /// \brief populate
    ///
    void populate();

    /// 折线平移
    /// \brief shiftDown
    /// \param rect
    /// \param offset
    ///
    void shiftDown(QRect& rect, int offset) const;

    //范围
    QwtScaleMap rawXMap;
    QwtScaleMap rawYMap;
    QwtScaleMap eegXMap;
    QwtScaleMap eegYMap;

    QVector<double> rawx;//坐标轴
    QVector<double> eegx;//坐标轴

    QVector<double> dataRaw;//原始数据折线数据
    // EEG数据折线数据
    QVector<double> dataDelta;
    QVector<double> dataTheta;
    QVector<double> dataLowAlpha;
    QVector<double> dataHighAlpha;
    QVector<double> dataLowBeta;
    QVector<double> dataHighBeta;
    QVector<double> dataLowGamma;
    QVector<double> dataMidGamma;

    // 折线
    QwtPlotCurve curveRaw;
    //分别为 delta theta lowalpha highalpha lowbeta highbeta lowgamma midgamma
    QwtPlotCurve curve[8];
};

#endif // CURVE_H
