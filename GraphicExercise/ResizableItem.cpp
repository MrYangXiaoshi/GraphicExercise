#include "ResizableItem.h"

void ResizableItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    qDebug() << "ResizableRectItem::paint::revealPoint:" << revealPoint;
    // 绘制控制点
    if (revealPoint) {
        painter->setPen(QPen(Qt::magenta));
        painter->setBrush(Qt::magenta);
        for (const auto& point : controlPoints) {
            painter->drawRect(point.x() - 3, point.y() - 3, 6, 6);
        }
    }
}

void ResizableItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    for (int i = 0; i < controlPoints.size(); ++i) {
        //按压在某个控制点且控制点显示的情况下
        if (QRectF(controlPoints[i].x() - 3, controlPoints[i].y() - 3, 6, 6).contains(event->pos())) {
            resizingIndex = i;
            resizing = true;
            return;
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void ResizableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    resizing = false;
    qDebug() << " ResizableItem::mouseReleaseEvent::resizing:" << resizing;
    QGraphicsItem::mouseReleaseEvent(event);
}

void ResizableItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    revealPoint = (!revealPoint);
    qDebug() << "revealPoint:" << revealPoint;
    update();
}
