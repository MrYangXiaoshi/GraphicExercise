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
    view->setFixedSize(740, 660);
    layout->addWidget(view);
    view->setBackgroundBrush(Qt::black);
    view->setScene(&scene);

    //OpenCV,背景图片
    image = imread("C:\\AAA-Temp\\新建文件夹\\2023_04_19_15_37_05_612.bmp");
    if (image.empty()) {
        qDebug() << "Failed to load image!";
    }
    else {
        qDebug() << "mat.rows:" << image.rows << " mat.cols:" << image.cols;
    }
    QImage qImage = MatToQImage(image);
    QPixmap backgroundPixmap = QPixmap::fromImage(qImage);
    scene.setBackgroundBrush(backgroundPixmap);
    backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    backgroundItem->setTransformOriginPoint(0, 0);
    scene.addItem(backgroundItem);
    backgroundItem->setPos(0, 0);

    // 创建右侧按钮列
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    QPushButton* buttonRect = new QPushButton("Rect", centralWidget);
    QPushButton* buttonRotateRect = new QPushButton("RotateRect", centralWidget);
    QPushButton* buttonEllipse = new QPushButton("Ellipse", centralWidget);
    QPushButton* buttonPolygon = new QPushButton("Polygon", centralWidget);

    QPushButton* buttonCircle = new QPushButton("Circle", centralWidget);
    QPushButton* buttonRing = new QPushButton("Ring", centralWidget);
    QPushButton* buttonCicularArc = new QPushButton("CicularArc", centralWidget);
    QPushButton* buttonImageHandle = new QPushButton("ImageHandle", centralWidget);
    buttonImageHandle->setStyleSheet("background-color: yellow;");

    // 连接信号和槽
    connect(buttonRect, &QPushButton::clicked, this, &GraphicExercise::onButtonRectClicked);
    connect(buttonRotateRect, &QPushButton::clicked, this, &GraphicExercise::onButtonRotateRectClicked);
    connect(buttonEllipse, &QPushButton::clicked, this, &GraphicExercise::onButtonEllipseClicked);
    connect(buttonPolygon, &QPushButton::clicked, this, &GraphicExercise::onButtonPolygonClicked);
    connect(buttonCircle, &QPushButton::clicked, this, &GraphicExercise::onButtonCircleClicked);
    connect(buttonRing, &QPushButton::clicked, this, &GraphicExercise::onButtonRingClicked);
    connect(buttonCicularArc, &QPushButton::clicked, this, &GraphicExercise::onButtonCicularArcClicked);
    connect(buttonImageHandle, &QPushButton::clicked, this, &GraphicExercise::onButtonImageHandleClicked);

    buttonLayout->addWidget(buttonRect);
    buttonLayout->addWidget(buttonRotateRect);
    buttonLayout->addWidget(buttonEllipse);
    buttonLayout->addWidget(buttonPolygon);
    buttonLayout->addWidget(buttonCircle);
    buttonLayout->addWidget(buttonRing);
    buttonLayout->addWidget(buttonCicularArc);
    buttonLayout->addWidget(buttonImageHandle);

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

