#ifndef ONECURVE_H
#define ONECURVE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QRgba64>
#include <QRgb>

class OneCurve : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int pointCount READ getPointCount WRITE setPointCount NOTIFY pointCountChanged)
    Q_PROPERTY(int spaceCount READ getSpaceCount WRITE setSpaceCount NOTIFY spaceCountChanged)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QFont lineFont READ getLineFont WRITE setLineFont NOTIFY lineFontChanged)
    Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(int yMin READ getYMin WRITE setYMin NOTIFY yMinChanged)
    Q_PROPERTY(int yMax READ getYMax WRITE setYMax NOTIFY yMaxChanged)
public:
    OneCurve(QQuickItem* parent = nullptr);

    void paint(QPainter* painter) override;

    Q_INVOKABLE void appendPoint(int y);

    int getYMin() const;
    void setYMin(int value);

    int getYMax() const;
    void setYMax(int value);

    int getPointCount() const;
    void setPointCount(int pointCount);

    int getSpaceCount() const;
    void setSpaceCount(int spaceCount);

    const QList<QPointF>& getPoints() const;
    void setPoints(const QList<QPointF>& points);

    const QColor& getLineColor() const;
    void setLineColor(const QColor& newLineColor);

    const QFont& getLineFont() const;
    void setLineFont(const QFont& newLineFont);

    int getLineWidth() const;
    void setLineWidth(int newLineWidth);

signals:
    void pointCountChanged();
    void spaceCountChanged();
    void yMinChanged();
    void yMaxChanged();
    void lineColorChanged();
    void lineFontChanged();
    void lineWidthChanged();

private:
    void drawLine(QPainter* painter);
    QPointF transformPoint(const QPointF& pt) const;

private:
    int                       myPointCount{60};
    int                       mySpaceCount{10};
    QColor                    myLineColor;
    QFont                     myLineFont;
    int                       myLineWidth;
    int                       myYMaxValue{100};
    int                       myYMinValue{};
    QList<QPointF>            myPoints;
    int                       myCurrentPointIndex{};
    int                       myXStart{};
    int                       myXEnd{};
    int                       myYStart{};
    int                       myYEnd{};
};

#endif // ONECURVE_H
