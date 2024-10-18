#include "GraphicExercise.h"
#include "ResizableRectItem.h"
#include "ResizableRotateRectItem.h"
#include "ResizableEllipseItem.h"
#include "ResizablePolygonItem.h"
#include <QVBoxLayout>
#include <QPushButton>

GraphicExercise::GraphicExercise(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "GraphicExercise###";
    QVBoxLayout* layout = new QVBoxLayout(this);
    QGraphicsScene* scene = new QGraphicsScene(this);

    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(Qt::black);
    view->setSceneRect(0, 0, 400, 400);

    QPushButton* rectButton = new QPushButton("Add Rectangle");
    QPushButton* ellipseButton = new QPushButton("Add Ellipse");
    QPushButton* polygonButton = new QPushButton("Add Polygon");

    connect(rectButton, &QPushButton::clicked, [scene]() {
        QGraphicsRectItem* rectItem = new QGraphicsRectItem(100, 100, 200, 100);
        rectItem->setBrush(Qt::green);
        scene->addItem(rectItem);
        });

    connect(ellipseButton, &QPushButton::clicked, [scene]() {
        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(50, 50, 100, 50);
        ellipseItem->setBrush(Qt::blue);
        scene->addItem(ellipseItem);
        });

    connect(polygonButton, &QPushButton::clicked, [scene]() {
        ResizablePolygonItem* polygon = new ResizablePolygonItem();
        scene->addItem(polygon);
        });

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(rectButton);
    buttonLayout->addWidget(ellipseButton);
    buttonLayout->addWidget(polygonButton);

    layout->addWidget(view);
    layout->addLayout(buttonLayout);
    setLayout(layout);
    //ui.setupUi(this);
}

GraphicExercise::~GraphicExercise()
{}
