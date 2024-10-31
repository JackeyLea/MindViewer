/////////////////////////////////////////////
///
/// \author jacky lea
/// \date 2020-12-26
/// \note 绘制原始数据折线图，位于界面上半部分，是主要部分
///
////////////////////////////////////////////

#ifndef CURVES_H
#define CURVES_H

#include <QPen>

#include "qwt.h"
#include "qwt_plot.h"
#include "qwt_plot_canvas.h"
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>

#include <qwt_legend.h>
#include <qwt_legend_label.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qwt_symbol.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_layout.h>

namespace Ui {
class Curves;
}

class Curves : public QwtPlot
{
    Q_OBJECT

public:
    explicit Curves(QWidget *parent = nullptr);
    ~Curves();

    void updateRawData(short raw);
    void updateRawData(QVector<double> rawData);
    void updateEEGData(struct _eegPkt pkt);

    void CurveClear();

private slots:
    void showItem(const QVariant &itemInfo, bool on);

private:
    Ui::Curves *ui;

    QwtPlotCanvas *canvas;

    QwtPlotCurve *curveRaw;
    QwtPlotCurve *curveDelta;
    QwtPlotCurve *curveTheta;
    QwtPlotCurve *curveLowAlpha;
    QwtPlotCurve *curveHighAlpha;
    QwtPlotCurve *curveLowBeta;
    QwtPlotCurve *curveHighBeta;
    QwtPlotCurve *curveLowGamma;
    QwtPlotCurve *curveMidGamma;

    QVector<double> xdata;
    QVector<double> dataRaw;
    QVector<double> dataDelta;
    QVector<double> dataTheta;
    QVector<double> dataLowAlpha;
    QVector<double> dataHighAlpha;
    QVector<double> dataLowBeta;
    QVector<double> dataHighBeta;
    QVector<double> dataLowGamma;
    QVector<double> dataMidGamma;

    int maxCnt;
};

#endif // CURVES_H
