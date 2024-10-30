///////////////////
/// \author JackeyLea
/// \date 2024-10-30
/// \note 指示器类
///////////////////

#ifndef INDICATOR_H
#define INDICATOR_H

#include <QString>
#include <QwtDial>

class Indicator : public QwtDial
{
public:
    Indicator(QWidget *parent = nullptr);

    void setLabel( const QString& );
    QString label() const;

protected:
    virtual void drawScaleContents( QPainter* painter,
                                   const QPointF& center, double radius ) const QWT_OVERRIDE;

private:
    QString m_label;
};

#endif // INDICATOR_H
