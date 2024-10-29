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
    image = imread("C:\\AAA-Temp\\�½��ļ���\\2023_04_19_15_37_05_612.bmp");
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
    // �Ҷ�ͼ��
    if (mat.type() == CV_8UC1)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    }
    // RGBͼ��
    else if (mat.type() == CV_8UC3)
    {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    }
    // ����alphaͨ����ͼ��
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
    QList<QGraphicsItem*> items = scene.items();

    for (QGraphicsItem* item : items) {
        if (item != backgroundItem) {
            scene.removeItem(item); 
            delete item;            // ɾ��ͼ���ȷ���ڴ汻��ȷ�ͷ�
        }
    }
}

void GraphicExercise::handleMask()
{
    // ʹ��������ȡ���������
    cv::Mat maskRoi;
    if (!mask.empty() && !image.empty()) {
        image.copyTo(maskRoi, mask); // ͨ��������ȡ����
    }
    else {
        throw std::runtime_error("Image or mask is empty.");
    }

    // �� ROI ת��Ϊ�Ҷ�ͼ��
    Mat grayROI;
    cv::cvtColor(maskRoi, grayROI, COLOR_BGR2GRAY); // ����� maskRoi

    // �ԻҶ�ͼ����ж�ֵ������
    Mat binaryROI;
    cv::threshold(grayROI, binaryROI, 128, 255, THRESH_BINARY);

    // ����ֵ���Ľ��ת���� BGR ��ͨ��
    Mat binaryROIColor;
    cv::cvtColor(binaryROI, binaryROIColor, COLOR_GRAY2BGR);

    // �������� ROI �Ż�ԭͼ
    binaryROIColor.copyTo(image, mask); // ͨ�� mask ��ȡ���� roi

    // ���±���ͼ��
    QImage qImage = MatToQImage(image);
    QPixmap backgroundPixmap = QPixmap::fromImage(qImage);
    backgroundItem->setPixmap(backgroundPixmap);
}

