#include "BucketTool.h"
#include <LayerManager.h>



#include<HueDial.h>



BucketTool::BucketTool(QWidget* parent)
    : QWidget(parent)
{
    //setWindowTitle("Bad Apple");
    //setFixedSize(1920, 1080);
    //setStyleSheet("background-color: rgb(30,30,30);");
    setAttribute(Qt::WA_TabletTracking);
    setAttribute(Qt::WA_MouseTracking);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);


    pngBackground = QImage(QDir::currentPath() + "/Images/PNGBackground.png");

    background = QImage(1100, 1100, QImage::Format_ARGB32_Premultiplied);
    image = background;
    image.fill(Qt::transparent);
    originalImage = image;
    background.fill(Qt::white);
    //layers = { background, image };

    //brush = QImage(QDir::currentPath() + "/Images/ChalkRot.png");

    //brushOutline = QImage(QDir::currentPath() + "/Images/ChalkRot_Outline.png");

    colourWindow = new ColourWindow(this);

    layerManager = new LayerManager(this);

    layers = layerManager->layers;
    //undoStack.push(layers);

    overlay = layerManager->selectionOverlay;

    connect(layerManager, &LayerManager::layerSelected,
        this, [=](const QString& layerName, int layerIndex) {
            selectedLayerIndex = layerIndex;
        });


    connect(layerManager, &LayerManager::layerAdded,
        this, [=](int layerIndex) {

            layers.insert(layerIndex, originalImage);
            //pushUndo(layers);
            layerManager->update();
            update();
        });


    connect(layerManager, &LayerManager::layerDeleted,
        this, [=](int layerIndex) {
            if (layerIndex < 0 || layerIndex >= layers.size()) {
                return;
            }

            layers.removeAt(layerIndex);
            //pushUndo(layers);

            if (layers.count() == 0) {
                selectedLayerIndex = 0;
            }
            layerManager->update();
            update();
        });



}


void BucketTool::applyZoom(float zoomAmount)
{

    if (1 <= zoomPercentage * zoomAmount <= 12800)
    {
        zoomPercentage = zoomPercentage * zoomAmount;
    }
    else if (zoomPercentage < 1) { zoomPercentage = 1; }
    else { zoomPercentage = 12800; }
    //QPointF hoverFromCenter = rect().center() + hoverPoint;
    repaint();
    update();

}

void BucketTool::zoomIn()
{
    applyZoom((1.111));
}

void BucketTool::zoomOut()
{
    applyZoom((0.9));
}

void BucketTool::resetZoom()
{
    zoomPercentage = 100.0;
    applyZoom(1);
}

void BucketTool::keyPressEvent(QKeyEvent* event)
{

    if (event->key() == 61 && event->modifiers() & Qt::ControlModifier)
        zoomIn();
    if (event->key() == 45 && event->modifiers() & Qt::ControlModifier)
        zoomOut();

    if (event->key() == Qt::Key_0 && event->modifiers() & Qt::ControlModifier)
        resetZoom();

    if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier)
    {
        //undo();
        //layerManager->undo();
    }

    if (event->key() == Qt::Key_Y && event->modifiers() & Qt::ControlModifier)
    {
        //redo();
        //layerManager->redo();
    }

    if (event->key() == Qt::Key_Space)
    {
        panningEnabled = true;
        setCursor(Qt::OpenHandCursor);
    }



    if (event->key() == Qt::Key_L)
    {
        emit bucketDisabled();
        emit lassoEnabled();
    }

    if (event->key() == Qt::Key_B)
    {
        emit bucketDisabled();
        emit brushEnabled();
    }
}


void BucketTool::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
        return;
    }
    if (event->key() == Qt::Key_Space)
    {
        lastPanPoint = QPoint();
        panningEnabled = false;
        setCursor(Qt::ArrowCursor);
    }
}

void BucketTool::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPoint center = rect().center();
    //QPoint hoverOffset = center - hoverPoint.toPoint();

    painter.translate(center);
    painter.scale(zoomPercentage / 100, zoomPercentage / 100);
    painter.translate(panOffset / (zoomPercentage / 100.0));

    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    QPointF topLeft(-image.width() / 2.0, -image.height() / 2.0);

    painter.drawImage(topLeft, pngBackground);

    for (const QImage layer : layers) {
        painter.drawImage(topLeft, layer);
    }
    painter.drawImage(topLeft, overlay);
}


QPoint BucketTool::mapToImage(const QPoint& p)
{
    QPoint center = rect().center();
    qDebug() << center;
    QPoint offsetPoint = (p - center - panOffset) / (zoomPercentage / 100.0);
    //QPoint offsetPoint = (p / (zoomPercentage / 100.0) - center - panOffset / (zoomPercentage / 100.0));

    return offsetPoint + QPoint(image.width() / 2.0, image.height() / 2.0);
}

