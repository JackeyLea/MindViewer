#ifndef ONECURVE_H
#define ONECURVE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPainterPath>

class OneCurve : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int pointCount READ getPointCount WRITE setPointCount NOTIFY pointCountChanged)
    Q_PROPERTY(int spaceCount READ getSpaceCount WRITE setSpaceCount NOTIFY spaceCountChanged)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QColor gridLineColor READ getGridLineColor WRITE setGridLineColor NOTIFY gridLineColorChanged)
    Q_PROPERTY(QFont lineFont READ getLineFont WRITE setLineFont NOTIFY lineFontChanged)
    Q_PROPERTY(QFont gridLineFont READ getGridLineFont WRITE setGridLineFont NOTIFY gridLineFontChanged)
    Q_PROPERTY(bool xLineVisible READ getXLineVisible WRITE setXLineVisible NOTIFY xLineVisibleChanged)
    Q_PROPERTY(bool yLineVisible READ getYLineVisible WRITE setYLineVisible NOTIFY yLineVisibleChanged)
    Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(int gridLineWidth READ getGridLineWidth WRITE setGridLineWidth NOTIFY gridLineWidthChanged)
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

    bool getXLineVisible() const;
    void setXLineVisible(bool newXLineVisible);

    bool getYLineVisible() const;
    void setYLineVisible(bool newYLineVisible);

    int getPointCount() const;
    void setPointCount(int pointCount);

    int getSpaceCount() const;
    void setSpaceCount(int spaceCount);

    const QList<QPointF>& getPoints() const;
    void setPoints(const QList<QPointF>& points);

    const QColor& getLineColor() const;
    void setLineColor(const QColor& newLineColor);

    const QColor& getGridLineColor() const;
    void setGridLineColor(const QColor& newGridLineColor);

    const QFont& getLineFont() const;
    void setLineFont(const QFont& newLineFont);

    const QFont& getGridLineFont() const;
    void setGridLineFont(const QFont& newGridLineFont);

    int getLineWidth() const;
    void setLineWidth(int newLineWidth);

    int getGridLineWidth() const;
    void setGridLineWidth(int newGridLineWidth);

signals:
    void pointCountChanged();
    void spaceCountChanged();
    void yMinChanged();
    void yMaxChanged();
    void xLineVisibleChanged();
    void yLineVisibleChanged();
    void lineColorChanged();
    void gridLineColorChanged();
    void lineFontChanged();
    void gridLineFontChanged();
    void lineWidthChanged();
    void gridLineWidthChanged();

private:
    void drawGridLine(QPainter* painter);
    void drawLine(QPainter* painter);
    QPointF transformPoint(const QPointF& pt) const;

private:
    int                       myPointCount{60};
    int                       mySpaceCount{10};
    int                       myXTickCount{10};
    int                       myYTickCount{6};
    bool                      myXLineVisible{};
    bool                      myYLineVisible{};
    QColor                    myLineColor;
    QColor                    myGridLineColor;
    QFont                     myLineFont;
    QFont                     myGridLineFont;
    int                       myLineWidth;
    int                       myGridLineWidth;
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
