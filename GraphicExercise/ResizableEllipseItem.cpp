#include "ResizableEllipseItem.h"

ResizableEllipseItem::ResizableEllipseItem(qreal x, qreal y, qreal width, qreal height)
    : ellipseRect(x, y, width, height) {
    setFlag(QGraphicsItem::ItemIsMovable);
    updateControlPoints();
}

QRectF ResizableEllipseItem::boundingRect() const {
    return ellipseRect.adjusted(-400, -400, 400, 400);
}

void ResizableEllipseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    painter->drawEllipse(ellipseRect);

    //父类绘制控制点
    ResizableItem::paint(painter, option, widget);
}

void ResizableEllipseItem::updateControlPoints() {
    controlPoints.clear();
    controlPoints.append(QPointF((ellipseRect.left() + ellipseRect.right()) / 2, ellipseRect.top()));    // 上
    controlPoints.append(QPointF((ellipseRect.left() + ellipseRect.right()) / 2, ellipseRect.bottom())); // 下
    controlPoints.append(QPointF(ellipseRect.left(), (ellipseRect.top() + ellipseRect.bottom()) / 2));    // 左
    controlPoints.append(QPointF(ellipseRect.right(), (ellipseRect.top() + ellipseRect.bottom()) / 2));   // 右
}

void ResizableEllipseItem::setEllipseRect(const QRectF& newRect) {
    ellipseRect = newRect;
    updateControlPoints();
    update();
}

void ResizableEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (resizing && revealPoint) {
        switch (resizingIndex) {
        case 0: // 上
            setEllipseRect(QRectF(ellipseRect.left(), event->pos().y(), ellipseRect.width(), ellipseRect.bottom() - event->pos().y()));
            break;
        case 1: // 下
            setEllipseRect(QRectF(ellipseRect.left(), ellipseRect.top(), ellipseRect.width(), event->pos().y() - ellipseRect.top()));
            break;
        case 2: // 左
            setEllipseRect(QRectF(event->pos().x(), ellipseRect.top(), ellipseRect.right() - event->pos().x(), ellipseRect.height()));
            break;
        case 3: // 右
            setEllipseRect(QRectF(ellipseRect.left(), ellipseRect.top(), event->pos().x() - ellipseRect.left(), ellipseRect.height()));
            break;
        }
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
