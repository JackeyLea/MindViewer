#include "curve.h"

const int rawCnt = 500;//原始数据可视范围点数量
const int eegCnt = 250;//EEG可视范围点数量
const int CurvCnt = 9;//折线数量

Curve::Curve(QWidget *parent)
    :QFrame(parent)
{
    //绘图范围
    m_rawXMap.setScaleInterval(0.0,rawCnt);
    m_rawYMap.setScaleInterval(-32768,32767);
    m_eegXMap.setScaleInterval(0.0,eegCnt);
    m_eegYMap.setScaleInterval(-10737423,10737423);

    setFrameStyle( QFrame::Box | QFrame::Raised );
    setLineWidth( 3 );
    setMidLineWidth( 5 );

    //坐标轴
    for(int i=0;i<rawCnt;i++){
        m_vRawX.append(i);
    }
    for(int i=0;i<eegCnt;i++){
        m_vEEGX.append(i);
    }

    populate();
}

//显示八个脑电波数据
void Curve::updateData(const _eegPkt& pkt)
{
    // 原始数据
    int newSize = pkt.raw.size();
    if(m_vDataRaw.size()>=rawCnt){//保持内存中最多rawCnt个点数据
        m_vDataRaw.remove(0,qMin(newSize,m_vDataRaw.size()));
    }
    m_vDataRaw.append(pkt.raw);
    m_curveRaw.setSamples(m_vRawX,m_vDataRaw);

    // EEG数据
    //δ线
    if(m_vDataDelta.size()>=eegCnt){
        m_vDataDelta.pop_front();
    }
    m_vDataDelta.append(pkt.delta);
    m_curve[0].setSamples(m_vEEGX,m_vDataDelta);

    //高α线
    if(m_vDataHighAlpha.size()>=eegCnt){
        m_vDataHighAlpha.pop_front();
    }
    m_vDataHighAlpha.append(pkt.highAlpha);
    m_curve[1].setSamples(m_vEEGX,m_vDataHighAlpha);

    //高β线
    if(m_vDataHighBeta.size()>=eegCnt){
        m_vDataHighBeta.pop_front();
    }
    m_vDataHighBeta.append(pkt.highBeta);
    m_curve[2].setSamples(m_vEEGX,m_vDataHighBeta);

    //低α线
    if(m_vDataLowAlpha.size()>=eegCnt){
        m_vDataLowAlpha.pop_front();
    }
    m_vDataLowAlpha.append(pkt.lowAlpha);
    m_curve[3].setSamples(m_vEEGX,m_vDataLowAlpha);

    //低β线
    if(m_vDataLowBeta.size()>=eegCnt){
        m_vDataLowBeta.pop_front();
    }
    m_vDataLowBeta.append(pkt.lowBeta);
    m_curve[4].setSamples(m_vEEGX,m_vDataLowBeta);

    //低γ线
    if(m_vDataLowGamma.size()>=eegCnt){
        m_vDataLowGamma.pop_front();
    }
    m_vDataLowGamma.append(pkt.lowGamma);
    m_curve[5].setSamples(m_vEEGX,m_vDataLowGamma);

    //高γ线
    if(m_vDataMidGamma.size()>=eegCnt){
        m_vDataMidGamma.pop_front();
    }
    m_vDataMidGamma.append(pkt.midGamma);
    m_curve[6].setSamples(m_vEEGX,m_vDataMidGamma);

    //θ线
    if(m_vDataTheta.size()>=eegCnt){
        m_vDataTheta.pop_front();
    }
    m_vDataTheta.append(pkt.theta);
    m_curve[7].setSamples(m_vEEGX,m_vDataTheta);
}

