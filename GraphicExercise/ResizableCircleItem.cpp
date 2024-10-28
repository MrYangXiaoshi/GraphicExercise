#include "ResizableCircleItem.h"

ResizableCircleItem::ResizableCircleItem(qreal x, qreal y, qreal width, qreal height)
    : circleRect(x, y, width, height) {
    setFlag(QGraphicsItem::ItemIsMovable);
    updateControlPoints();
}

QRectF ResizableCircleItem::boundingRect() const
{
    return circleRect.adjusted(-400, -400, 400, 400);
}


void ResizableCircleItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    painter->drawEllipse(circleRect);

    //父类绘制控制点
    ResizableItem::paint(painter, option, widget);
}

void ResizableCircleItem::updateControlPoints() {
    controlPoints.clear();
    controlPoints.append(QPointF((circleRect.left() + circleRect.right()) / 2, circleRect.top()));    // 上
    controlPoints.append(QPointF((circleRect.left() + circleRect.right()) / 2, circleRect.bottom())); // 下
    controlPoints.append(QPointF(circleRect.left(), (circleRect.top() + circleRect.bottom()) / 2));    // 左
    controlPoints.append(QPointF(circleRect.right(), (circleRect.top() + circleRect.bottom()) / 2));   // 右

    //记录roi关键点
    roiPoly.clear();
    roiPoly << controlPoints[0] << controlPoints[1] << controlPoints[2] << controlPoints[3];
    qDebug() << "roiPoly" << roiPoly << "####";
}

void ResizableCircleItem::setCircleRect(const QRectF& newRect) {
    circleRect = newRect;
    updateControlPoints();
    update();
}

void ResizableCircleItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (resizing && revealPoint) {
        QPointF center = circleRect.center(); // 获取当前圆心

        // 计算新的半径，保持圆心不变
        qreal newRadius = 0;
        switch (resizingIndex) {
        case 0: // 上
            newRadius = center.y() - event->pos().y(); // 计算上边缘新位置
            break;
        case 1: // 下
            newRadius = event->pos().y() - center.y(); // 计算下边缘新位置
            break;
        case 2: // 左
            newRadius = center.x() - event->pos().x(); // 计算左边缘新位置
            break;
        case 3: // 右
            newRadius = event->pos().x() - center.x(); // 计算右边缘新位置
            break;
        }

        // 确保半径为正值
        if (newRadius < 0) {
            newRadius = -newRadius;
        }
        setCircleRect(QRectF(center.x() - newRadius, center.y() - newRadius, newRadius * 2, newRadius * 2));
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}