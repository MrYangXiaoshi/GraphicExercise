#pragma once
#include "ResizableItem.h"
#define M_PI 3.14159265358979323846
class ResizableCicularArcItem :
    public ResizableItem
{
public:
    ResizableCicularArcItem(qreal x, qreal y, qreal width, qreal height);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF circleRect;
    QRectF circleRect2;
    int startAngle = 60; // 起始角度
    int spanAngle = 90; // 跨度角度
    QPolygonF polygon;

    void updateControlPoints();
    void setCircleRect(const QRectF& newRect);
    QPoint getArcCenterPoint(QRectF& rectangle);
    QPointF getArcEndpoint(QRectF& rectangle, double angle);
    double calculateAngle(QPointF& point);
    double calculateSpanAngle(QPointF& point);
};