//清空数据
void Curve::clear()
{
    m_vDataRaw.clear();
    m_curveRaw.setSamples(m_vRawX,m_vDataRaw);

    m_vDataDelta.clear();
    m_curve[0].setSamples(m_vEEGX,m_vDataDelta);

    m_vDataHighAlpha.clear();
    m_curve[1].setSamples(m_vEEGX,m_vDataHighAlpha);

    m_vDataHighBeta.clear();
    m_curve[2].setSamples(m_vEEGX,m_vDataHighBeta);

    m_vDataLowAlpha.clear();
    m_curve[3].setSamples(m_vEEGX,m_vDataLowAlpha);

    m_vDataLowBeta.clear();
    m_curve[4].setSamples(m_vEEGX,m_vDataLowBeta);

    m_vDataLowGamma.clear();
    m_curve[5].setSamples(m_vEEGX,m_vDataLowGamma);

    m_vDataMidGamma.clear();
    m_curve[6].setSamples(m_vEEGX,m_vDataMidGamma);

    m_vDataTheta.clear();
    m_curve[7].setSamples(m_vEEGX,m_vDataTheta);
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
    m_rawXMap.setPaintInterval( r.left(), r.right() );
    m_rawYMap.setPaintInterval( r.top(), r.bottom() );

    painter->setRenderHint( QPainter::Antialiasing,
                            m_curveRaw.testRenderHint( QwtPlotItem::RenderAntialiased ) );
    m_curveRaw.draw( painter, m_rawXMap, m_rawYMap, r );
    shiftDown( r, deltay );

    // eeg线
    for(int i=0;i<8;i++){
        m_eegXMap.setPaintInterval( r.left(), r.right() );
        m_eegYMap.setPaintInterval( r.top(), r.bottom() );
        painter->setRenderHint( QPainter::Antialiasing,
                                m_curve[i].testRenderHint( QwtPlotItem::RenderAntialiased ) );
        m_curve[i].draw( painter, m_eegXMap, m_eegYMap, r );
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
    m_curveRaw.setPen( Qt::red );
    m_curveRaw.setStyle( QwtPlotCurve::Lines );
    m_curveRaw.setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curveRaw.setSamples(m_vRawX,m_vDataRaw);

    //δ线
    m_curve[0].setPen( Qt::black );
    m_curve[0].setStyle( QwtPlotCurve::Lines );
    m_curve[0].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[0].setSamples(m_vEEGX,m_vDataDelta);

    //高α线
    m_curve[1].setPen( Qt::magenta );
    m_curve[1].setStyle( QwtPlotCurve::Lines );
    m_curve[1].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[1].setSamples(m_vEEGX,m_vDataHighAlpha);

    //低α线
    m_curve[2].setPen( Qt::darkBlue );
    m_curve[2].setStyle( QwtPlotCurve::Lines );
    m_curve[2].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[2].setSamples(m_vEEGX,m_vDataLowAlpha);

    //高β
    m_curve[3].setPen( Qt::darkCyan );
    m_curve[3].setStyle( QwtPlotCurve::Lines );
    m_curve[3].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[3].setSamples(m_vEEGX,m_vDataHighBeta);

    //低β
    m_curve[4].setPen( Qt::darkMagenta );
    m_curve[4].setStyle( QwtPlotCurve::Lines );
    m_curve[4].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[4].setSamples(m_vEEGX,m_vDataLowBeta);

    //低γ
    m_curve[5].setPen( Qt::darkGreen );
    m_curve[5].setStyle( QwtPlotCurve::Lines );
    m_curve[5].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[5].setSamples(m_vEEGX,m_vDataLowGamma);

    //中γ
    m_curve[6].setPen( Qt::darkRed );
    m_curve[6].setStyle( QwtPlotCurve::Lines );
    m_curve[6].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[6].setSamples(m_vEEGX,m_vDataMidGamma);

    //θ
    m_curve[7].setPen( Qt::darkYellow );
    m_curve[7].setStyle( QwtPlotCurve::Lines );
    m_curve[7].setRenderHint( QwtPlotItem::RenderAntialiased );
    m_curve[7].setSamples(m_vEEGX,m_vDataTheta);
}

void Curve::shiftDown(QRect &rect, int offset) const
{
    rect.translate(0, offset);
}
