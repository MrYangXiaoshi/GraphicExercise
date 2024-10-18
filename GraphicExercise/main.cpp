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
    //// ����һ���ɵ�����С��λ�õľ�����
    ///*ResizableRectItem* rectItem = new ResizableRectItem(100, 100, 200, 100);
    //scene.addItem(rectItem);*/

    ////��ת����
    ///*ResizableRotateRectItem* rotateRect = new ResizableRotateRectItem(100, 100, 200, 100);
    //scene.addItem(rotateRect);*/

    ////��Բ
    ///*ResizableEllipseItem* ellipse = new ResizableEllipseItem(50, 50, 50, 50);
    //scene.addItem(ellipse);*/

    ////�����
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
