#include "curve.h"

Curve::Curve(QWidget *parent)
    :QFrame(parent)
{
    //绘图范围
    rawXMap.setScaleInterval(0.0,rawCnt);
    rawYMap.setScaleInterval(-32768,32767);
    eegXMap.setScaleInterval(0.0,eegCnt);
    eegYMap.setScaleInterval(-10737423,10737423);

    setFrameStyle( QFrame::Box | QFrame::Raised );
    setLineWidth( 3 );
    setMidLineWidth( 5 );

    //坐标轴
    for(int i=0;i<rawCnt;i++){
        rawx.append(i);
    }
    for(int i=0;i<eegCnt;i++){
        eegx.append(i);
    }

    populate();
}

//显示八个脑电波数据
void Curve::updateData(const _eegPkt& pkt)
{
    // 原始数据
    int newSize = pkt.raw.size();
    if(dataRaw.size()>=rawCnt){//保持内存中最多rawCnt个点数据
        dataRaw.remove(0,qMin(newSize,dataRaw.size()));
    }
    dataRaw.append(pkt.raw);
    curveRaw.setSamples(rawx,dataRaw);

    // EEG数据
    //δ线
    if(dataDelta.size()>=eegCnt){
        dataDelta.pop_front();
    }
    dataDelta.append(pkt.delta);
    curve[0].setSamples(eegx,dataDelta);

    //高α线
    if(dataHighAlpha.size()>=eegCnt){
        dataHighAlpha.pop_front();
    }
    dataHighAlpha.append(pkt.highAlpha);
    curve[1].setSamples(eegx,dataHighAlpha);

    //高β线
    if(dataHighBeta.size()>=eegCnt){
        dataHighBeta.pop_front();
    }
    dataHighBeta.append(pkt.highBeta);
    curve[2].setSamples(eegx,dataHighBeta);

    //低α线
    if(dataLowAlpha.size()>=eegCnt){
        dataLowAlpha.pop_front();
    }
    dataLowAlpha.append(pkt.lowAlpha);
    curve[3].setSamples(eegx,dataLowAlpha);

    //低β线
    if(dataLowBeta.size()>=eegCnt){
        dataLowBeta.pop_front();
    }
    dataLowBeta.append(pkt.lowBeta);
    curve[4].setSamples(eegx,dataLowBeta);

    //低γ线
    if(dataLowGamma.size()>=eegCnt){
        dataLowGamma.pop_front();
    }
    dataLowGamma.append(pkt.lowGamma);
    curve[5].setSamples(eegx,dataLowGamma);

    //高γ线
    if(dataMidGamma.size()>=eegCnt){
        dataMidGamma.pop_front();
    }
    dataMidGamma.append(pkt.midGamma);
    curve[6].setSamples(eegx,dataMidGamma);

    //θ线
    if(dataTheta.size()>=eegCnt){
        dataTheta.pop_front();
    }
    dataTheta.append(pkt.theta);
    curve[7].setSamples(eegx,dataTheta);
}

//清空数据
void Curve::clear()
{
    dataRaw.clear();
    curveRaw.setSamples(rawx,dataRaw);

    dataDelta.clear();
    curve[0].setSamples(eegx,dataDelta);

    dataHighAlpha.clear();
    curve[1].setSamples(eegx,dataHighAlpha);

    dataHighBeta.clear();
    curve[2].setSamples(eegx,dataHighBeta);

    dataLowAlpha.clear();
    curve[3].setSamples(eegx,dataLowAlpha);

    dataLowBeta.clear();
    curve[4].setSamples(eegx,dataLowBeta);

    dataLowGamma.clear();
    curve[5].setSamples(eegx,dataLowGamma);

    dataMidGamma.clear();
    curve[6].setSamples(eegx,dataMidGamma);

    dataTheta.clear();
    curve[7].setSamples(eegx,dataTheta);
}

void Curve::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setClipRect(contentsRect());

    drawCurves(&painter);
}

void Curve::drawCurves(QPainter *painter)
{
    int deltay;

    QRect r = contentsRect();

    deltay = r.height() / CurvCnt - 1;

    r.setHeight( deltay );

    //  raw线
    rawXMap.setPaintInterval( r.left(), r.right() );
    rawYMap.setPaintInterval( r.top(), r.bottom() );

    painter->setRenderHint( QPainter::Antialiasing,
                            curveRaw.testRenderHint( QwtPlotItem::RenderAntialiased ) );
    curveRaw.draw( painter, rawXMap, rawYMap, r );
    shiftDown( r, deltay );

    // eeg线
    for(int i=0;i<8;i++){
        eegXMap.setPaintInterval( r.left(), r.right() );
        eegYMap.setPaintInterval( r.top(), r.bottom() );
        painter->setRenderHint( QPainter::Antialiasing,
                                curve[i].testRenderHint( QwtPlotItem::RenderAntialiased ) );
        curve[i].draw( painter, eegXMap, eegYMap, r );
        shiftDown( r, deltay );
    }

    // draw titles
    r = contentsRect();//回到起点
    painter->setFont( QFont( "Helvetica", 20 ) );

    const int alignment = Qt::AlignTop | Qt::AlignRight;

    painter->setPen( Qt::black );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "Raw" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "δ" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "α↑" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "α↓" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "β↑" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "β↓" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "γ↓" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "γ-" );
    shiftDown( r, deltay );

    painter->drawText( 0, r.top(), r.width(), painter->fontMetrics().height(),
                       alignment, "θ" );
    shiftDown( r, deltay );
}

void Curve::populate()
{
    //原始
    curveRaw.setPen( Qt::red );
    curveRaw.setStyle( QwtPlotCurve::Lines );
    curveRaw.setRenderHint( QwtPlotItem::RenderAntialiased );
    curveRaw.setSamples(rawx,dataRaw);

    //δ线
    curve[0].setPen( Qt::black );
    curve[0].setStyle( QwtPlotCurve::Lines );
    curve[0].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[0].setSamples(eegx,dataDelta);

    //高α线
    curve[1].setPen( Qt::magenta );
    curve[1].setStyle( QwtPlotCurve::Lines );
    curve[1].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[1].setSamples(eegx,dataHighAlpha);

    //低α线
    curve[2].setPen( Qt::darkBlue );
    curve[2].setStyle( QwtPlotCurve::Lines );
    curve[2].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[2].setSamples(eegx,dataLowAlpha);

    //高β
    curve[3].setPen( Qt::darkCyan );
    curve[3].setStyle( QwtPlotCurve::Lines );
    curve[3].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[3].setSamples(eegx,dataHighBeta);

    //低β
    curve[4].setPen( Qt::darkMagenta );
    curve[4].setStyle( QwtPlotCurve::Lines );
    curve[4].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[4].setSamples(eegx,dataLowBeta);

    //低γ
    curve[5].setPen( Qt::darkGreen );
    curve[5].setStyle( QwtPlotCurve::Lines );
    curve[5].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[5].setSamples(eegx,dataLowGamma);

    //中γ
    curve[6].setPen( Qt::darkRed );
    curve[6].setStyle( QwtPlotCurve::Lines );
    curve[6].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[6].setSamples(eegx,dataMidGamma);

    //θ
    curve[7].setPen( Qt::darkYellow );
    curve[7].setStyle( QwtPlotCurve::Lines );
    curve[7].setRenderHint( QwtPlotItem::RenderAntialiased );
    curve[7].setSamples(eegx,dataTheta);
}

void Curve::shiftDown(QRect &rect, int offset) const
{
    rect.translate(0, offset);
}
