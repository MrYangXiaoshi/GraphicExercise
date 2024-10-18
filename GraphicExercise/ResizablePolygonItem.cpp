#include "ResizablePolygonItem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>

ResizablePolygonItem::ResizablePolygonItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    controlPoints.clear();
    unSetted = true;
    
}

QRectF ResizablePolygonItem::boundingRect() const
{
    return polygon.boundingRect().adjusted(-400, -400, 400, 400);
}

void ResizablePolygonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    //polygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(100, 100) << QPointF(0, 100);
    //updateControlPoints();

    polygon.clear();
    for (const auto& point : controlPoints) {
        polygon << controlPoints;
        qDebug() << controlPoints;
    }
    //画出多边形
    painter->drawPolygon(polygon);

    ResizableItem::paint(painter, option, widget);
}

void ResizablePolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
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

void ResizablePolygonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
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

void ResizablePolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
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

void ResizablePolygonItem::updateControlPoints()
{
    controlPoints.clear();
           
    qDebug() << "ResizablePolygonItem::updateControlPoints()::controlPoints.clear()";
}
