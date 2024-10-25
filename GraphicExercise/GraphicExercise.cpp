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
    view->setFixedSize(720, 540);
    layout->addWidget(view);
    //view->setBackgroundBrush(Qt::black);
    view->setScene(&scene);

    //OpenCV,����ͼƬ
    Mat mat = imread("C:\\AAA-Temp\\�½��ļ���\\2023_04_19_15_37_05_612.bmp");
    if (mat.empty()) {
        qDebug() << "Failed to load image!";
    }
    else {
        qDebug() << "mat.rows:" << mat.rows << " mat.cols:" << mat.cols;
    }
    QImage qImage = MatToQImage(mat);
    QPixmap backgroundPixmap = QPixmap::fromImage(qImage);
    //scene.setBackgroundBrush(backgroundPixmap);
    //view->setBackgroundBrush(backgroundPixmap);
    backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    scene.addItem(backgroundItem);

    ////OpenCVExercise
    //Mat image;
    //image = imread("D:\\AAA_Temp\\test.jpg");	// ����ͼ��
    //if (image.empty())	// ���� if(!image.data) �ж�ͼƬ�Ƿ���سɹ�
    //{
    //    std::cout << "image not exist";
    //}
    //namedWindow("demo ͼƬ");
    //imshow("demo ͼƬ", image);	// ��ʾͼ��

    //Mat dst;//Ŀ��ͼ��
    //// ���и�ʴ����
    //Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //erode(image, dst, element);

    //blur(image, dst, Size(15, 15));
    //imshow("��ʴͼƬ", dst);

    //imwrite("D:\\AAA_Temp\\save.jpg", dst);
    //waitKey(2000);	// �ȴ����ⰴ�����£��˳�ͼƬ��ʾ

    // �����Ҳఴť��
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    QPushButton* buttonRect = new QPushButton("Rect", centralWidget);
    QPushButton* buttonRotateRect = new QPushButton("RotateRect", centralWidget);
    QPushButton* buttonEllipse = new QPushButton("Ellipse", centralWidget);
    QPushButton* buttonPolygon = new QPushButton("Polygon", centralWidget);

    QPushButton* buttonCircle = new QPushButton("Circle", centralWidget);
    QPushButton* buttonRing = new QPushButton("Ring", centralWidget);
    QPushButton* buttonCicularArc = new QPushButton("CicularArc", centralWidget);

    // �����źźͲ�
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
    ResizableRingItem* ring = new ResizableRingItem(150, 150, 50, 50);
    scene.addItem(ring);
}

void GraphicExercise::onButtonCicularArcClicked()
{
    scene.clear();
    ResizableCicularArcItem* cicularArc = new ResizableCicularArcItem(200, 200, 150, 150);
    scene.addItem(cicularArc);
}

