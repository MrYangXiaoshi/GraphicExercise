#include "GraphicExercise.h"
#include <filesystem>

using namespace cv;

GraphicExercise::GraphicExercise(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "GraphicExercise###";

    ui.setupUi(this);

    // ����һ�� QWidget ��Ϊ central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // ����ˮƽ����
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);

    // ���������ͼ
    QGraphicsView* view = new QGraphicsView(centralWidget);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(740, 660);
    layout->addWidget(view);
    view->setBackgroundBrush(Qt::black);
    view->setScene(&scene);

    //OpenCV,����ͼƬ
    mat = imread("C:\\AAA-Temp\\�½��ļ���\\2023_04_19_15_37_05_612.bmp");
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
    backgroundItem->setTransformOriginPoint(0, 0);
    scene.addItem(backgroundItem);
    backgroundItem->setPos(0, 0);

    // �����Ҳఴť��
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

    // �����źźͲ�
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
    // ����ǻҶ�ͼ��
    if (mat.type() == CV_8UC1)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    }
    // �����RGBͼ��
    else if (mat.type() == CV_8UC3)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    }
    // ����Ǵ���alphaͨ����ͼ��
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
    // ��ȡ�����е�����ͼ����
    QList<QGraphicsItem*> items = scene.items();

    // ��������ͼ�����ɾ�����в����ڱ���ͼ���������
    for (QGraphicsItem* item : items) {
        if (item != backgroundItem) {
            scene.removeItem(item); // �ӳ������Ƴ�
            delete item;            // ɾ��ͼ���ȷ���ڴ汻��ȷ�ͷ�
        }
    }
}

void GraphicExercise::onButtonImageHandleClicked()
{
    mat = imread("C:\\AAA-Temp\\�½��ļ���\\2023_04_19_15_37_05_612.bmp");//����ԭͼƬ
    QList<QGraphicsItem*> items = scene.items();
    QGraphicsItem* child = nullptr;//��ֹ�ڴ����
    for (QGraphicsItem* item : items) {
        qDebug() << "123line:" << item;
        if (item != backgroundItem) {
            child = item;
        }
    }
    
    if (backgroundItem && child) {
        // ��ȡ��ͼ�����ڸ�ͼ�����е�λ��
        QPointF topLeft = child->mapToParent(child->boundingRect().topLeft());
        QPointF bottomRight = child->mapToParent(child->boundingRect().bottomRight());
        QPolygonF childArea = child->mapToParent(child->shape().boundingRect());
        //QRectF childRect = child->mapToParent(child->rect());

        //�����ͼ�����roi
        qDebug() << topLeft << bottomRight <<  QRectF(topLeft, bottomRight) << "###";
        qDebug() << childArea << "####";
        qDebug() << "child->boundingRect():" << child->boundingRect();

        Rect roi(topLeft.x(), topLeft.y(),
            child->boundingRect().width(), child->boundingRect().height());

        // ��ȡROI
        Mat imageROI = mat(roi);

        // ��ROIת��Ϊ�Ҷ�ͼ��
        Mat grayROI;
        cvtColor(imageROI, grayROI, COLOR_BGR2GRAY);

        // �ԻҶ�ͼ����ж�ֵ������
        Mat binaryROI;
        threshold(grayROI, binaryROI, 128, 255, THRESH_BINARY);

        // ����ֵ���Ľ��ת���� BGR ��ͨ�� (���ԭͼ���ǲ�ɫ��)
        Mat binaryROIColor;
        cvtColor(binaryROI, binaryROIColor, COLOR_GRAY2BGR);

        // ��������ROI�Ż�ԭͼ
        binaryROIColor.copyTo(mat(roi));

        QImage qImage = MatToQImage(mat);
        QPixmap backgroundPixmap = QPixmap::fromImage(qImage);
        /*scene.setBackgroundBrush(backgroundPixmap);
        backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);*/
        //backgroundItem->setTransformOriginPoint(0, 0);
        //scene.addItem(backgroundItem);
        //backgroundItem->setPos(0, 0);
        backgroundItem->setPixmap(backgroundPixmap);
    }
    return;
}

void GraphicExercise::onButtonRectClicked() {
    keepOneItem();
    ResizableRectItem* rectItem = new ResizableRectItem(100, 100, 200, 100);
    rectItem->setParentItem(backgroundItem);
    //scene.addItem(rectItem);
}

void GraphicExercise::onButtonRotateRectClicked() {
    keepOneItem();
    ResizableRotateRectItem* rotateRect = new ResizableRotateRectItem(100, 100, 200, 100);
    rotateRect->setParentItem(backgroundItem);
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

