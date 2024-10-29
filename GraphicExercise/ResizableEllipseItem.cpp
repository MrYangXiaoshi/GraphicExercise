#include "ResizableEllipseItem.h"

ResizableEllipseItem::ResizableEllipseItem(qreal x, qreal y, qreal width, qreal height)
    : ellipseRect(x, y, width, height) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
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

    //������ƿ��Ƶ�
    ResizableItem::paint(painter, option, widget);
}

void ResizableEllipseItem::addFivePoints()
{
    QVector<QPointF> points;

    // ��Բ������
    QPointF center = ellipseRect.center();

    // ����Ͷ���İ뾶
    double a = ellipseRect.width() / 2.0;  // �볤��
    double b = ellipseRect.height() / 2.0; // �����

    // �����ĽǶȣ�0�㡢72�㡢144�㡢216�㡢288�㣩
    const double angles[5] = { 0.0, 72.0, 144.0, 216.0, 288.0 };

    // ������Բ�ϵ������
    for (double angle : angles) {
        // ת��Ϊ����
        double radians = qDegreesToRadians(angle);

        // ����������
        double x = center.x() + a * std::cos(radians);
        double y = center.y() + b * std::sin(radians);

        points.append(QPointF(x, y));
    }
    roiPoly << points;
}

void ResizableEllipseItem::updateControlPoints() {
    controlPoints.clear();
    controlPoints.append(QPointF((ellipseRect.left() + ellipseRect.right()) / 2, ellipseRect.top()));    // ��
    controlPoints.append(QPointF((ellipseRect.left() + ellipseRect.right()) / 2, ellipseRect.bottom())); // ��
    controlPoints.append(QPointF(ellipseRect.left(), (ellipseRect.top() + ellipseRect.bottom()) / 2));    // ��
    controlPoints.append(QPointF(ellipseRect.right(), (ellipseRect.top() + ellipseRect.bottom()) / 2));   // ��

    // ��ת���Ƶ�����Ϸ�һ������
    QPointF rotateControlPoint = controlPoints[0] + QPointF(0, -10);  // ���Ϸ�������ת���Ƶ�
    controlPoints.append(rotateControlPoint);

    //��¼roi�ؼ���
    roiPoly.clear();
    roiPoly << controlPoints[0] << controlPoints[1] << controlPoints[2] << controlPoints[3];
    addFivePoints();    
    qDebug() << "roiPoly" << roiPoly;
}

void ResizableEllipseItem::setEllipseRect(const QRectF& newRect) {
    ellipseRect = newRect;
    updateControlPoints();
    update();
}

void ResizableEllipseItem::rotateEllipse(const QPointF& currentPos) {
    // ��Բ��ת
    setTransformOriginPoint(ellipseRect.center()); // ������תԭ��Ϊ��Բ����
    setRotation(rotation() + 1); // ������ת�Ƕ�
}

void ResizableEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (resizing && revealPoint) {
        switch (resizingIndex) {
        case 0: // ��
            setEllipseRect(QRectF(ellipseRect.left(), event->pos().y(), ellipseRect.width(), ellipseRect.bottom() - event->pos().y()));
            break;
        case 1: // ��
            setEllipseRect(QRectF(ellipseRect.left(), ellipseRect.top(), ellipseRect.width(), event->pos().y() - ellipseRect.top()));
            break;
        case 2: // ��
            setEllipseRect(QRectF(event->pos().x(), ellipseRect.top(), ellipseRect.right() - event->pos().x(), ellipseRect.height()));
            break;
        case 3: // ��
            setEllipseRect(QRectF(ellipseRect.left(), ellipseRect.top(), event->pos().x() - ellipseRect.left(), ellipseRect.height()));
            break;
        case 4: // ��ת���Ƶ�
            rotateEllipse(event->pos());
            break;
        }
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
