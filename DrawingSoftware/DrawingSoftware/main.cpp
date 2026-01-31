#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QTabletEvent>
#include <QPainter>
#include <QStack>
#include <QKeyEvent>
#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <string>
#include <QPolygon>
#include <QRect>
#include <QPainterPath>
#include <QDial>
#include <QProxyStyle>
#include <list>

#include <QVBoxLayout>
#include <QListWidget>
#include <Qstring>
#include <QPixmap>
#include <QDockWidget>

#include <QMainWindow>
#include <QMenu>

#include <LayerManager.h>
#include <BrushTool.h>

#include<HueDial.h>

//class HueDial : public QDial
//{
//
//    //signals:
//    //    void colorDialAngle(float angle);
//
//public:
//    HueDial(QWidget* parent = nullptr)
//        : QDial(parent)
//    {
//        setMinimumSize(300, 300);
//        setWrapping(true);
//        setStyleSheet("border: 0");
//
//
//        connect(this, &QDial::valueChanged, this, [this](int change) {
//            //emit colorDialAngle(static_cast<float>(change));
//            update();  // repaint when dial moves
//            });
//
//        QRectF windowArea = rect();
//        qreal windowSide = qMin(windowArea.width(), windowArea.height());
//
//        outerRect = QRect((width() - windowSide) / 2, (height() - windowSide) / 2, windowSide, windowSide);
//
//        thickness = windowSide * 0.075;
//        innerRect = outerRect.adjusted(thickness, thickness, -thickness, -thickness);
//    }
//    float getSaturation() const
//    {
//        float w1, w2, w3;
//        barycentricPoints(p1, p2, p3, SLPosition, w1, w2, w3);
//        return qBound(0.0f, w2, 1.0f);
//
//    }
//    float getLightness() const
//    {
//        float w1, w2, w3;
//        barycentricPoints(p1, p2, p3, SLPosition, w1, w2, w3);
//        float lightness = w3 + 0.5f * w2;
//        return qBound(0.0f, lightness, 1.0f);
//    }
//
//
//private:
//    QRectF outerRect;
//    qreal thickness;
//    QRectF innerRect;
//    bool inRing;
//    QPointF clickPosition;
//    bool inTriangle;
//    QPolygonF triangle;
//    QPointF SLPosition;
//    float maxDist;
//    QPointF p1;
//    QPointF p2;
//    QPointF p3;
//    QPointF offset;
//
//protected:
//
//    QPointF projectPointToSegment(
//        const QPointF& p,
//        const QPointF& a,
//        const QPointF& b)
//    {
//        QVector2D ap(p - a);
//        QVector2D ab(b - a);
//
//        float abLenSq = QVector2D::dotProduct(ab, ab);
//        if (abLenSq == 0.0f)
//            return a;
//
//        float t = QVector2D::dotProduct(ap, ab) / abLenSq;
//        t = std::clamp(t, 0.0f, 1.0f);
//
//        return a + (b - a) * t;
//    }
//
//    QPointF clampToTriangle(const QPointF& mousePos)
//    {
//        if (triangle.containsPoint(mousePos, Qt::OddEvenFill))
//            return mousePos;
//
//        QPointF pAB = projectPointToSegment(mousePos, p1, p2);
//        QPointF pBC = projectPointToSegment(mousePos, p2, p3);
//        QPointF pCA = projectPointToSegment(mousePos, p3, p1);
//
//        float dAB = QLineF(mousePos, pAB).length();
//        float dBC = QLineF(mousePos, pBC).length();
//        float dCA = QLineF(mousePos, pCA).length();
//        if (dAB <= dBC && dAB <= dCA) return pAB;
//        if (dBC <= dCA)              return pBC;
//        return pCA;
//    }
//
//
//
//    static void barycentricPoints(
//        const QPointF& p1,
//        const QPointF& p2,
//        const QPointF& p3,
//        const QPointF& p,
//        float& w1, float& w2, float& w3)
//    {
//        float det =
//            (p1.x() - p3.x()) * (p2.y() - p3.y()) -
//            (p2.x() - p3.x()) * (p1.y() - p3.y());
//
//        w1 =
//            (p2.y() - p3.y()) * (p.x() - p3.x()) +
//            (p3.x() - p2.x()) * (p.y() - p3.y());
//
//        w2 =
//            (p3.y() - p1.y()) * (p.x() - p3.x()) +
//            (p1.x() - p3.x()) * (p.y() - p3.y());
//
//        w1 /= det;
//        w2 /= det;
//        w3 = 1.0f - w1 - w2;
//    }
//
//    float angleFromMouse(const QPoint& pos)
//    {
//        QPointF center = rect().center();
//        QPointF d = pos - center;
//
//        float angle = std::atan2(d.y(), d.x());
//        angle = qRadiansToDegrees(angle);
//
//        if (angle < 0)
//            angle += 360.0f;
//
//        return angle;
//    }
//
//
//    void mousePressEvent(QMouseEvent* event)
//    {
//        triangle.clear();
//        qreal windowSide = qMin(width(), height());
//        qreal outerRadius = windowSide / 2.0;
//        qreal thickness = windowSide * 0.075;
//        qreal innerRadius = outerRadius - thickness;
//
//        clickPosition = QPointF(event->pos());
//
//
//        QPointF center = rect().center();
//        QPointF delta = clickPosition - center;
//        qreal dist = std::hypot(delta.x(), delta.y());
//
//        inRing = (dist >= innerRadius) && (dist <= outerRadius);
//
//        float r = qMin(width(), height()) * 0.735f;
//        float h = std::sqrt(3.0f) * r / 2.0f;
//
//        p1 = QPointF(-r / 2, h / 3);
//        p2 = QPointF(r / 2, h / 3);
//        p3 = QPointF(0, -2 * h / 3);
//
//        QTransform t;
//        t.translate(center.x(), center.y());
//        t.rotate(-22.5);
//        t.translate(-center.x(), -center.y());
//
//        p1 = t.map(p1 + center);
//        p2 = t.map(p2 + center);
//        p3 = t.map(p3 + center);
//
//        triangle << p1 << p2 << p3;
//
//        if (inRing) {
//            setValue(angleFromMouse(event->pos()));
//            inTriangle = false;
//        }
//        else {
//            if (triangle.containsPoint(clickPosition, Qt::OddEvenFill)) {
//                inTriangle = true;
//            }
//            else {
//                inTriangle = false;
//
//            }
//        }
//        //update();
//    }
//
//    void mouseMoveEvent(QMouseEvent* event)
//    {
//        QPointF mousePos = event->pos();
//        clickPosition = clampToTriangle(mousePos);
//        SLPosition = clickPosition;
//        if (inRing) {
//            setValue(angleFromMouse(event->pos()));
//        }
//        else if (inTriangle) if ((triangle.containsPoint(clickPosition, Qt::OddEvenFill))) {
//            offset = rect().center() - SLPosition;
//        }
//
//        update();
//
//    }
//    void mouseReleaseEvent(QMouseEvent* event) override
//    {
//        inRing = false;
//        Q_UNUSED(event);
//        inTriangle = false;
//    }
//
//    void paintEvent(QPaintEvent* event) override
//    {
//        Q_UNUSED(event);
//        QPainter p(this);
//        QPainter painterHS(this);
//
//        p.setRenderHint(QPainter::Antialiasing);
//
//        QRectF windowArea = rect();
//        qreal windowSide = qMin(windowArea.width(), windowArea.height());
//
//
//        qreal knobRadius = windowSide * 0.028; //change to 0.035 if i manage to sort the weird offset
//        qreal knobDistance = windowSide / 2.135 - windowSide * 0.008; //remove subtraction
//
//        QPointF center = rect().center();
//        p.setPen(QPen(Qt::white, 2));
//        p.setBrush(Qt::NoBrush);
//
//        p.save();
//        p.translate(center);
//        p.rotate(value());
//        QPointF knobCenter = QPointF(knobDistance, 1.0);
//        p.drawEllipse(knobCenter, knobRadius, knobRadius);
//        p.restore();
//
//        p.save();
//        p.drawEllipse(center - offset, knobRadius, knobRadius);
//        p.restore();
//
//
//
//
//
//    }
//};


