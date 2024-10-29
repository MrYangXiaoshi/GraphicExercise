#include "ResizableRingItem.h"

ResizableRingItem::ResizableRingItem(qreal x, qreal y, qreal width, qreal height)
    : circleRect(x, y, width, height) {
    circleRect2 = circleRect.adjusted(-10, -10, 10, 10);
    setFlag(QGraphicsItem::ItemIsMovable);
    updateControlPoints();
}

QRectF ResizableRingItem::boundingRect() const
{
    return circleRect.adjusted(-400, -400, 400, 400);
}

void ResizableRingItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    painter->drawEllipse(circleRect);
    painter->drawEllipse(circleRect2);
    //������ƿ��Ƶ�
    ResizableItem::paint(painter, option, widget);
}

void ResizableRingItem::updateControlPoints() {
    controlPoints.clear();
    controlPoints.append(QPointF((circleRect.left() + circleRect.right()) / 2, circleRect.top()));    // ��
    controlPoints.append(QPointF((circleRect.left() + circleRect.right()) / 2, circleRect.bottom())); // ��
    controlPoints.append(QPointF(circleRect.left(), (circleRect.top() + circleRect.bottom()) / 2));    // ��
    controlPoints.append(QPointF(circleRect.right(), (circleRect.top() + circleRect.bottom()) / 2));   // ��
    controlPoints.append(QPointF((circleRect2.left() + circleRect2.right()) / 2, circleRect2.top()));    // ��
    controlPoints.append(QPointF((circleRect2.left() + circleRect2.right()) / 2, circleRect2.bottom())); // ��
    controlPoints.append(QPointF(circleRect2.left(), (circleRect2.top() + circleRect2.bottom()) / 2));    // ��
    controlPoints.append(QPointF(circleRect2.right(), (circleRect2.top() + circleRect2.bottom()) / 2));   // ��

    //��¼roi�ؼ���
    roiPoly.clear();
    roiPoly << controlPoints[0] << controlPoints[1] << controlPoints[2] << controlPoints[3]
        << controlPoints[4] << controlPoints[5] << controlPoints[6] << controlPoints[7];
    qDebug() << "roiPoly" << roiPoly << "####";
}

void ResizableRingItem::setCircleRect(const QRectF& newRect) {
    if (resizingIndex < 4) {
        circleRect = newRect;
    }
    else {
        circleRect2 = newRect;
    }
    updateControlPoints();
    update();
}

void ResizableRingItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (resizing && revealPoint) {
        QPointF center = circleRect.center(); // ��ȡ��ǰԲ��

        // �����µİ뾶������Բ�Ĳ���
        qreal newRadius = 0;
        switch (resizingIndex) {
        case 0: // ��
            newRadius = center.y() - event->pos().y(); // �����ϱ�Ե��λ��
            break;
        case 1: // ��
            newRadius = event->pos().y() - center.y(); // �����±�Ե��λ��
            break;
        case 2: // ��
            newRadius = center.x() - event->pos().x(); // �������Ե��λ��
            break;
        case 3: // ��
            newRadius = event->pos().x() - center.x(); // �����ұ�Ե��λ��
            break;
        case 4: // ��
            newRadius = center.y() - event->pos().y(); // �����ϱ�Ե��λ��
            break;
        case 5: // ��
            newRadius = event->pos().y() - center.y(); // �����±�Ե��λ��
            break;
        case 6: // ��
            newRadius = center.x() - event->pos().x(); // �������Ե��λ��
            break;
        case 7: // ��
            newRadius = event->pos().x() - center.x(); // �����ұ�Ե��λ��
            break;
        }

        // ȷ���뾶Ϊ��ֵ
        if (newRadius < 0) {
            newRadius = -newRadius;
        }
        setCircleRect(QRectF(center.x() - newRadius, center.y() - newRadius, newRadius * 2, newRadius * 2));
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}