#include "ResizableRotateRectItem.h"

ResizableRotateRectItem::ResizableRotateRectItem(qreal x, qreal y, qreal width, qreal height) : rect(x, y, width, height)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    updateControlPoints();
}

QRectF ResizableRotateRectItem::boundingRect() const
{
    return rect.adjusted(-400, -400, 400, 400);
}

void ResizableRotateRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    //painter->drawRect(rect);

    polygon_user.clear();//�ؼӣ��ȿӣ�
    polygon_user << controlPoints[7];
    for (int i = 0; i < 9; i++) {
        polygon_user << controlPoints[i];
    }
    qDebug() << controlPoints;

    //����һ����
    painter->drawPolyline(polygon_user);
    ResizableItem::paint(painter, option, widget);
}

void ResizableRotateRectItem::updateControlPoints()
{
    controlPoints.clear();
    controlPoints.append(QPointF(rect.left(), rect.top()));              // ����0
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.top()));    // ����
    controlPoints.append(QPointF(rect.right(), rect.top()));             // ����2
    controlPoints.append(QPointF(rect.right(), (rect.top() + rect.bottom()) / 2));   // ����
    controlPoints.append(QPointF(rect.right(), rect.bottom()));          //����4
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.bottom())); // ����
    controlPoints.append(QPointF(rect.left(), rect.bottom()));           // ����6
    controlPoints.append(QPointF(rect.left(), (rect.top() + rect.bottom()) / 2));    // ����
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, (rect.top() + rect.bottom()) / 2));//����
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.top() - 10));    // ������ת��
    
    //����roi�����
    roiPoly.clear();
    roiPoly << controlPoints[0] << controlPoints[2] << controlPoints[4] << controlPoints[6];
    qDebug() << "newPoly" << roiPoly << "####";
}

void ResizableRotateRectItem::setRect(const QRectF& newRect)
{
    rect = newRect;
    updateControlPoints();
    update();
}

void ResizableRotateRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //�жϵ�ǰ����Ƿ�ѹ�ڿ��Ƶ���
    if (resizing && revealPoint) {
        switch (resizingIndex) {
        case 0: // ����
            setRect(QRectF(event->pos().x(), event->pos().y(), rect.right() - event->pos().x(), rect.bottom() - event->pos().y()));// ����
            break;
        case 1: // ����
            setRect(QRectF(rect.left(), event->pos().y(), rect.width(), rect.bottom() - event->pos().y()));// ����
            break;
        case 2: // ����
            setRect(QRectF(rect.left(), event->pos().y(), event->pos().x() - rect.left(), rect.bottom() - event->pos().y())); // ���� 
            break;
        case 3:// ����
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), rect.height()));// ����
            break;
        case 4:  // ����
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), event->pos().y() - rect.top())); // ����
            break;
        case 5: // ����
            setRect(QRectF(rect.left(), rect.top(), rect.width(), event->pos().y() - rect.top())); // ����
            break;
        case 6: // ����
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), event->pos().y() - rect.top()));// ����
            break;
        case 7: // ����
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), rect.height())); // ����
            break;
        case 9://��ת��
            qDebug() << "case 9";
            rotateRect(event->pos());
            qDebug() << "case 9";
            break;
        }
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void ResizableRotateRectItem::rotateRect(const QPointF& currentPos)
{
    setTransformOriginPoint(rect.center()); // ������תԭ��Ϊ��Բ����
    setRotation(rotation() + 1); // ������ת�Ƕ�
}