QPointF BucketTool::mapToImageF(const QPointF& p)
{
    QPointF center = rect().center();
    QPointF offsetPoint = (p - center - panOffset) / (zoomPercentage / 100.0);
    //QPoint offsetPoint = (p / (zoomPercentage / 100.0) - center - panOffset / (zoomPercentage / 100.0)).toPoint();

    return offsetPoint + QPointF(image.width() / 2.0, image.height() / 2.0);
}

void BucketTool::mousePressEvent(QMouseEvent* event)
{
    if (layers.count() < 1) return;

    if (event->button() == Qt::LeftButton) {
        if (panningEnabled) {
            lastPanPoint = event->pos();
            isPanning = true;
        }
        else
        {
            QPoint point = mapToImage(event->pos());

            QImage currentImage = layers[selectedLayerIndex];

            QColor basePixelColor = QColor(currentImage.pixel(point.x(), point.y()));

            qDebug() << basePixelColor;

            QColor TEST = QColor(qRgb(255, 0, 0));

            //dfs(currentImage, point.x(), point.y(), basePixelColor, TEST);
            layers[selectedLayerIndex] = fill(currentImage, point.x(), point.y(), basePixelColor, TEST);
            qDebug() << selectedLayerIndex;




            //for (int pixelY = 0; pixelY < currentImage.height(); pixelY++)
            //{
            //    for (int pixelX = 0; pixelX < currentImage.width(); pixelX++)
            //    {

            //    }
            //}
        }
    }
}



//void BucketTool::dfs(QImage image, int pixelX, int pixelY, const QColor oldColor, const QColor newColor)
//{
//    if (oldColor == newColor)
//        return;
//    if (pixelX < 0 || pixelX >= image.width() || pixelY < 0 || pixelY >= image.height() || QColor(image.pixel(pixelX, pixelY)) != oldColor)
//    {
//        return;
//    }
//    else
//    {
//        image.setPixelColor(pixelX, pixelY, newColor);
//        dfs(image, pixelX + 1, pixelY, oldColor, newColor);
//        dfs(image, pixelX - 1, pixelY, oldColor, newColor);
//        dfs(image, pixelX, pixelY + 1, oldColor, newColor);
//        dfs(image, pixelX, pixelY - 1, oldColor, newColor);
//    }
//
//
//}


QImage BucketTool::fill(QImage& image, int startX, int startY,
    const QColor& oldColor, const QColor& newColor)
{
    const QRgb target = image.pixel(startX, startY);
    const QRgb replacement = newColor.rgba();

    if (target == replacement)
        return image;

    QStack<QPoint> stack;
    stack.push(QPoint(startX, startY));

    while (!stack.isEmpty())
    {
        QPoint p = stack.pop();
        int x = p.x();
        int y = p.y();

        if (x < 0 || x >= image.width() ||
            y < 0 || y >= image.height())
            continue;

        if (image.pixel(x, y) != target)
            continue;

        image.setPixel(x, y, replacement);

        stack.push(QPoint(x + 1, y));
        stack.push(QPoint(x - 1, y));
        stack.push(QPoint(x, y + 1));
        stack.push(QPoint(x, y - 1));
    }
    return image;
}


//#include <iostream>
//#include <vector>
//using namespace std;
//
//void dfs(vector<vector<int>>& img, int x,
//    int y, int oldColor, int newColor) {
//
//    if (x < 0 || x >= img.size() ||
//        y < 0 || y >= img[0].size() || img[x][y] != oldColor) {
//        return;
//    }
//
//    // Update the color of the current pixel
//    img[x][y] = newColor;
//
//    // Recursively visit all 4 connected neighbors
//    dfs(img, x + 1, y, oldColor, newColor);
//    dfs(img, x - 1, y, oldColor, newColor);
//    dfs(img, x, y + 1, oldColor, newColor);
//    dfs(img, x, y - 1, oldColor, newColor);
//}
//
//vector<vector<int>> floodFill(vector<vector<int>>& img, int sr,
//    int sc, int newColor) {
//
//    // If the starting pixel already has the new color,
//    // no changes are needed
//    if (img[sr][sc] == newColor) {
//        return img;
//    }
//
//    // Call DFS to start filling from the source pixel
//     // Store original color
//    int oldColor = img[sr][sc];
//    dfs(img, sr, sc, oldColor, newColor);
//
//    return img;
//}
//
//int main() {
//    vector<vector<int>> img = {
//        {1, 1, 1, 0},
//        {0, 1, 1, 1},
//        {1, 0, 1, 1}
//    };
//
//    int sr = 1, sc = 2;
//
//    int newColor = 2;
//
//    vector<vector<int>> result = floodFill(img, sr, sc, newColor);
//
//    for (auto& row : result) {
//        for (auto& pixel : row) {
//            cout << pixel << " ";
//        }
//    }
//    return 0;
//}

