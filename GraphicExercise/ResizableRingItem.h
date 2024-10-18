#pragma once
#include "ResizableItem.h"

class ResizableRingItem :
    public ResizableItem
{
public:
    ResizableRingItem::ResizableRingItem();

    virtual QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    //QPolygonF polygon;
    QRectF circleRect1;
    QRectF circleRect2;

    bool unSetted;

    // Í¨¹ý ResizableItem ¼Ì³Ð
    virtual void updateControlPoints() override;
};

