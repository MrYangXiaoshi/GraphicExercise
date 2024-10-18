#pragma once
#include <qgraphicsitem.h>
#include "ResizableItem.h"

class ResizablePolygonItem :
    public ResizableItem
{
public:
    ResizablePolygonItem::ResizablePolygonItem();

    virtual QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    QPolygonF polygon;

    bool unSetted;

    // 通过 ResizableItem 继承
    virtual void updateControlPoints() override;
    
    //设置初始图形
    void setControlPoints(QGraphicsSceneMouseEvent* event);
};