//class ColourWindow : public QWidget
//{
//
//public:
//
//    ColourWindow(QWidget* parent = nullptr) : QWidget(parent)
//    {
//        setWindowTitle("Colour Wheel");
//        resize(300, 300);
//        setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
//        createWheel();
//
//    }
//
//    int hueAngle() const
//    {
//        return dial->value();
//    }
//
//    QColor updateColour() const
//    {
//        float saturation = dial->getSaturation();
//        float lightness = dial->getLightness();
//        return QColor::fromHsl(360 - hueAngle(), int(saturation * 255), int(lightness * 255));
//    }
//
//protected:
//    void resizeEvent(QResizeEvent* event) override
//    {
//        Q_UNUSED(event);
//        dial->setGeometry(rect());
//    }
//
//    void createWheel()
//    {
//        dial->setRange(0, 360);
//        dial->setGeometry(0, 0, 300, 300);
//        int angle = dial->value();
//    }
//
//    void mousePressEvent(QMouseEvent* event) override
//    {
//        QPointF clickPosition = QPointF(event->pos());
//        if (windowArea.contains(clickPosition)) {
//        }
//        else {
//        }
//    }
//
//    void paintEvent(QPaintEvent*) override
//    {
//        QPainter painter(this);
//        painter.setRenderHint(QPainter::Antialiasing);
//
//        windowArea = rect();
//        qreal windowSide = qMin(windowArea.width(), windowArea.height());
//
//        QRectF outerRect((width() - windowSide) / 2, (height() - windowSide) / 2, windowSide, windowSide);
//
//        qreal thickness = windowSide * 0.075;
//        QRectF innerRect = outerRect.adjusted(thickness, thickness, -thickness, -thickness);
//
//        QPainterPath ring;
//        ring.addEllipse(outerRect);
//        ring.addEllipse(innerRect);
//
//        ring.setFillRule(Qt::OddEvenFill);
//
//        QConicalGradient gradient(rect().center(), 0);
//        gradient.setColorAt(0.0, Qt::red);
//        gradient.setColorAt(0.17, Qt::yellow);
//        gradient.setColorAt(0.33, Qt::green);
//        gradient.setColorAt(0.5, Qt::cyan);
//        gradient.setColorAt(0.67, Qt::blue);
//        gradient.setColorAt(0.83, Qt::magenta);
//        gradient.setColorAt(1.0, Qt::red);
//
//        painter.setBrush(gradient);
//        painter.setPen(Qt::NoPen);
//
//        painter.drawPath(ring);
//
//        QPointF center = rect().center();
//
//        float r = qMin(width(), height()) * 0.735f;
//        float h = std::sqrt(3.0f) * r / 2.0f;
//
//        QPointF p1(-r / 2, h / 3);
//        QPointF p2(r / 2, h / 3);
//        QPointF p3(0, -2 * h / 3);
//
//        QImage triImg(windowSide, windowSide, QImage::Format_ARGB32);
//        triImg.fill(Qt::transparent);
//
//        QPointF imgCenter(windowSide / 2.0, windowSide / 2.0);
//
//        QPointF a = p1 + imgCenter;
//        QPointF b = p2 + imgCenter;
//        QPointF c = p3 + imgCenter;
//
//
//        QColor ca = Qt::black;
//        QColor cb = QColor::fromHsv(360 - hueAngle(), 255, 255);
//        QColor cc = Qt::white;
//
//        float denom = (b.y() - c.y()) * (a.x() - c.x()) + (c.x() - b.x()) * (a.y() - c.y());
//
//        for (int y = 0; y < windowSide; ++y)
//        {
//            for (int x = 0; x < windowSide; ++x)
//            {
//                QPointF p(x, y);
//
//                float w1 = ((b.y() - c.y()) * (p.x() - c.x()) + (c.x() - b.x()) * (p.y() - c.y())) / denom;
//                float w2 = ((c.y() - a.y()) * (p.x() - c.x()) + (a.x() - c.x()) * (p.y() - c.y())) / denom;
//                float w3 = 1.0f - w1 - w2;
//
//                if (w1 >= 0 && w2 >= 0 && w3 >= 0)
//                {
//                    QColor col(
//                        ca.red() * w1 + cb.red() * w2 + cc.red() * w3,
//                        ca.green() * w1 + cb.green() * w2 + cc.green() * w3,
//                        ca.blue() * w1 + cb.blue() * w2 + cc.blue() * w3
//                    );
//
//                    triImg.setPixelColor(x, y, col);
//                }
//            }
//        }
//        center = rect().center();
//        painter.setRenderHint(QPainter::Antialiasing);
//
//        painter.save();
//        painter.resetTransform();
//        painter.translate(center);
//        painter.rotate(-22.5);
//        painter.drawImage(QPointF(-triImg.width() / 2.0, -triImg.height() / 2.0), triImg);
//        painter.restore();
//
//
//    }
//private:
//    HueDial* dial = new HueDial(this);
//    QRectF windowArea;
//};

