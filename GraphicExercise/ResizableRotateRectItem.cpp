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

    polygon_user.clear();//必加（踩坑）
    polygon_user << controlPoints[7];
    for (int i = 0; i < 9; i++) {
        polygon_user << controlPoints[i];
    }
    qDebug() << controlPoints;

    //画出一条线
    painter->drawPolyline(polygon_user);
    ResizableItem::paint(painter, option, widget);
}

void ResizableRotateRectItem::updateControlPoints()
{
    controlPoints.clear();
    controlPoints.append(QPointF(rect.left(), rect.top()));              // 左上0
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.top()));    // 上中
    controlPoints.append(QPointF(rect.right(), rect.top()));             // 右上2
    controlPoints.append(QPointF(rect.right(), (rect.top() + rect.bottom()) / 2));   // 右中
    controlPoints.append(QPointF(rect.right(), rect.bottom()));          //右下4
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.bottom())); // 下中
    controlPoints.append(QPointF(rect.left(), rect.bottom()));           // 左下6
    controlPoints.append(QPointF(rect.left(), (rect.top() + rect.bottom()) / 2));    // 左中
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, (rect.top() + rect.bottom()) / 2));//中心
    controlPoints.append(QPointF((rect.left() + rect.right()) / 2, rect.top() - 10));    // 上中旋转点
    
    //设置roi多边形
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
    //判断当前鼠标是否按压在控制点上
    if (resizing && revealPoint) {
        switch (resizingIndex) {
        case 0: // 左上
            setRect(QRectF(event->pos().x(), event->pos().y(), rect.right() - event->pos().x(), rect.bottom() - event->pos().y()));// 左上
            break;
        case 1: // 上中
            setRect(QRectF(rect.left(), event->pos().y(), rect.width(), rect.bottom() - event->pos().y()));// 上中
            break;
        case 2: // 右上
            setRect(QRectF(rect.left(), event->pos().y(), event->pos().x() - rect.left(), rect.bottom() - event->pos().y())); // 右上 
            break;
        case 3:// 右中
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), rect.height()));// 右中
            break;
        case 4:  // 右下
            setRect(QRectF(rect.left(), rect.top(), event->pos().x() - rect.left(), event->pos().y() - rect.top())); // 右下
            break;
        case 5: // 下中
            setRect(QRectF(rect.left(), rect.top(), rect.width(), event->pos().y() - rect.top())); // 下中
            break;
        case 6: // 左下
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), event->pos().y() - rect.top()));// 左下
            break;
        case 7: // 左中
            setRect(QRectF(event->pos().x(), rect.top(), rect.right() - event->pos().x(), rect.height())); // 左中
            break;
        case 9://旋转点
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
    setTransformOriginPoint(rect.center()); // 设置旋转原点为椭圆中心
    setRotation(rotation() + 1); // 设置旋转角度
}
