#pragma once
#include "ResizableItem.h"
class ResizableCircleItem :
    public ResizableItem
{
public:
    ResizableCircleItem(qreal x, qreal y, qreal width, qreal height);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF circleRect;

    void updateControlPoints();
    void setCircleRect(const QRectF& newRect);
};