class MainWindow : public QMainWindow
{
public:
    MainWindow()
    {
        setWindowTitle("Bad Apple");
        setFixedSize(1440, 720);
        setStyleSheet("background-color: rgb(30,30,30);");
        setAttribute(Qt::WA_TabletTracking);
        setAttribute(Qt::WA_MouseTracking);
        setMouseTracking(true);


        //pngBackground = QImage(QDir::currentPath() + "/Images/PNGBackground.png");

        //background = QImage(1100, 1100, QImage::Format_ARGB32_Premultiplied);
        //image = background;
        //image.fill(Qt::transparent);
        //originalImage = image;
        //background.fill(Qt::white);
        //layers = { background, image };

        //undoStack.push(layers);
        //brush = QImage(QDir::currentPath() + "/Images/ChalkRot.png");

        //brushOutline = QImage(QDir::currentPath() + "/Images/ChalkRot_Outline.png");
        brushTool = new BrushTool(this);


        colourWindow = brushTool->colourWindow;
        colourWindow->show();

        //layerManager = new LayerManager(this);
        layerManager = brushTool->layerManager;
        layerManager->show();



        createDockWindows();

        //connect(layerManager, &LayerManager::layerSelected,
        //    this, [=](const QString& layerName, int layerIndex) {
        //        selectedLayerIndex = layerIndex;
        //    });


        //connect(layerManager, &LayerManager::layerAdded,
        //    this, [=](int layerIndex) {

        //        layers.insert(layerIndex, originalImage);
        //        pushUndo(layers);
        //        layerManager->update();
        //        update();
        //    });


        //connect(layerManager, &LayerManager::layerDeleted,
        //    this, [=](int layerIndex) {
        //        if (layerIndex < 0 || layerIndex >= layers.size()) {
        //            return;
        //        }

        //        layers.removeAt(layerIndex);
        //        pushUndo(layers);
        //        
        //        if (layers.count() == 0) {
        //            selectedLayerIndex = 0;
        //        }
        //        // HERE
        //        selectedLayerIndex = layerIndex-1;
        //        layerManager->update();
        //        update();
        //    });


    }
    //
    //protected:
    //
    //    void tabletEvent(QTabletEvent* event) override
    //    {
    //
    //        if (event->type() == QEvent::TabletPress) {
    //            if (layers.count() < 1) return;
    //            if (panningEnabled) {
    //                lastPanPoint = event->position().toPoint();
    //                isPanning = true;
    //            }
    //            else {
    //                drawing = true;
    //                usingTablet = true;
    //                lastPointF = mapToImageF(getScaledPointF(event->position()));
    //
    //                if (!isErasing)
    //                {
    //                    colour = colourWindow->updateColour();
    //
    //
    //                }
    //
    //                brush = adjustBrushColour(brush, colour);
    //            }
    //        }
    //
    //        if (event->type() == QEvent::TabletMove) {
    //            if (isPanning)
    //            {
    //
    //                if (!lastPanPoint.isNull()) {
    //                    QPoint change = event->position().toPoint() - lastPanPoint;
    //                    panOffset += change;
    //                    lastPanPoint = event->position().toPoint();
    //                }
    //            }else{
    //                hoverPoint = event->position();
    //                isHovering = true;
    //                delayCounter += 1;
    //                if (delayCounter == 5) {
    //                    repaint();
    //                    delayCounter = 0;
    //                }
    //            }
    //            update();
    //
    //        }
    //
    //        if (event->type() == QEvent::TabletMove && drawing && !isPanning) {
    //            if (layers.count() < 1) return;
    //
    //            currentPoint = mapToImageF(getScaledPointF(event->position()));
    //            qreal pressure = event->pressure();
    //            xTilt = event->xTilt();
    //            yTilt = event->yTilt();
    //
    //            QPainter painter(&layers[selectedLayerIndex]);
    //
    //            painter.setRenderHint(QPainter::Antialiasing, true);
    //            if (isErasing) {
    //                painter.setCompositionMode(QPainter::CompositionMode_Clear);
    //
    //            }
    //
    //            drawStroke(painter, lastPointF, currentPoint, pressure);
    //
    //            lastPointF = currentPoint;
    //            update();
    //
    //        }
    //
    //        if (event->type() == QEvent::TabletRelease)
    //        {
    //            if (isPanning) {
    //                isPanning = false;
    //            }
    //            if (layers.count() < 1) return;
    //
    //            lastPointF = currentPoint;
    //            drawing = false;
    //            usingTablet = true;
    //            pushUndo(layers);
    //            redoStack.clear();
    //        }
    //
    //        event->accept();
    //    }
    //
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == 61 && event->modifiers() & Qt::ControlModifier)
            brushTool->zoomIn();
        if (event->key() == 45 && event->modifiers() & Qt::ControlModifier)
            brushTool->zoomOut();

        if (event->key() == Qt::Key_0 && event->modifiers() & Qt::ControlModifier)
            brushTool->resetZoom();

        if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier)
            brushTool->undo();
        layerManager->undo();
        if (event->key() == Qt::Key_Y && event->modifiers() & Qt::ControlModifier)
            brushTool->redo();
        layerManager->redo();

        if (event->key() == Qt::Key_Space)
        {
            //panningEnabled = true;
            setCursor(Qt::OpenHandCursor);
        }

        if (event->key() == Qt::Key_E)
        {
            /*  if (isErasing == true) {
                  isErasing = false;
                  colour = colourWindow->updateColour();
              }
              else {

                  isErasing = true;
              }*/
        }

        if (event->key() == Qt::Key_B)
        {
            //if (brushType == "chalk") {

            //    brush = QImage(QDir::currentPath() + "/Images/CircleBrush.png");
            //    brushOutline = QImage(QDir::currentPath() + "/Images/CircleBrush_Outline.png");
            //    brushType = "circle";
            //}
            //else {
            //    brush = QImage(QDir::currentPath() + "/Images/ChalkRot.png");
            //    brushTool->brushOutline = QImage(QDir::currentPath() + "/Images/ChalkRot_Outline.png");
            //    brushType = "chalk";

            //}
        }
        if (event->key() == 91)
        {
            //alterBrushSize(-1);
        }
        if (event->key() == 93) {
            //alterBrushSize(1);
        }
    }
    //    void keyReleaseEvent(QKeyEvent* event) override
    //    {
    //        if (event->isAutoRepeat())
    //        {
    //            return;
    //        }
    //        if (event->key() == Qt::Key_Space)
    //        {
    //            lastPanPoint = QPoint();
    //            panningEnabled = false;
    //            setCursor(Qt::ArrowCursor);
    //        }
    //    }
    //    void applyZoom(float zoomAmount)
    //    {
    //
    //        if (1 <= zoomPercentage * zoomAmount <= 12800)
    //        {
    //            zoomPercentage = zoomPercentage * zoomAmount;
    //        }
    //        else if (zoomPercentage < 1) { zoomPercentage = 1; }
    //        else { zoomPercentage = 12800; }
    //        QPointF hoverFromCenter = rect().center() - hoverPoint;
    //        hoverPoint = rect().center() - hoverFromCenter;
    //        repaint();
    //        update();
    //
    //    }
    //
    //    void zoomIn()
    //    {
    //        applyZoom((1.111));
    //    }
    //
    //    void zoomOut()
    //    {
    //        applyZoom((0.9));
    //    }
    //
    //    void resetZoom()
    //    {
    //        zoomPercentage = 100.0;
    //        applyZoom(1);
    //    }
    //
    //    QPoint getScaledPoint(QPoint pos) {
    //        return  QPoint(((pos.x() - panOffset.x())), ((pos.y() - panOffset.y())));
    //    }
    //
    //    QPointF getScaledPointF(QPointF pos) {
    //        return QPointF(((pos.x() - panOffset.x())), ((pos.y() - panOffset.y())));
    //    }
    //
    //    void alterBrushSize(int multiplier)
    //    {
    //        int alterAmoumt;
    //        if (brushSize < 10) {
    //            alterAmoumt = 1;
    //        }
    //        else if (brushSize < 50) {
    //            alterAmoumt = 5;
    //        }
    //        else if (brushSize < 100) {
    //            alterAmoumt = 10;
    //        }
    //        else if (brushSize < 200) {
    //            alterAmoumt = 25;
    //        }
    //        else {
    //            alterAmoumt = 100;
    //        }
    //
    //        brushSize = brushSize + alterAmoumt * multiplier;
    //        brushSize = qBound(1, brushSize, 500);
    //        update();
    //
    //    }
    //    void mousePressEvent(QMouseEvent* event) override
    //    {
    //        if (usingTablet == true) return;
    //        if (layers.count() < 1) return;
    //
    //        if (event->button() == Qt::LeftButton) {
    //            if (panningEnabled) {
    //                lastPanPoint = event->pos();
    //                isPanning = true;
    //            }
    //            else {
    //                drawing = true;
    //                lastPoint = mapToImage(getScaledPoint(event->pos()));
    //                if (!isErasing)
    //                {
    //                    colour = colourWindow->updateColour();
    //                }
    //                brush = adjustBrushColour(brush, colour);
    //            }
    //
    //        }
    //    }
    //
    //    void mouseMoveEvent(QMouseEvent* event) override
    //    {
    //
    //        if (usingTablet == true) return;
    //        if (layers.count() < 1) return;
    //        if (isPanning)
    //        {
    //            if (!lastPanPoint.isNull()) {
    //                QPoint change = event->pos() - lastPanPoint;
    //                panOffset += change;
    //                lastPanPoint = event->pos();
    //            }
    //        } else{
    //            if (drawing && (event->buttons() & Qt::LeftButton)) {
    //                QPoint currentPoint = mapToImage(getScaledPoint(event->pos()));
    //
    //                QPainter painter(&layers[selectedLayerIndex]);
    //
    //                painter.setRenderHint(QPainter::Antialiasing, true);
    //                if (isErasing) {
    //                    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    //                    repaint();
    //                }
    //                drawStroke(painter, lastPoint.toPointF(), currentPoint.toPointF(), 1.0);
    //                lastPoint = currentPoint;
    //                update();
    //            }
    //            else {
    //                hoverPoint =  event->pos();
    //                isHovering = true;
    //                if (delayCounter == 5) {
    //                    repaint();
    //                    delayCounter = 0;
    //                }
    //
    //            }
    //        }
    //        update();
    //    }
    //
    //    void mouseReleaseEvent(QMouseEvent* event) override
    //       {
    //        if (isPanning) {
    //            isPanning = false;
    //        }
    //
    //        if (usingTablet == true) return;
    //
    //        if (event->button() == Qt::LeftButton) {
    //            drawing = false;
    //            pushUndo(layers);
    //            redoStack.clear();
    //        }
    //
    //    }
    //
    //    void paintEvent(QPaintEvent* event) override
    //    {
    //
    //        QPainter painter(this);
    //        QPoint center = rect().center();
    //        QPoint hoverOffset = center - hoverPoint.toPoint();
    //
    //        painter.translate(center);
    //        painter.scale(zoomPercentage / 100, zoomPercentage / 100);
    //        painter.translate(panOffset / (zoomPercentage / 100.0));
    //
    //        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    //        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //
    //        QPointF topLeft(-image.width() / 2.0, -image.height() / 2.0);
    //        
    //        painter.drawImage(topLeft, pngBackground);
    //
    //        for (const QImage layer : layers) {
    //            painter.drawImage(topLeft, layer);
    //        }
    //
    //        painter.scale(100/ zoomPercentage, 100/zoomPercentage);
    //
    //        painter.translate(-center);
    //   
    //        if (isErasing) {
    //            painter.setCompositionMode(QPainter::CompositionMode_Clear);
    //
    //        }
    //        if (isHovering) if (!panningEnabled) {
    //            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //            qreal size = brushSize;
    //            QImage brushHover = brushOutline.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //
    //            QTransform t;
    //            t.rotate(xTilt * 3);
    //            t.scale(zoomPercentage/100.0, zoomPercentage / 100.0);
    //            brushHover = brushHover.transformed(t, Qt::SmoothTransformation);
    //
    //
    //
    //            QPointF drawPos(hoverPoint.x() - brushHover.width()  / 2, hoverPoint.y() - brushHover.height()   / 2);
    //            drawPos = center - hoverOffset - panOffset;
    //            drawPos = QPoint(drawPos.x() - brushHover.width() / 2, drawPos.y() - brushHover.height() / 2);
    //
    //            painter.drawImage(drawPos, brushHover);
    //        }
    //
    //
    //    }
    //
