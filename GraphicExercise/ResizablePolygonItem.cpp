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

    polygon.clear();
    for (const auto& point : controlPoints) {
        polygon << controlPoints;
        qDebug() << controlPoints;
    }
    //���������
    if (unSetted) {
        painter->drawPolyline(controlPoints.data(), controlPoints.size());
    }
    else {
        painter->drawPolygon(polygon);
        roiPoly = polygon;
    }
    
    ResizableItem::paint(painter, option, widget);
}

void ResizablePolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //�жϵ�ǰ����Ƿ�ѹ�ڿ��Ƶ���
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
            //controlPoints.append(controlPoints[0]);//���ĵ㲻��Ҫappend���Ե�һ����Ϊ�յ�
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
