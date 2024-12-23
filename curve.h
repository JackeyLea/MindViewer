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

#include <QPainter>
#include <QFrame>

#include "icd.h"

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
    void updateData(const _eegPkt& pkt);

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
    void drawCurves(QPainter* painter);

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
    QwtScaleMap m_rawXMap;
    QwtScaleMap m_rawYMap;
    QwtScaleMap m_eegXMap;
    QwtScaleMap m_eegYMap;

    QVector<double> m_vRawX;//坐标轴
    QVector<double> m_vEEGX;//坐标轴

    QVector<double> m_vDataRaw;//原始数据折线数据
    // EEG数据折线数据
    QVector<double> m_vDataDelta;
    QVector<double> m_vDataTheta;
    QVector<double> m_vDataLowAlpha;
    QVector<double> m_vDataHighAlpha;
    QVector<double> m_vDataLowBeta;
    QVector<double> m_vDataHighBeta;
    QVector<double> m_vDataLowGamma;
    QVector<double> m_vDataMidGamma;

    // 折线
    QwtPlotCurve m_curveRaw;
    //分别为 delta theta lowalpha highalpha lowbeta highbeta lowgamma midgamma
    QwtPlotCurve m_curve[8];
};

#endif // CURVE_H
