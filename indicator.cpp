#include "indicator.h"

#include "qwt_dial_needle.h"
#include "qwt_round_scale_draw.h"

#include <QPainter>

Indicator::Indicator( QWidget* parent )
    : QwtDial( parent )
    , m_label( "" )
{
    QwtRoundScaleDraw* scaleDraw = new QwtRoundScaleDraw();
    scaleDraw->setSpacing( 8 );
    scaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, false );
    scaleDraw->setTickLength( QwtScaleDiv::MinorTick, 0 );
    scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 4 );
    scaleDraw->setTickLength( QwtScaleDiv::MajorTick, 8 );
    scaleDraw->setPenWidthF( 2 );
    setScaleDraw( scaleDraw );

    setScaleStepSize( 20.0 );
    setScale( 0.0, 100.0 );

    setWrapping( false );
    setReadOnly( true );

    setOrigin( 135.0 );
    setScaleArc( 0.0, 270.0 );

    QwtDialSimpleNeedle* needle = new QwtDialSimpleNeedle(
        QwtDialSimpleNeedle::Arrow, true, Qt::red,
        QColor( Qt::gray ).lighter( 130 ) );
    setNeedle( needle );
}

void Indicator::setLabel( const QString& label )
{
    m_label = label;
    update();
}

void Indicator::drawScaleContents( QPainter* painter,
                                    const QPointF& center, double radius ) const
{
    QRectF rect( 0.0, 0.0, 2.0 * radius, 2.0 * radius - 10.0 );
    rect.moveCenter( center );

    const QColor color = palette().color( QPalette::Text );
    painter->setPen( color );

    const int flags = Qt::AlignBottom | Qt::AlignHCenter;
    painter->drawText( rect, flags, m_label );
}
