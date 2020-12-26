#include "curves.h"
#include "ui_curves.h"

Curves::Curves(QWidget *parent) :
    QwtPlot(parent),
    ui(new Ui::Curves)
{
    ui->setupUi(this);

    maxCnt = 201;

    for(int i=0;i<maxCnt;i++){
        xdata.append(i);
    }

    canvas = new QwtPlotCanvas(this);
    canvas->setPalette(Qt::white);
    canvas->setBorderRadius(10);
    setCanvas(canvas);
    plotLayout()->setAlignCanvasToScales(true);

    enableAxis(QwtPlot::yRight,true);

    setAxisTitle(QwtPlot::yLeft,"eeg value");
    setAxisTitle(QwtPlot::xBottom,"time: s");
    setAxisTitle(QwtPlot::yRight,"raw value");
    setAxisScale(QwtPlot::yRight,-32768,32767);
    setAxisScale(QwtPlot::yLeft,-10737423,10737423);
    setAxisScale(QwtPlot::xBottom,0.0,maxCnt);

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->enableX(true);
    grid->enableY(true);
    grid->setMajorPen(Qt::black,0,Qt::DotLine);
    grid->attach(this);

    curveRaw = new QwtPlotCurve("raw");
    curveRaw->setPen(Qt::red,2);
    curveRaw->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    curveRaw->setYAxis(QwtPlot::yRight);

    curveDelta = new QwtPlotCurve("delta");
    curveDelta->setPen(Qt::black,2);
    curveDelta->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveHighAlpha = new QwtPlotCurve("highalpha");
    curveHighAlpha->setPen(Qt::magenta,2);
    curveHighAlpha->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveHighBeta = new QwtPlotCurve("highbeta");
    curveHighBeta->setPen(Qt::darkBlue,2);
    curveHighBeta->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveLowAlpha = new QwtPlotCurve("lowalpha");
    curveLowAlpha->setPen(Qt::darkCyan,2);
    curveLowAlpha->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveLowBeta = new QwtPlotCurve("lowbeta");
    curveLowBeta->setPen(Qt::darkGray,2);
    curveLowBeta->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveLowGamma = new QwtPlotCurve("lowgamma");
    curveLowGamma->setPen(Qt::darkGreen,2);
    curveLowGamma->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveMidGamma = new QwtPlotCurve("midgamma");
    curveMidGamma->setPen(Qt::darkRed,2);
    curveMidGamma->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    curveTheta = new QwtPlotCurve("theta");
    curveTheta->setPen(Qt::darkYellow,2);
    curveTheta->setRenderHint(QwtPlotItem::RenderAntialiased,true);

//    QwtSymbol *symbol=new QwtSymbol(QwtSymbol::Ellipse,QBrush(Qt::yellow),QPen(Qt::red,2),QSize(6,6));//设置样本点的颜色、大小
//    curveRaw->setSymbol(symbol);//添加样本点形状

    //--------------设置图例可以被点击来确定是否显示曲线-----------------------//
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );//图例可被点击
    insertLegend( legend, QwtPlot::RightLegend );
    connect(legend,SIGNAL(checked(const QVariant &,bool,int)),SLOT(showItem(const QVariant &, bool)));//点击图例操作

    QwtPlotItemList items = itemList( QwtPlotItem::Rtti_PlotCurve );//获取画了多少条曲线,如果为获取其他形状，注意改变参数
    for ( int i = 0; i < items.size(); i++ ){
        items[i]->setVisible(true);
//        if ( i == 0 ){
//            const QVariant itemInfo = itemToInfo( items[i] );

//            QwtLegendLabel *legendLabel =
//                    qobject_cast<QwtLegendLabel *>( legend->legendWidget( itemInfo ) );
//            if ( legendLabel )
//                legendLabel->setChecked( true );//
//            items[i]->setVisible( true );
//        }else{
//            items[i]->setVisible( false );
//        }
    }
    resize(800,532);
    replot();
    setAutoReplot( true );//设置自动重画，相当于更新
}

Curves::~Curves()
{
    delete canvas;
    delete ui;
}

void Curves::updateRawData(short raw)
{
    if(dataRaw.size()>=maxCnt){
        dataRaw.pop_front();
        //dataRaw.erase(dataRaw.begin(),dataRaw.begin()+1);
    }
    dataRaw.append((double)raw);

    curveRaw->setSamples(xdata,dataRaw);
    curveRaw->attach(this);
    curveRaw->setLegendAttribute(curveRaw->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    replot();
}
//显示八个脑电波数据
void Curves::updateEEGData(_eegPkt pkt)
{
    if(dataDelta.size()>=maxCnt){
        dataDelta.pop_front();
    }
    dataDelta.append(pkt.delta);
    curveDelta->setSamples(xdata,dataDelta);
    curveDelta->attach(this);
    curveDelta->setLegendAttribute(curveDelta->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataHighAlpha.size()>=maxCnt){
        dataHighAlpha.pop_front();
    }
    dataHighAlpha.append(pkt.highAlpha);
    curveHighAlpha->setSamples(xdata,dataHighAlpha);
    curveHighAlpha->attach(this);
    curveHighAlpha->setLegendAttribute(curveHighAlpha->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataHighBeta.size()>=maxCnt){
        dataHighBeta.pop_front();
    }
    dataHighBeta.append(pkt.highBeta);
    curveHighBeta->setSamples(xdata,dataHighBeta);
    curveHighBeta->attach(this);
    curveHighBeta->setLegendAttribute(curveHighBeta->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataLowAlpha.size()>=maxCnt){
        dataLowAlpha.pop_front();
    }
    dataLowAlpha.append(pkt.lowAlpha);
    curveLowAlpha->setSamples(xdata,dataLowAlpha);
    curveLowAlpha->attach(this);
    curveLowAlpha->setLegendAttribute(curveLowAlpha->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataLowBeta.size()>=maxCnt){
        dataLowBeta.pop_front();
    }
    dataLowBeta.append(pkt.lowBeta);
    curveLowBeta->setSamples(xdata,dataLowBeta);
    curveLowBeta->attach(this);
    curveLowBeta->setLegendAttribute(curveLowBeta->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataLowGamma.size()>=maxCnt){
        dataLowGamma.pop_front();
    }
    dataLowGamma.append(pkt.lowGamma);
    curveLowGamma->setSamples(xdata,dataLowGamma);
    curveLowGamma->attach(this);
    curveLowGamma->setLegendAttribute(curveLowGamma->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataMidGamma.size()>=maxCnt){
        dataMidGamma.pop_front();
    }
    dataMidGamma.append(pkt.midGamma);
    curveMidGamma->setSamples(xdata,dataMidGamma);
    curveMidGamma->attach(this);
    curveMidGamma->setLegendAttribute(curveMidGamma->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    if(dataTheta.size()>=maxCnt){
        dataTheta.pop_front();
    }
    dataTheta.append(pkt.theta);
    curveTheta->setSamples(xdata,dataTheta);
    curveTheta->attach(this);
    curveTheta->setLegendAttribute(curveTheta->LegendShowLine);//显示图例的标志，这里显示线的颜色。

    replot();
}

void Curves::showItem(const QVariant &itemInfo, bool on)
{
    QwtPlotItem *plotItem = infoToItem( itemInfo );
    if ( plotItem )
        plotItem->setVisible( on );
}
