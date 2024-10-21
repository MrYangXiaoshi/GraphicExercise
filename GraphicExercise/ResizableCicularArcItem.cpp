#include "ResizableCicularArcItem.h"

ResizableCicularArcItem::ResizableCicularArcItem(qreal x, qreal y, qreal width, qreal height)
    : circleRect(x, y, width, height) {
    circleRect2 = circleRect.adjusted(-15, -15, 15, 15);
    setFlag(QGraphicsItem::ItemIsMovable);
    updateControlPoints();
}

QRectF ResizableCicularArcItem::boundingRect() const
{
    return circleRect.adjusted(-400, -400, 400, 400);
}


void ResizableCicularArcItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(QColor(155, 155, 155, 0));
    painter->drawArc(circleRect, startAngle * 16, spanAngle * 16);

    painter->drawArc(circleRect2, startAngle * 16, spanAngle * 16);

    polygon.clear();
    polygon << controlPoints[0] << controlPoints[3];
    painter->drawPolyline(polygon);
    polygon.clear();
    polygon << controlPoints[1] << controlPoints[4];
    painter->drawPolyline(polygon);

    //������ƿ��Ƶ�
    ResizableItem::paint(painter, option, widget);
}

void ResizableCicularArcItem::updateControlPoints() {
    controlPoints.clear();
    controlPoints.append(getArcEndpoint(circleRect, startAngle));    // ���
    controlPoints.append(getArcEndpoint(circleRect, (spanAngle + startAngle))); // �յ�
    controlPoints.append(getArcCenterPoint(circleRect));    // �е�
    controlPoints.append(getArcEndpoint(circleRect2, startAngle));   // ���
    controlPoints.append(getArcEndpoint(circleRect2, (spanAngle + startAngle)));    // �յ�
    controlPoints.append(QPointF(getArcCenterPoint(circleRect2))); // �е�
}

void ResizableCicularArcItem::setCircleRect(const QRectF& newRect) {
    if (resizingIndex == 2) {
        circleRect = newRect;
    }
    else if(resizingIndex == 5){
        circleRect2 = newRect;
    }
    updateControlPoints();
    update();
}

QPoint ResizableCicularArcItem::getArcCenterPoint(QRectF& rectangle)
{
    int centerX = rectangle.x() + rectangle.width() / 2;
    int centerY = rectangle.y() + rectangle.height() / 2;

    int middleAngle = -startAngle - spanAngle / 2; // �� 1/16 ��Ϊ��λ
    double radians = middleAngle * M_PI / 180.0;

    double radiusX = rectangle.width() / 2.0;
    double radiusY = rectangle.height() / 2.0;

    int middlePointX = centerX + radiusX * cos(radians);
    int middlePointY = centerY + radiusY * sin(radians);

    return QPoint(middlePointX, middlePointY);
}

QPointF ResizableCicularArcItem::getArcEndpoint(QRectF& rectangle, double angle)
{
    // ������ε����ĵ�
    double centerX = rectangle.x() + rectangle.width() / 2.0;
    double centerY = rectangle.y() + rectangle.height() / 2.0;

    // ����뾶����Ⱥ͸߶ȵ�һ�룩
    double radiusX = rectangle.width() / 2.0;
    double radiusY = rectangle.height() / 2.0;

    // ���Ƕ�ת��Ϊ����
    double radians = -angle * M_PI / 180.0;

    // ����˵�����
    double x = centerX + radiusX * cos(radians);
    double y = centerY + radiusY * sin(radians);

    return QPointF(x, y);
}


double ResizableCicularArcItem::calculateAngle(QPointF& point)
{
    // ������ε����ĵ�
    QPointF center = circleRect.center();

    // ����Ӿ������ĵ������������
    double vectorX = point.x() - center.x();
    double vectorY = point.y() - center.y();

    // ����Ƕȣ����ȣ�
    double angleInRadians = atan2(vectorY, vectorX);

    // ������ת��Ϊ��
    double angleInDegrees = angleInRadians * 180.0 / M_PI;
    
    // ȷ���Ƕ��� 0 �� 360 ��֮��
    if (angleInDegrees < 0) {
        angleInDegrees += 360;
    }

    return -angleInDegrees;
}

double ResizableCicularArcItem::calculateSpanAngle(QPointF& point)
{
    // ������ε����ĵ�
    QPointF center = circleRect.center();

    // ����Ӿ������ĵ������������
    double vectorX = point.x() - center.x();
    double vectorY = point.y() - center.y();

    // ����Ƕȣ����ȣ�
    double angleInRadians = atan2(vectorY, vectorX);

    // ������ת��Ϊ��
    double angleInDegrees = angleInRadians * 180.0 / M_PI;

    angleInDegrees = -angleInDegrees - startAngle;

    // ȷ���Ƕ��� 0 �� 360 ��֮��
    if (angleInDegrees < 0) {
        angleInDegrees += 360;
    }

    return angleInDegrees;
}


void ResizableCicularArcItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (resizing && revealPoint) {
        QPointF center = circleRect.center(); // ��ȡ��ǰԲ��
        QPointF eventPos = event->pos();

        // �����µİ뾶������Բ�Ĳ���
        qreal newRadius = 0;
        switch (resizingIndex) {
        case 2: 
            newRadius = event->pos().y() - center.y();
            break;
        case 5: 
            newRadius = event->pos().y() - center.y(); 
            break;
        case 0:
            startAngle = calculateAngle(eventPos);
            break;
        case 1:
            spanAngle = calculateSpanAngle(eventPos);
            break;
        case 3:
            startAngle = calculateAngle(eventPos);
            break;
        case 4:
            spanAngle = calculateSpanAngle(eventPos);
            break;
        }

        updateControlPoints();
        update();

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
