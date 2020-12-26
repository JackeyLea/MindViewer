#ifndef CURVESCOMMON_H
#define CURVESCOMMON_H

#include <QPen>
#include <QColor>
#include <QResizeEvent>

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

#include "common.h"

namespace Ui {
class CurvesCommon;
}

class CurvesCommon : public QwtPlot
{
    Q_OBJECT

public:
    explicit CurvesCommon(QWidget *parent = nullptr);
    ~CurvesCommon();

    void updateCommonData(struct _eegPkt pkt);

private slots:
    void showItem(const QVariant &itemInfo, bool on);

private:
    Ui::CurvesCommon *ui;

    QwtPlotCanvas *canvas;

    QwtPlotCurve *curveAttention;
    QwtPlotCurve *curveMeditation;
    QwtPlotCurve *curveSignal;//信号强度
    QwtPlotCurve *curveBlink;//眨眼
    //QwtPlotCurve *curveMWL;

    QVector<double> dataAttention;
    QVector<double> dataMeditation;
    QVector<double> dataSignal;
    QVector<double> dataBlink;
    QVector<double> xdata;

    int maxCnt;
};

#endif // CURVESCOMMON_H
