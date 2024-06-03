#include "onecurve.h"

OneCurve::OneCurve(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{}
void OneCurve::paint(QPainter* painter)
{
    if (!painter) {
        return;
    }

    myXStart = myGridLineWidth;
    myXEnd = width() - myGridLineWidth;
    myYStart = myGridLineWidth;
    myYEnd = height() - myGridLineWidth;

    // The drawing order cannot be changed,
    // because there are dependencies between them
    drawTitle(painter);
    drawLabels(painter);
    drawGridLine(painter);
    drawLine(painter);
}

void OneCurve::appendPoint(int y)
{
    if (myPointCount <= 0) {
        return;
    }
    if (myPoints.size() < myPointCount) {
        myCurrentPointIndex = 0;
        myPoints.push_back(QPointF{static_cast<double>(myPoints.size()), static_cast<double>(y)});
    } else {
        myPoints[myCurrentPointIndex].setY(y);
        ++myCurrentPointIndex;
        myCurrentPointIndex = myCurrentPointIndex % myPoints.size();
    }

    update();
}

int OneCurve::getYMin() const
{
    return myYMinValue;
}

void OneCurve::setYMin(int value)
{
    if (myYMinValue == value) {
        return;
    }
    myYMinValue = value;
    emit yMinChanged();
    update();
}

int OneCurve::getYMax() const
{
    return myYMaxValue;
}

void OneCurve::setYMax(int value)
{
    if (myYMaxValue == value) {
        return;
    }
    myYMaxValue = value;
    emit yMaxChanged();
    update();
}

int OneCurve::getYTickCount() const
{
    return myYTickCount;
}

void OneCurve::setYTickCount(int tickCount)
{
    if (myYTickCount == tickCount) {
        return;
    }
    if (tickCount <= 0) {
        return;
    }
    myYTickCount = tickCount;
    emit yTickCountChanged();
}

bool OneCurve::getYLineVisible() const
{
    return myYLineVisible;
}

void OneCurve::setYLineVisible(bool newYLineVisible)
{
    if (myYLineVisible == newYLineVisible) {
        return;
    }
    myYLineVisible = newYLineVisible;
    emit yLineVisibleChanged();
}

bool OneCurve::getXLineVisible() const
{
    return myXLineVisible;
}

void OneCurve::setXLineVisible(bool newXLineVisible)
{
    if (myXLineVisible == newXLineVisible) {
        return;
    }
    myXLineVisible = newXLineVisible;
    emit xLineVisibleChanged();
}

int OneCurve::getXTickCount() const
{
    return myXTickCount;
}

void OneCurve::setXTickCount(int tickCount)
{
    if (myXTickCount == tickCount) {
        return;
    }
    if (tickCount <= 0) {
        return;
    }
    myXTickCount = tickCount;
    emit xTickCountChanged();
}

int OneCurve::getPointCount() const
{
    return myPointCount;
}

void OneCurve::setPointCount(int pointCount)
{
    if (myPointCount == pointCount) {
        return;
    }
    if (pointCount <= 0) {
        return;
    }
    myPointCount = pointCount;

    // remove old point(s)
    myCurrentPointIndex = 0;
    if (myPoints.size() > pointCount) {
        myPoints.erase(myPoints.begin(), myPoints.begin() + (myPoints.size() - pointCount));
    }

    emit pointCountChanged();
    update();
}

int OneCurve::getSpaceCount() const
{
    return mySpaceCount;
}

void OneCurve::setSpaceCount(int spaceCount)
{
    if (mySpaceCount == spaceCount) {
        return;
    }
    if (spaceCount < 0) {
        return;
    }
    mySpaceCount = spaceCount;
    emit spaceCountChanged();
}

const QList<QPointF>& OneCurve::getPoints() const
{
    return myPoints;
}

void OneCurve::setPoints(const QList<QPointF>& points)
{
    if (myPoints == points) {
        return;
    }
    myPoints = points;
    update();
}

const QString& OneCurve::getTitle() const
{
    return myTitle;
}

void OneCurve::setTitle(const QString& title)
{
    if (myTitle == title) {
        return;
    }
    myTitle = title;
    emit titleChanged();
    update();
}

const QFont& OneCurve::getTitleFont() const
{
    return myTitleFont;
}

void OneCurve::setTitleFont(const QFont& font)
{
    if (myTitleFont == font)
        return;
    myTitleFont = font;
    emit titleFontChanged();
}

const QColor& OneCurve::getTitleColor() const
{
    return myTitleColor;
}

void OneCurve::setTitleColor(const QColor& color)
{
    if (myTitleColor == color) {
        return;
    }
    myTitleColor = color;
    emit titleColorChanged();
    update();
}

const QColor& OneCurve::getLineColor() const
{
    return myLineColor;
}

void OneCurve::setLineColor(const QColor& newLineColor)
{
    if (myLineColor == newLineColor) {
        return;
    }
    myLineColor = newLineColor;
    emit lineColorChanged();
}

const QColor& OneCurve::getGridLineColor() const
{
    return myGridLineColor;
}

void OneCurve::setGridLineColor(const QColor& newGridLineColor)
{
    if (myGridLineColor == newGridLineColor)
        return;
    myGridLineColor = newGridLineColor;
    emit gridLineColorChanged();
}

const QFont& OneCurve::getLineFont() const
{
    return myLineFont;
}

void OneCurve::setLineFont(const QFont& newLineFont)
{
    if (myLineFont == newLineFont) {
        return;
    }
    myLineFont = newLineFont;
    emit lineFontChanged();
}

const QFont& OneCurve::getGridLineFont() const
{
    return myGridLineFont;
}

void OneCurve::setGridLineFont(const QFont& newGridLineFont)
{
    if (myGridLineFont == newGridLineFont) {
        return;
    }
    myGridLineFont = newGridLineFont;
    emit gridLineFontChanged();
}

int OneCurve::getGridLineWidth() const
{
    return myGridLineWidth;
}

void OneCurve::setGridLineWidth(int newGridLineWidth)
{
    if (myGridLineWidth == newGridLineWidth) {
        return;
    }
    myGridLineWidth = newGridLineWidth;
    emit gridLineWidthChanged();
}

int OneCurve::getLineWidth() const
{
    return myLineWidth;
}

void OneCurve::setLineWidth(int newLineWidth)
{
    if (myLineWidth == newLineWidth) {
        return;
    }
    myLineWidth = newLineWidth;
    emit lineWidthChanged();
}


bool OneCurve::getLabelsVisible() const
{
    return myLabelsVisible;
}

void OneCurve::setLabelsVisible(bool newLabelsVisible)
{
    if (myLabelsVisible == newLabelsVisible) {
        return;
    }
    myLabelsVisible = newLabelsVisible;
    emit labelsVisibleChanged();
}

const QFont& OneCurve::getLabelsFont() const
{
    return myLabelsFont;
}

void OneCurve::setLabelsFont(const QFont& newLabelsFont)
{
    if (myLabelsFont == newLabelsFont) {
        return;
    }
    myLabelsFont = newLabelsFont;
    emit labelsFontChanged();
}

const QColor& OneCurve::getLabelsColor() const
{
    return myLabelsColor;
}

void OneCurve::setLabelsColor(const QColor& newLabelsColor)
{
    if (myLabelsColor == newLabelsColor) {
        return;
    }
    myLabelsColor = newLabelsColor;
    emit labelsColorChanged();
}

void OneCurve::drawTitle(QPainter* painter)
{
    if (!myTitle.isEmpty()) {
        QFontMetrics metrics(myTitleFont, painter->device());
        int titleHeight = metrics.height() + 10;
        myYStart += titleHeight;

        painter->save();
        QPen pen = painter->pen();
        pen.setColor(myTitleColor);
        painter->setPen(pen);
        painter->setFont(myTitleFont);
        painter->drawText(0, 0, width(), titleHeight, Qt::AlignCenter, myTitle);
        painter->restore();
    }
}

void OneCurve::drawLabels(QPainter* painter)
{
    if (myLabelsVisible) {
        painter->save();
        QPen pen = painter->pen();
        pen.setColor(myLabelsColor);
        painter->setPen(pen);
        painter->setFont(myLabelsFont);
        const QRect rc = painter->boundingRect(myXStart, myYStart, myXEnd - myXStart, myYEnd - myYStart
                                               , Qt::AlignLeft, QString::number(myYMaxValue) + "W");

        auto fnDrawLabel = [&](const QRect& rc, int val) {
            painter->drawText(rc, Qt::AlignCenter, QString::number(val));
        };

        QRect labelRect{myXStart, myYStart, rc.width(), rc.height()};
        fnDrawLabel(labelRect, myYMaxValue);

        int valueSpace = (myYMaxValue - myYMinValue) / myYTickCount;
        int curValue = myYMaxValue - valueSpace;
        int yLineSpace = (myYEnd - myYStart) / myYTickCount;
        for (int i = 1; i < myYTickCount; ++i) {
            labelRect.setY(myYStart + i * yLineSpace * 2 - rc.height());
            fnDrawLabel(labelRect, curValue);
            curValue -= valueSpace;
        }

        labelRect.setRect(myXStart, myYEnd - rc.height(), rc.width(), rc.height());
        fnDrawLabel(labelRect, myYMinValue);

        myXStart += rc.width();
        painter->restore();
    }
}

void OneCurve::drawGridLine(QPainter* painter)
{
    QPainterPath linePath;
    if (myXLineVisible) {
        int xLineSpace = (myXEnd - myXStart) / myXTickCount;
        for (int i = 1; i < myXTickCount; ++i) {
            int xPos = myXStart + xLineSpace * i;
            linePath.moveTo(xPos, myYStart);
            linePath.lineTo(xPos, myYEnd);
        }
    }
    if (myYLineVisible) {
        int yLineSpace = (myYEnd - myYStart) / myYTickCount;
        for (int i = 1; i < myYTickCount; ++i) {
            int yPos = myYStart + yLineSpace * i;
            linePath.moveTo(myXStart, yPos);
            linePath.lineTo(myXEnd, yPos);
        }
    }
    if (!linePath.isEmpty()) {
        painter->save();
        QPen pen = painter->pen();
        pen.setColor(myGridLineColor);
        pen.setStyle(Qt::CustomDashLine);
        pen.setDashPattern(QVector<qreal>{8, 10});
        pen.setWidth(myGridLineWidth);
        painter->setPen(pen);
        painter->drawPath(linePath);
        painter->setFont(myGridLineFont);
        painter->restore();
    }
}

void OneCurve::drawLine(QPainter* painter)
{
    if (!myPoints.isEmpty()) {
        QPainterPath ptPath;
        ptPath.moveTo(transformPoint(myPoints.at(0)));

        if (myCurrentPointIndex > 0) {
            int i = 0;
            for (; i < myCurrentPointIndex; ++i) {
                ptPath.lineTo(transformPoint(myPoints.at(i)));
            }

            i = myCurrentPointIndex + mySpaceCount;
            if (i < myPoints.size()) {
                ptPath.moveTo(transformPoint(myPoints.at(i)));
                for (; i < myPoints.size(); ++i) {
                    ptPath.lineTo(transformPoint(myPoints.at(i)));
                }
            }
        } else {
            for (int i = 1; i < myPoints.size(); ++i) {
                ptPath.lineTo(transformPoint(myPoints.at(i)));
            }
        }

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        QPen pen = painter->pen();
        pen.setColor(myLineColor);
        pen.setWidth(myLineWidth);
        painter->setPen(pen);
        painter->drawPath(ptPath);
        painter->setFont(myLineFont);
        painter->restore();
    }
}

QPointF OneCurve::transformPoint(const QPointF& pt) const
{
    int pointCount = myPointCount > 0 ? myPointCount : 1;
    int w = myXEnd - myXStart;
    auto x = pt.x() * w / pointCount + myXStart;

    int h = myYEnd - myYStart;
    auto y = h - pt.y() * h / (myYMaxValue - myYMinValue) + myYStart;
    if (y < myYStart) {
        y = myYStart;
    } else if (y > myYEnd) {
        y = myYEnd;
    }

    return QPointF{x, y};
}
