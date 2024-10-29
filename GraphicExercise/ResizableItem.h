#pragma once
#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <qdebug.h>
#include <QtMath>

class ResizableItem :
    public QGraphicsItem
{
public:
    // 设置多边形
    QVector<QPointF> roiPoly;

    virtual void updateControlPoints() = 0;

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    bool revealPoint = true;//控制点是否显示
    bool resizing = false;//是否可以改变大小
    QVector<QPointF> controlPoints;//控制点列表
    int resizingIndex = -1;//当前按压控制点下标

    //鼠标按压事件，判断按压哪个点
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    //鼠标释放事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    //鼠标双击改变控制点显示状态
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};