void GraphicExercise::keepOneItem(){
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

void GraphicExercise::onButtonImageHandleClicked()
{
    image = imread("C:\\AAA-Temp\\新建文件夹\\2023_04_19_15_37_05_612.bmp");//重置原图片
    QList<QGraphicsItem*> items = scene.items();
    QGraphicsItem* child = nullptr;//防止内存溢出
    for (QGraphicsItem* item : items) {
        qDebug() << "123line:" << item;
        if (item != backgroundItem) {
            child = item;
            
        }
    }
    try {
        if (backgroundItem && child) {

            // 获取子图形项在父图形项中的位置
            QPointF topLeft = child->mapToParent(child->boundingRect().topLeft());
            QPointF bottomRight = child->mapToParent(child->boundingRect().bottomRight());
            QPolygonF childArea = child->mapToParent(child->shape().boundingRect());

            ResizableItem* polygonItem = dynamic_cast<ResizableItem*>(child);
            if (!polygonItem) {
                throw std::runtime_error("Child item is not a QGraphicsPolygonItem.");
            }
            qDebug() << "child-> parentItem:" << child->parentItem();

            // 获取多边形顶点
            QPolygonF poly = polygonItem->roiPoly;

            // 创建一个新的多边形来存储转换后的顶点
            QPolygonF transformedPoly;

            // 将每个点从子坐标系转换为父坐标系
            for (const QPointF& point : poly) {   
                QPointF parentPoint = polygonItem->mapToParent(point);
                transformedPoly.append(parentPoint); // 添加到转换后的多边形
            }

            // 创建一个与源图像相同大小的掩码，初始化为零（黑色）
            cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

            // 定义 cv 多边形的顶点
            std::vector<cv::Point> polygonPoints;
            for (const QPointF& point : transformedPoly) {
                polygonPoints.emplace_back(static_cast<int>(point.x()), static_cast<int>(point.y()));
            }

            // 使用 fillPoly 在掩码上绘制多边形
            std::vector<std::vector<cv::Point>> contours = { polygonPoints };
            cv::fillPoly(mask, contours, cv::Scalar(255)); // 填充白色

            // 使用掩码提取多边形区域
            cv::Mat maskRoi;
            if (!mask.empty() && !image.empty()) {
                image.copyTo(maskRoi, mask); // 通过掩码提取区域
            }
            else {
                throw std::runtime_error("Image or mask is empty.");
            }

            // 将 ROI 转换为灰度图像
            Mat grayROI;
            cv::cvtColor(maskRoi, grayROI, COLOR_BGR2GRAY); // 多边形 maskRoi

            // 对灰度图像进行二值化处理
            Mat binaryROI;
            cv::threshold(grayROI, binaryROI, 128, 255, THRESH_BINARY);

            // 将二值化的结果转换回 BGR 三通道
            Mat binaryROIColor;
            cv::cvtColor(binaryROI, binaryROIColor, COLOR_GRAY2BGR);

            // 将处理后的 ROI 放回原图
            binaryROIColor.copyTo(image, mask); // 通过 mask 获取到的 roi

            // 更新背景图像
            QImage qImage = MatToQImage(image);
            QPixmap backgroundPixmap = QPixmap::fromImage(qImage);
            backgroundItem->setPixmap(backgroundPixmap);
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Exception occurred: " << e.what(); // 输出异常信息
    }
    catch (...) {
        qDebug() << "An unknown exception occurred.";
    }
    return;
}

void GraphicExercise::onButtonRectClicked() {
    keepOneItem();
    ResizableRectItem* rectItem = new ResizableRectItem(100, 100, 200, 100);
    rectItem->ResizableItem::setParentItem(backgroundItem);
    //scene.addItem(rectItem);
}

void GraphicExercise::onButtonRotateRectClicked() {
    keepOneItem();
    ResizableRotateRectItem* rotateRect = new ResizableRotateRectItem(100, 100, 200, 100);
    rotateRect->ResizableItem::setParentItem(backgroundItem);
    //scene.addItem(rotateRect);
}

void GraphicExercise::onButtonEllipseClicked() {
    keepOneItem();
    ResizableEllipseItem* ellipse = new ResizableEllipseItem(50, 50, 50, 100);
    ellipse->setParentItem(backgroundItem);
    //scene.addItem(ellipse);
}

void GraphicExercise::onButtonPolygonClicked() {
    keepOneItem();
    ResizablePolygonItem* polygon = new ResizablePolygonItem();
    polygon->setParentItem(backgroundItem);
    //scene.addItem(polygon);
}

void GraphicExercise::onButtonCircleClicked(){
    keepOneItem();
    ResizableCircleItem* circle = new ResizableCircleItem(50, 50, 50, 50);
    circle->setParentItem(backgroundItem);
    //scene.addItem(circle);
}

void GraphicExercise::onButtonRingClicked(){
    keepOneItem();
    ResizableRingItem* ring = new ResizableRingItem(150, 150, 50, 50);
    ring->setParentItem(backgroundItem);
    //scene.addItem(ring);
}

void GraphicExercise::onButtonCicularArcClicked(){
    keepOneItem();
    ResizableCicularArcItem* cicularArc = new ResizableCicularArcItem(200, 200, 150, 150);
    cicularArc->setParentItem(backgroundItem);
    //scene.addItem(cicularArc);
}

