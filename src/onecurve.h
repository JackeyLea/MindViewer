#ifndef ONECURVE_H
#define ONECURVE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPainterPath>

class OneCurve : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QFont titleFont READ getTitleFont WRITE setTitleFont NOTIFY titleFontChanged)
    Q_PROPERTY(QColor titleColor READ getTitleColor WRITE setTitleColor NOTIFY titleColorChanged)
    Q_PROPERTY(int pointCount READ getPointCount WRITE setPointCount NOTIFY pointCountChanged)
    Q_PROPERTY(int spaceCount READ getSpaceCount WRITE setSpaceCount NOTIFY spaceCountChanged)
    Q_PROPERTY(int xTickCount READ getXTickCount WRITE setXTickCount NOTIFY xTickCountChanged)
    Q_PROPERTY(int yTickCount READ getYTickCount WRITE setYTickCount NOTIFY yTickCountChanged)
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
    Q_PROPERTY(bool labelsVisible READ getLabelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)
    Q_PROPERTY(QColor labelsColor READ getLabelsColor WRITE setLabelsColor NOTIFY labelsColorChanged)
    Q_PROPERTY(QFont labelsFont READ getLabelsFont WRITE setLabelsFont NOTIFY labelsFontChanged)
public:
    OneCurve(QQuickItem* parent = nullptr);

    void paint(QPainter* painter) override;

    Q_INVOKABLE void appendPoint(int y);

    int getYMin() const;
    void setYMin(int value);

    int getYMax() const;
    void setYMax(int value);

    int getXTickCount() const;
    void setXTickCount(int tickCount);

    int getYTickCount() const;
    void setYTickCount(int tickCount);

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

    const QString& getTitle() const;
    void setTitle(const QString& title);

    const QFont& getTitleFont() const;
    void setTitleFont(const QFont& font);

    const QColor& getTitleColor() const;
    void setTitleColor(const QColor& color);

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

    bool getLabelsVisible() const;
    void setLabelsVisible(bool newLabelsVisible);

    const QColor& getLabelsColor() const;
    void setLabelsColor(const QColor& newLabelsColor);

    const QFont& getLabelsFont() const;
    void setLabelsFont(const QFont& newLabelsFont);

signals:
    void titleChanged();
    void titleFontChanged();
    void titleColorChanged();
    void pointCountChanged();
    void spaceCountChanged();
    void yMinChanged();
    void yMaxChanged();
    void xTickCountChanged();
    void yTickCountChanged();
    void xLineVisibleChanged();
    void yLineVisibleChanged();
    void lineColorChanged();
    void gridLineColorChanged();
    void lineFontChanged();
    void gridLineFontChanged();
    void lineWidthChanged();
    void gridLineWidthChanged();
    void labelsVisibleChanged();
    void labelsColorChanged();
    void labelsFontChanged();

private:
    void drawTitle(QPainter* painter);
    void drawLabels(QPainter* painter);
    void drawGridLine(QPainter* painter);
    void drawLine(QPainter* painter);
    QPointF transformPoint(const QPointF& pt) const;

private:
    QString                   myTitle;
    QFont                     myTitleFont;
    QColor                    myTitleColor;
    int                       myPointCount{60};
    int                       mySpaceCount{10};
    int                       myXTickCount{1};
    int                       myYTickCount{1};
    bool                      myXLineVisible{};
    bool                      myYLineVisible{};
    QColor                    myLineColor;
    QColor                    myGridLineColor;
    QFont                     myLineFont;
    QFont                     myGridLineFont;
    int                       myLineWidth;
    int                       myGridLineWidth;
    bool                      myLabelsVisible{true};
    QColor                    myLabelsColor;
    QFont                     myLabelsFont;
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
