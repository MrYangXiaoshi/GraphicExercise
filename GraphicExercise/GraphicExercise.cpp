#include "GraphicExercise.h"
#include "ResizableRectItem.h"
#include "ResizableRotateRectItem.h"
#include "ResizableEllipseItem.h"
#include "ResizablePolygonItem.h"
#include "ResizableCircleItem.h"
#include "ResizableRingItem.h"
#include <QVBoxLayout>
#include <QPushButton>

GraphicExercise::GraphicExercise(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "GraphicExercise###";

    ui.setupUi(this);

    // 创建一个 QWidget 作为 central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建水平布局
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);

    // 创建左侧视图
    QGraphicsView* view = new QGraphicsView(centralWidget);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(400, 400);
    layout->addWidget(view);
    view->setBackgroundBrush(Qt::black);
    view->setScene(&scene);

    // 创建右侧按钮列
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    QPushButton* buttonRect = new QPushButton("Rect", centralWidget);
    QPushButton* buttonRotateRect = new QPushButton("RotateRect", centralWidget);
    QPushButton* buttonEllipse = new QPushButton("Ellipse", centralWidget);
    QPushButton* buttonPolygon = new QPushButton("Polygon", centralWidget);

    QPushButton* buttonCircle = new QPushButton("Circle", centralWidget);
    QPushButton* buttonRing = new QPushButton("Ring", centralWidget);
    QPushButton* buttonCicularArc = new QPushButton("CicularArc", centralWidget);

    // 连接信号和槽
    connect(buttonRect, &QPushButton::clicked, this, &GraphicExercise::onButtonRectClicked);
    connect(buttonRotateRect, &QPushButton::clicked, this, &GraphicExercise::onButtonRotateRectClicked);
    connect(buttonEllipse, &QPushButton::clicked, this, &GraphicExercise::onButtonEllipseClicked);
    connect(buttonPolygon, &QPushButton::clicked, this, &GraphicExercise::onButtonPolygonClicked);
    connect(buttonCircle, &QPushButton::clicked, this, &GraphicExercise::onButtonCircleClicked);
    connect(buttonRing, &QPushButton::clicked, this, &GraphicExercise::onButtonRingClicked);
    connect(buttonCicularArc, &QPushButton::clicked, this, &GraphicExercise::onButtonCicularArcClicked);


    buttonLayout->addWidget(buttonRect);
    buttonLayout->addWidget(buttonRotateRect);
    buttonLayout->addWidget(buttonEllipse);
    buttonLayout->addWidget(buttonPolygon);
    buttonLayout->addWidget(buttonCircle);
    buttonLayout->addWidget(buttonRing);
    buttonLayout->addWidget(buttonCicularArc);

    layout->addLayout(buttonLayout);
}

GraphicExercise::~GraphicExercise()
{}

void GraphicExercise::onButtonRectClicked() {
    scene.clear();
    ResizableRectItem* rectItem = new ResizableRectItem(100, 100, 200, 100);
    scene.addItem(rectItem);
}

void GraphicExercise::onButtonRotateRectClicked() {
    scene.clear();
    ResizableRotateRectItem* rotateRect = new ResizableRotateRectItem(100, 100, 200, 100);
    scene.addItem(rotateRect);
}

void GraphicExercise::onButtonEllipseClicked() {
    scene.clear();
    ResizableEllipseItem* ellipse = new ResizableEllipseItem(50, 50, 50, 100);
    scene.addItem(ellipse);
}

void GraphicExercise::onButtonPolygonClicked() {
    scene.clear();
    ResizablePolygonItem* polygon = new ResizablePolygonItem();
    scene.addItem(polygon);
}


void GraphicExercise::onButtonCircleClicked()
{
    scene.clear();
    ResizableCircleItem* circle = new ResizableCircleItem(50, 50, 50, 50);
    scene.addItem(circle);
}

void GraphicExercise::onButtonRingClicked()
{
    scene.clear();
    ResizableRingItem* ring = new ResizableRingItem(50, 50, 50, 50);
    scene.addItem(ring);
}

void GraphicExercise::onButtonCicularArcClicked()
{
    scene.clear();
}

