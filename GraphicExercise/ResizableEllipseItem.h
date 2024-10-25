#ifndef RESIZABLEELLIPSEITEM_H
#define RESIZABLEELLIPSEITEM_H

#include "ResizableItem.h"

class ResizableEllipseItem : public ResizableItem {
public:
    ResizableEllipseItem(qreal x, qreal y, qreal width, qreal height);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF ellipseRect;

    void updateControlPoints();
    void setEllipseRect(const QRectF& newRect);
    void rotateEllipse(const QPointF& currentPos); // Ðý×ªº¯Êý
};

#endif // RESIZABLEELLIPSEITEM_H
