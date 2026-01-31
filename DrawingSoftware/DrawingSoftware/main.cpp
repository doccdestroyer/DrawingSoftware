//#include "QtWidgetsApplicationTest.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    QtWidgetsApplicationTest window;
//    window.show();
//    return app.exec();
//}

//#include <QApplication>
//#include <QWidget>
//#include <QEvent>
//#include <QMouseEvent>
//#include <QDebug>
//#include <string>
//#include <cstdbool>
//
//class MyWindow : public QWidget
//{
//public:
//    MyWindow()
//    {
//        isBlack = true;
//        setStyleSheet("background-color: rgb(0, 0, 0);");
//    }
//protected:
//    bool event(QEvent* event) override
//    {
//        if (event->type() == QEvent::MouseButtonPress)
//        {
//            if (isBlack == true) {
//                setStyleSheet("background-color: rgb(255, 255, 255);");
//            }
//            else {
//                setStyleSheet("background-color: rgb(0, 0, 0);");
//
//            }z`
//            isBlack = !isBlack;
//
//            //auto* mouseEvent = static_cast<QMouseEvent*>(event);
//            //qDebug() << "Mouse pressed at:"
//            //    << mouseEvent->position();
//            //return true; // event handled
//
//        }
//
//        return QWidget::event(event); // pass other events on
//    }
//private:
//    bool isBlack;
//};
//int main(int argc, char* argv[])
//{
//    QApplication app(argc, argv);
//
//    //std::string blackRGB = "(0, 0, 0)";
//    //bool isBlack = true;
//
//
//    MyWindow window;
//    window.resize(400, 300);
//    window.setWindowTitle("Test");
//    //window.setStyleSheet("background-color: rgb(0, 0, 0);");
//    window.show();
//
//    return app.exec();
//}

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

class MyWindow : public QWidget
{
public:
    MyWindow()
    {
        setWindowTitle("drawing software like you've never seen before");
        setFixedSize(1920, 1080);
        setStyleSheet("background-color: rgb(220,220,220);");
        setAttribute(Qt::WA_TabletTracking);

        image = QImage(900, 900, QImage::Format_RGB32);
        image.fill(Qt::white);
        undoStack.push(image);
    }

protected:
    void tabletEvent(QTabletEvent* event) override
    {
        if (event->type() == QEvent::TabletPress) {
            drawing = true;
            usingTablet = true;
            lastPoint = mapToImage(event->position());
        }

        if (event->type() == QEvent::TabletMove && drawing) {
            QPoint currentPoint = mapToImage(event->position());
            qreal pressure = event->pressure();

            QPainter painter(&image);
            int penWidth = 1 + (pressure * 5);
            painter.setPen(QPen(colour, penWidth, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(lastPoint, currentPoint);

            qDebug() << "pressure:" << event->pressure();

            lastPoint = currentPoint;
            update();
        }

        if (event->type() == QEvent::TabletRelease) {
            drawing = false;
            usingTablet = true;
            pushUndo(image);
            redoStack.clear();
        }

        event->accept();
    }

    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier)
            undo();
        if (event->key() == Qt::Key_Y && event->modifiers() & Qt::ControlModifier)
            redo();
        if (event->key() == Qt::Key_C) {
            colour = QColorDialog::getColor();
            //if (colour.isValid()) {
            //    
            //}
        }
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        if (usingTablet == true) return;

        if (event->button() == Qt::LeftButton) {
            drawing = true;
            lastPoint = mapToImage(event->position());
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (usingTablet == true) return;

        if (drawing && (event->buttons() & Qt::LeftButton)) {
            QPoint currentPoint = mapToImage(event->position());

            QPainter painter(&image);
            painter.setPen(QPen(colour, 2, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(lastPoint, currentPoint);

            lastPoint = currentPoint;
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (usingTablet == true) return;

        if (event->button() == Qt::LeftButton) {
            drawing = false;
            pushUndo(image);
            redoStack.clear();
        }
    }

    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        QPoint center = rect().center();
        QPoint topLeft = center - QPoint(image.width() / 2, image.height() / 2);
        painter.drawImage(topLeft, image);
    }

private:
    bool drawing = false;
    bool usingTablet = false;

    //QImage stamp(":/Images/.png");


    QColor colour;

    QPoint lastPoint;
    QImage image;
    QStack<QImage> undoStack;
    QStack<QImage> redoStack;

    void pushUndo(const QImage& img)
    {
        undoStack.push(img);
        if (undoStack.size() > 50) undoStack.remove(0);
    }

    // Mouse version
    QPoint mapToImage(const QPoint& p)
    {
        QPoint center = rect().center();
        QPoint topLeft = center - QPoint(image.width() / 2, image.height() / 2);
        return p - topLeft;
    }

    // Tablet version
    QPoint mapToImage(const QPointF& p)
    {
        return mapToImage(p.toPoint());
    }

    void undo()
    {
        if (undoStack.size() <= 1) return;
        redoStack.push(undoStack.pop());
        image = undoStack.top();
        update();
    }

    void redo()
    {
        if (redoStack.isEmpty()) return;
        image = redoStack.pop();
        undoStack.push(image);
        update();
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MyWindow window;
    window.show();
    return app.exec();

    // felix was here
}
