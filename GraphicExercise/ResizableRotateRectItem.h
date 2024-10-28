#pragma once
#include "ResizableItem.h"

class ResizableRotateRectItem :
    public ResizableItem
{
public:
    ResizableRotateRectItem(qreal x, qreal y, qreal width, qreal height);

    // 通过 ResizableItem 继承
    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

    void updateControlPoints() override;

    void setRect(const QRectF& newRect);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QRectF rect;
    QPolygonF polygon_user;
    QTransform transform;
    

    void rotateRect(const QPointF& currentPos); // 旋转函数
};

