#include "ResizableRectItem.h"

ResizableRectItem::ResizableRectItem(qreal x, qreal y, qreal width, qreal height) : rect(x, y, width, height)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    updateControlPoints();
}

QRectF ResizableRectItem::boundingRect() const
{
    return rect.adjusted(-400, -400, 400, 400);
}

void ResizableRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    painter->drawRect(rect);

    ResizableItem::paint(painter, option, widget);
}

//更新控制点
void ResizableRectItem::updateControlPoints()
{
    controlPoints.clear();
    controlPoints.append(QPointF(rect.left(), rect.top()));              // 左上
    controlPoints.append(QPointF(rect.right(), rect.top()));             // 右上
    controlPoints.append(QPointF(rect.right(), rect.bottom()));          // 右下
    controlPoints.append(QPointF(rect.left(), rect.bottom()));           // 左下
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.top()));    // 上中
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.bottom())); // 下中
    controlPoints.append(QPointF(rect.left(), (rect.top() + rect.bottom()) / 2));    // 左中
    controlPoints.append(QPointF(rect.right(), (rect.top() + rect.bottom()) / 2));   // 右中
}

//更新控制点、重新绘图
void ResizableRectItem::setRect(const QRectF& newRect)
{
    rect = newRect;
    updateControlPoints();
    update();
}

//鼠标移动事件
void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //判断当前鼠标是否按压在控制点上
    if (resizing && revealPoint) {
        switch (resizingIndex) {
        case 0: // 左上
            setRect(QRectF(event->pos().x(), event->pos().y(), rect.right() - event->pos().x(), rect.bottom() - event->pos().y()));
            break;
        case 1: // 右上
            setRect(QRectF(rect.left(), event->pos().y(), event->pos().x() - rect.left(), rect.bottom() - event->pos().y()));
            break;
        case 2: // 右下
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), event->pos().y() - rect.top()));
            break;
        case 3: // 左下
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), event->pos().y() - rect.top()));
            break;
        case 4: // 上中
            setRect(QRectF(rect.left(), event->pos().y(), rect.width(), rect.bottom() - event->pos().y()));
            break;
        case 5: // 下中
            setRect(QRectF(rect.left(), rect.top(), rect.width(), event->pos().y() - rect.top()));
            break;
        case 6: // 左中
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), rect.height()));
            break;
        case 7: // 右中
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), rect.height()));
            break;
        }
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