void GraphicExercise::onButtonImageHandleClicked()
{
    image = imread("C:\\AAA-Temp\\�½��ļ���\\2023_04_19_15_37_05_612.bmp");//����ԭͼƬ
    QList<QGraphicsItem*> items = scene.items();
    QGraphicsItem* child = nullptr;//��ֹ�ڴ����
    for (QGraphicsItem* item : items) {
        qDebug() << "123line:" << item;
        if (item != backgroundItem) {
            child = item;
        }
    }
    try {
        if (backgroundItem && child) {
            // ��ȡ��ͼ�����ڸ�ͼ�����е�λ��
            QPointF topLeft = child->mapToParent(child->boundingRect().topLeft());
            QPointF bottomRight = child->mapToParent(child->boundingRect().bottomRight());
            QPolygonF childArea = child->mapToParent(child->shape().boundingRect());

            ResizableItem* polygonItem = dynamic_cast<ResizableItem*>(child);
            if (!polygonItem) {
                throw std::runtime_error("Child item is not a QGraphicsPolygonItem.");
            }
            qDebug() << "child-> parentItem:" << child->parentItem();

            // ��ȡ����ζ���
            QPolygonF poly = polygonItem->roiPoly;

            // ����һ���µĶ�������洢ת����Ķ���
            QPolygonF transformedPoly;

            // ��ÿ�����������ϵת��Ϊ������ϵ
            for (const QPointF& point : poly) {   
                QPointF parentPoint = polygonItem->mapToParent(point);
                transformedPoly.append(parentPoint); // ��ӵ�ת����Ķ����
            }

            // ����һ����Դͼ����ͬ��С�����룬��ʼ��Ϊ�㣨��ɫ��
            mask = cv::Mat::zeros(image.size(), CV_8UC1);

            // ���� cv ����εĶ���
            std::vector<cv::Point> polygonPoints;
            for (const QPointF& point : transformedPoly) {
                polygonPoints.emplace_back(static_cast<int>(point.x()), static_cast<int>(point.y()));
            }

            //���ƶ�Ӧ����
            if (typeid(*child) == typeid(ResizableCircleItem)) {
                // ����Բ������
                int centerX = (polygonPoints[2].x + polygonPoints[3].x) / 2;
                int centerY = (polygonPoints[0].y + polygonPoints[1].y) / 2;
                cv::Point center(centerX, centerY);

                // ����뾶��ʹ�����㵽Բ�ĵľ�����Ϊ�뾶��
                int radius = std::abs(polygonPoints[2].x - centerX);

                // �������ϻ��ư�ɫ��Բ��
                cv::circle(mask, center, radius, cv::Scalar(255), -1);
            }
            else if (typeid(*child) == typeid(ResizableEllipseItem)) {
                // ����ת��Ϊ std::vector<cv::Point2f> ����
                std::vector<cv::Point2f> points(polygonPoints.begin(), polygonPoints.end());

                // ʹ�� fitEllipse �����Բ
                cv::RotatedRect fittedEllipse = cv::fitEllipse(points);

                // �������ϻ�����ϵ���Բ
                cv::ellipse(mask, fittedEllipse, cv::Scalar(255), -1); // -1 ��ʾ���
            }
            else if (typeid(*child) == typeid(ResizableRingItem)) {
                // ����Բ������
                int centerX = (polygonPoints[2].x + polygonPoints[3].x) / 2;
                int centerY = (polygonPoints[0].y + polygonPoints[1].y) / 2;
                cv::Point center(centerX, centerY);

                // ����뾶��ʹ�����㵽Բ�ĵľ�����Ϊ�뾶��
                int radius = std::abs(polygonPoints[2].x - centerX);
                int radius2 = std::abs(polygonPoints[6].x - centerX);
                int temp;
                if (radius2 > radius) {
                    temp = radius;
                    radius = radius2;
                    radius2 = temp;
                }
                cv::circle(mask, center, radius, cv::Scalar(255), -1);
                cv::circle(mask, center, radius2, cv::Scalar(0), -1);
            }
            else if (typeid(*child) == typeid(ResizableCicularArcItem)) {
                ResizableCicularArcItem* arcItem = dynamic_cast<ResizableCicularArcItem*>(child);
                QPointF centerf = arcItem->mapToParent(arcItem->getArcCenter());
                qDebug() << "centerf:" << centerf;
                
                cv::Point center(centerf.x(), centerf.y());

                // ����뾶��ʹ�����㵽Բ�ĵľ�����Ϊ�뾶��
                int radius = (arcItem->getCircleRect().width() / 2);
                int radius2 = (arcItem->getCircleRect2().width() / 2);
                int temp;
                if (radius2 > radius) {
                    temp = radius;
                    radius = radius2;
                    radius2 = temp;
                }
                // ��ȡ��ʼ�ǶȺͿ�ȽǶȣ���λ���ȣ�
                int startAngle = -arcItem->getStartAngle();
                int spanAngle = -arcItem->getSpanAngle();
                // ������ʼ�Ƕȵ� 0-360 �ȷ�Χ��
                if (startAngle < 0) {
                    startAngle += 360;
                }
                // ʹ�� OpenCV ��������Բ��
                cv::ellipse(mask, center, cv::Size(radius, radius), 0, startAngle, startAngle + spanAngle, cv::Scalar(255), -1);
                cv::ellipse(mask, center, cv::Size(radius2, radius2), 0, startAngle, startAngle + spanAngle, cv::Scalar(0), -1);
            } else {//���Ρ���ת���Ρ������
                // ʹ�� fillPoly �������ϻ��ƶ����
                std::vector<std::vector<cv::Point>> contours = { polygonPoints };
                cv::fillPoly(mask, contours, cv::Scalar(255)); // ����ɫ
            }
            handleMask();
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Exception occurred: " << e.what(); // ����쳣��Ϣ
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

