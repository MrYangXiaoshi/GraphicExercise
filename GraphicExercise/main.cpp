#include "GraphicExercise.h"
#include "ResizableRectItem.h"
#include "ResizableRotateRectItem.h"
#include "ResizableEllipseItem.h"
#include "ResizablePolygonItem.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GraphicExercise exercise;
    exercise.show();

    return app.exec();
}
