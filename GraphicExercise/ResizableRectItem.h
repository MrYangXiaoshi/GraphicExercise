#pragma once
#include "ResizableItem.h"

class ResizableRectItem :
    public ResizableItem,
    public QGraphicsPolygonItem
{
public:
    ResizableRectItem(qreal x, qreal y, qreal width, qreal height);

    // Í¨¹ý ResizableItem ¼Ì³Ð
    virtual void updateControlPoints() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

    void setRect(const QRectF& newRect);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF rect;
};

