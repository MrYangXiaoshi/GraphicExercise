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

//���¿��Ƶ�
void ResizableRectItem::updateControlPoints()
{
    controlPoints.clear();
    controlPoints.append(QPointF(rect.left(), rect.top()));              // ����
    controlPoints.append(QPointF(rect.right(), rect.top()));             // ����
    controlPoints.append(QPointF(rect.right(), rect.bottom()));          // ����
    controlPoints.append(QPointF(rect.left(), rect.bottom()));           // ����
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.top()));    // ����
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.bottom())); // ����
    controlPoints.append(QPointF(rect.left(), (rect.top() + rect.bottom()) / 2));    // ����
    controlPoints.append(QPointF(rect.right(), (rect.top() + rect.bottom()) / 2));   // ����
}

//���¿��Ƶ㡢���»�ͼ
void ResizableRectItem::setRect(const QRectF& newRect)
{
    rect = newRect;
    updateControlPoints();
    update();
}

//����ƶ��¼�
void ResizableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //�жϵ�ǰ����Ƿ�ѹ�ڿ��Ƶ���
    if (resizing && revealPoint) {
        switch (resizingIndex) {
        case 0: // ����
            setRect(QRectF(event->pos().x(), event->pos().y(), rect.right() - event->pos().x(), rect.bottom() - event->pos().y()));
            break;
        case 1: // ����
            setRect(QRectF(rect.left(), event->pos().y(), event->pos().x() - rect.left(), rect.bottom() - event->pos().y()));
            break;
        case 2: // ����
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), event->pos().y() - rect.top()));
            break;
        case 3: // ����
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), event->pos().y() - rect.top()));
            break;
        case 4: // ����
            setRect(QRectF(rect.left(), event->pos().y(), rect.width(), rect.bottom() - event->pos().y()));
            break;
        case 5: // ����
            setRect(QRectF(rect.left(), rect.top(), rect.width(), event->pos().y() - rect.top()));
            break;
        case 6: // ����
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), rect.height()));
            break;
        case 7: // ����
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), rect.height()));
            break;
        }
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
