#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_GraphicExercise.h"
#include "ResizableRectItem.h"
#include "ResizableRotateRectItem.h"
#include "ResizableEllipseItem.h"
#include "ResizablePolygonItem.h"
#include "ResizableCircleItem.h"
#include "ResizableRingItem.h"
#include "ResizableCicularArcItem.h"
#include <opencv2/opencv.hpp>
#include <QVBoxLayout>
#include <QPushButton>

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
    QGraphicsPixmapItem* backgroundItem;
    QImage MatToQImage(const cv::Mat& mat);
    void keepOneItem();

private slots:
    void onButtonRectClicked();
    void onButtonRotateRectClicked();
    void onButtonEllipseClicked();
    void onButtonPolygonClicked();
    void onButtonRingClicked();
    void onButtonCicularArcClicked();
    void onButtonCircleClicked();
};
