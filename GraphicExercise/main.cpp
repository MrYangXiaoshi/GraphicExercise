#include "GraphicExercise.h"
#include "ResizableRectItem.h"
#include "ResizableRotateRectItem.h"
#include "ResizableEllipseItem.h"
#include "ResizablePolygonItem.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    //QGraphicsScene scene;
    //
    //// 创建一个可调整大小和位置的矩形项
    ///*ResizableRectItem* rectItem = new ResizableRectItem(100, 100, 200, 100);
    //scene.addItem(rectItem);*/

    ////旋转矩形
    ///*ResizableRotateRectItem* rotateRect = new ResizableRotateRectItem(100, 100, 200, 100);
    //scene.addItem(rotateRect);*/

    ////椭圆
    ///*ResizableEllipseItem* ellipse = new ResizableEllipseItem(50, 50, 50, 50);
    //scene.addItem(ellipse);*/

    ////多边形
    //ResizablePolygonItem* polygon = new ResizablePolygonItem();
    ////scene.setBackgroundBrush(Qt::gray);
    //scene.addItem(polygon);

    //QGraphicsView view(&scene);
    //view.setRenderHint(QPainter::Antialiasing);
    //view.setBackgroundBrush(Qt::black);
    //view.setSceneRect(0, 0, 400, 400);
    ///*view.setFixedSize(400, 400);*/
    //view.show();

    GraphicExercise exercise;
    exercise.resize(400, 400);
    exercise.show();

    return app.exec();
}
