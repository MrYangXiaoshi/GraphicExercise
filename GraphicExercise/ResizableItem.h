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
    // ���ö����
    QVector<QPointF> roiPoly;

    virtual void updateControlPoints() = 0;

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    bool revealPoint = true;//���Ƶ��Ƿ���ʾ
    bool resizing = false;//�Ƿ���Ըı��С
    QVector<QPointF> controlPoints;//���Ƶ��б�
    int resizingIndex = -1;//��ǰ��ѹ���Ƶ��±�

    //��갴ѹ�¼����жϰ�ѹ�ĸ���
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    //����ͷ��¼�
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    //���˫���ı���Ƶ���ʾ״̬
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
};

