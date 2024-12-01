///////////////////
/// \author JackeyLea
/// \date 2024-10-30
/// \note 指示器类
///////////////////

#ifndef INDICATOR_H
#define INDICATOR_H

#include <QString>
#include <QWidget>
#include "qwt_dial.h"

class Indicator : public QwtDial
{
public:
    /// 构造函数
    /// \brief Indicator
    /// \param parent
    ///
    explicit Indicator(QWidget *parent = nullptr);

    /// 仪表名
    /// \brief setLabel
    ///
    void setLabel( const QString& );

protected:
    /// 绘图
    /// \brief drawScaleContents
    /// \param painter
    /// \param center
    /// \param radius
    ///
    virtual void drawScaleContents( QPainter* painter,
                                   const QPointF& center, double radius ) const QWT_OVERRIDE;

private:
    QString m_label;//仪表名称
};

#endif // INDICATOR_H
