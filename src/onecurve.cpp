#include "onecurve.h"

OneCurve::OneCurve(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{
    myGridLineColor = qRgba(127, 0, 0, 255);
}

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
