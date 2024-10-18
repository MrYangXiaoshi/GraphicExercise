#include "ResizableRingItem.h"


ResizableRingItem::ResizableRingItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    controlPoints.clear();
    unSetted = true;

}

QRectF ResizableRingItem::boundingRect() const
{
    return circleRect1.adjusted(-400, -400, 400, 400);
}

void ResizableRingItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));

    //polygon.clear();
    for (const auto& point : controlPoints) {
        //polygon << controlPoints;
        qDebug() << controlPoints;
    }
    //画出多边形
    //painter->drawPolygon(polygon);

    ResizableItem::paint(painter, option, widget);
}

void ResizableRingItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //判断当前鼠标是否按压在控制点上
    if (resizing && revealPoint) {
        controlPoints[resizingIndex] = event->pos();
        update();
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void ResizableRingItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{

    if (unSetted) {
        if (!resizing) {
            controlPoints.append(event->pos());
        }
        else if (QRectF(controlPoints[0].x() - 3, controlPoints[0].y() - 3, 6, 6).contains(event->pos())) {
            controlPoints.append(controlPoints[0]);
            unSetted = false;
        }
        else {
            QGraphicsItem::hoverLeaveEvent(event);
        }
        update();
    }
}

void ResizableRingItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (unSetted) {
        if (!resizing) {
            controlPoints.append(event->pos());
        }
        else if (QRectF(controlPoints[0].x() - 3, controlPoints[0].y() - 3, 6, 6).contains(event->pos())) {
            controlPoints.append(controlPoints[0]);
            unSetted = false;
        }
        else {
            //QGraphicsItem::mouseReleaseEvent(event);
            qDebug() << "ResizablePolygonItem::mouseReleaseEvent";
        }
        update();
    }
    ResizableItem::mouseReleaseEvent(event);
}

void ResizableRingItem::updateControlPoints()
{
    controlPoints.clear();

    qDebug() << "ResizablePolygonItem::updateControlPoints()::controlPoints.clear()";
}