private:
    //    bool panningEnabled = false;
    //    bool isPanning = false;
    //    QPoint lastPanPoint;
    //    QPoint panOffset;
    //
    //    int selectedLayerIndex = 1;
    //    QImage pngBackground;
    //    bool isHovering;
    //    QPointF currentPoint;
    //    QPointF hoverPoint;
    //    QPointF pan;
    ColourWindow* colourWindow = nullptr;
    LayerManager* layerManager = nullptr;
    BrushTool* brushTool = nullptr;
    //    qreal xTilt;
    //    qreal yTilt;
    //    bool drawing = false;
    //    bool usingTablet = false;
    //    bool isErasing = false;
    //    QPixmap TESTPIXMAP;
    //    int delayCounter;
    //
    //    QImage brush = QImage(QDir::currentPath() + "/Images/ChalkRot.png");
    //
    //    QImage brushOutline = QImage(QDir::currentPath() + "/Images/ChalkRot_Outline.png");
    //    std::string brushType = "chalk";
    //
    //    QColor colour = QColor(Qt::red);
    //
    //    QPoint lastPoint;
    //    QPointF lastPointF;
    //
    //    QImage image;
    //    QImage background;
    //    QImage originalImage;
    //    QVector<QImage> layers;
    //    QImage selectedImage = image;
    //
    //
    //    QStack<QVector<QImage>> undoStack;
    //    QStack<QVector<QImage>> redoStack;
    //
    //
    //    int brushSize = 50;
    //    float zoomPercentage = 100.0;
    //
    //    //QMenu* viewMenu;
    //
    //
    //    //void createDockWindows()
    //    //{
    //    //    //self.color_button = QPushButton("Pick Color")
    //    //    //    self.color_button.setCheckable(True)
    //    //    //    self.color_button.clicked.connect(self.color_dialog)
    //    //    //    dock = QDockWidget("Colour", self)
    //    //    //    dock.setAllowedAreas(Qt.DockWidgetArea.LeftDockWidgetArea
    //    ////            | Qt.DockWidgetArea.RightDockWidgetArea
    //    ////            | Qt.DockWidgetArea.TopDockWidgetArea)
    //    ////        self.setDockOptions(QMainWindow.DockOption.AllowNestedDocks)
    //    ////        self.color_button.setFixedSize(330, 100)
    //    ////        # Set up main dark mode for entire docked windows
    //    ////        self.setStyleSheet("""
    //    ////            background - color: #2c2c2c;
    //    ////color: #ffffff;
    //    ////    font - family: Segoe UI;
    //    ////    font - size: 12px;
    //    ////    selection - background - color: #424242;
    //    ////    """)  
    //    ////        # Set up color button values of black background and white text as default
    //    ////        self.color_button.setStyleSheet(f"""
    //    ////            background - color: #000000;
    //    ////color: #ffffff;
    //    ////    font - family: Segoe UI;
    //    ////    font - size: 12px;
    //    ////    """) 
    //
    //    ////        dock.setWidget(self.color_button)
    //    ////        self.addDockWidget(Qt.DockWidgetArea.RightDockWidgetArea, dock)
    //    //// 
    //    //// 
    //    //    QWidget window(this);
    //    //    QDockWidget dock = QDockWidget("Colour Wheel");
    //    //    dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea);
    //    //    //dock.allowNestedDocks
    //    //    dock.setWidget(colourWindow);
    //    //    window.addDockWi
    //    //    
    //    //    
    //
    //    //}
    //
    void createDockWindows()
    {
        QDockWidget* dock = new QDockWidget(tr("Customers"), this);
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        //QListWidget* customerList = new QListWidget(dock);
        //customerList->addItems(QStringList()
        //    << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
        //    << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
        //    << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
        //    << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
        //    << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
        //    << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
        colourWindow->setMinimumSize(200, 200);
        dock->setWidget(colourWindow);
        addDockWidget(Qt::RightDockWidgetArea, dock);
        //viewMenu->addAction(dock->toggleViewAction());

        dock = new QDockWidget(tr("Paragraphs"), this);
        //QListWidget* paragraphsList = new QListWidget(dock);
        //paragraphsList->addItems(QStringList()
        //    << "Thank you for your payment which we have received today."
        //    << "Your order has been dispatched and should be with you "
        //    "within 28 days."
        //    << "We have dispatched those items that were in stock. The "
        //    "rest of your order will be dispatched once all the "
        //    "remaining items have arrived at our warehouse. No "
        //    "additional shipping charges will be made."
        //    << "You made a small overpayment (less than $5) which we "
        //    "will keep on account for you, or return at your request."
        //    << "You made a small underpayment (less than $1), but we have "
        //    "sent your order anyway. We'll add this underpayment to "
        //    "your next bill."
        //    << "Unfortunately you did not send enough money. Please remit "
        //    "an additional $. Your order will be dispatched as soon as "
        //    "the complete amount has been received."
        //    << "You made an overpayment (more than $5). Do you wish to "
        //    "buy more items, or should we return the excess to you?");
        dock->setWidget(layerManager);
        addDockWidget(Qt::RightDockWidgetArea, dock);

        dock = new QDockWidget(tr("WindowFileName"), this);

        dock->setWidget(brushTool);
        addDockWidget(Qt::LeftDockWidgetArea, dock);
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}



