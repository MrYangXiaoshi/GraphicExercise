#pragma once
#include "ResizableItem.h"

class ResizableRingItem :
    public ResizableItem
{
public:
    ResizableRingItem(qreal x, qreal y, qreal width, qreal height);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF circleRect;
    QRectF circleRect2;

    void updateControlPoints();
    void setCircleRect(const QRectF& newRect);
};

