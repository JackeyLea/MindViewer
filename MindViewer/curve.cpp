#include "curve.h"

Curve::Curve(QWidget *parent)
    :QFrame(parent)
{
    xMap.setScaleInterval(-0.5,10.5);
    yMap.setScaleInterval(-1.1,1.1);

    setFrameStyle( QFrame::Box | QFrame::Raised );
    setLineWidth( 2 );
    setMidLineWidth( 3 );

    for( int i = 0; i < Size; i++ )
    {
        xval[i] = double( i ) * 10.0 / double( Size - 1 );
        yval[i] = std::sin( xval[i] ) * std::cos( 2.0 * xval[i] );
    }

    populate();
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
    int deltay, i;

    QRect r = contentsRect();

    deltay = r.height() / CurvCnt - 1;

    r.setHeight( deltay );

    //  draw curves
    for ( i = 0; i < CurvCnt; i++ )
    {
        xMap.setPaintInterval( r.left(), r.right() );
        yMap.setPaintInterval( r.top(), r.bottom() );

        painter->setRenderHint( QPainter::Antialiasing,
            m_curves[i].testRenderHint( QwtPlotItem::RenderAntialiased ) );
        m_curves[i].draw( painter, xMap, yMap, r );

        shiftDown( r, deltay );
    }

    // draw titles
    r = contentsRect();
    painter->setFont( QFont( "Helvetica", 8 ) );

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
    int i=0;

    m_curves[i].setPen( Qt::red );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::black );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::magenta );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::darkBlue );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::darkCyan );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::darkGray );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::darkGreen );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::darkRed );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    m_curves[i].setPen( Qt::darkYellow );
    m_curves[i].setStyle( QwtPlotCurve::Lines );
    m_curves[i].setRenderHint( QwtPlotItem::RenderAntialiased );
    i++;

    // TODO
    for( i = 0; i < CurvCnt; i++ )
        m_curves[i].setRawSamples( xval, yval, Size );
}

void Curve::shiftDown(QRect &rect, int offset) const
{
    rect.translate(0, offset);
}
