#include "GraphicExercise.h"
#include <filesystem>

using namespace cv;

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
    view->setFixedSize(720, 540);
    layout->addWidget(view);
    view->setBackgroundBrush(Qt::black);
    view->setScene(&scene);

    //OpenCV,背景图片
    Mat mat = imread("C:\\AAA-Temp\\新建文件夹\\2023_04_19_15_37_05_612.bmp");
    if (mat.empty()) {
        qDebug() << "Failed to load image!";
    }
    else {
        qDebug() << "mat.rows:" << mat.rows << " mat.cols:" << mat.cols;
    }
    QImage qImage = MatToQImage(mat);
    QPixmap backgroundPixmap = QPixmap::fromImage(qImage);
    scene.setBackgroundBrush(backgroundPixmap);
    backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    backgroundItem->setParentItem(nullptr); // 确保其生命周期独立于场景
    scene.addItem(backgroundItem);

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




QImage GraphicExercise::MatToQImage(const Mat& mat)
{
    // 如果是灰度图像
    if (mat.type() == CV_8UC1)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    }
    // 如果是RGB图像
    else if (mat.type() == CV_8UC3)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    }
    // 如果是带有alpha通道的图像
    else if (mat.type() == CV_8UC4)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
    }
    else
    {
        return QImage();
    }
}

void GraphicExercise::keepOneItem()
{
    // 获取场景中的所有图形项
    QList<QGraphicsItem*> items = scene.items();

    // 遍历所有图形项，并删除所有不等于背景图项的其他项
    for (QGraphicsItem* item : items) {
        if (item != backgroundItem) {
            scene.removeItem(item); // 从场景中移除
            delete item;            // 删除图形项，确保内存被正确释放
        }
    }
}

void GraphicExercise::onButtonRectClicked() {
    keepOneItem();
    ResizableRectItem* rectItem = new ResizableRectItem(100, 100, 200, 100);
    scene.addItem(rectItem);
}

void GraphicExercise::onButtonRotateRectClicked() {
    keepOneItem();
    ResizableRotateRectItem* rotateRect = new ResizableRotateRectItem(100, 100, 200, 100);
    scene.addItem(rotateRect);
}

void GraphicExercise::onButtonEllipseClicked() {
    keepOneItem();
    ResizableEllipseItem* ellipse = new ResizableEllipseItem(50, 50, 50, 100);
    scene.addItem(ellipse);
}

void GraphicExercise::onButtonPolygonClicked() {
    keepOneItem();
    ResizablePolygonItem* polygon = new ResizablePolygonItem();
    scene.addItem(polygon);
}


void GraphicExercise::onButtonCircleClicked()
{
    keepOneItem();
    ResizableCircleItem* circle = new ResizableCircleItem(50, 50, 50, 50);
    scene.addItem(circle);
}

void GraphicExercise::onButtonRingClicked()
{
    keepOneItem();
    ResizableRingItem* ring = new ResizableRingItem(150, 150, 50, 50);
    scene.addItem(ring);
}

void GraphicExercise::onButtonCicularArcClicked()
{
    keepOneItem();
    ResizableCicularArcItem* cicularArc = new ResizableCicularArcItem(200, 200, 150, 150);
    scene.addItem(cicularArc);
}

