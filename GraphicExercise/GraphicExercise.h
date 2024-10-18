#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GraphicExercise.h"
#include "ResizableRectItem.h"
#include "ResizableRotateRectItem.h"
#include "ResizableEllipseItem.h"
#include "ResizablePolygonItem.h"

class GraphicExercise : public QMainWindow
{
    Q_OBJECT

public:
    GraphicExercise(QWidget *parent = nullptr);
    ~GraphicExercise();

private:
    Ui::GraphicExerciseClass ui;
    //´´½¨³¡¾°
    QGraphicsScene scene;

private slots:
    void onButtonRectClicked();
    void onButtonRotateRectClicked();
    void onButtonEllipseClicked();
    void onButtonPolygonClicked();
    void onButtonRingClicked();
    void onButtonCicularArcClicked();
    void onButtonCircleClicked();
};
