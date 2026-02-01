#pragma once

#include <QWidget>
#include <QStack>
#include <QImage>
#include <QVector>
#include <QDir>
#include <QMouseEvent>
#include <QTabletEvent>
#include <QPainter>

#include <ColourWindow.h>
#include "LayerManager.h"


class BrushTool : public QWidget
{
    Q_OBJECT

public:
    explicit BrushTool(QWidget* parent = nullptr);
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void undo();
    void redo();
    LayerManager* layerManager;
    ColourWindow* colourWindow;

    QVector<QImage> layers;
    QImage overlay;

    float zoomPercentage = 100.0;
    QPoint panOffset;

    QVector<QPainterPath> selectionsPath;

    //signals:


    //private slots:

protected:
    void tabletEvent(QTabletEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void applyZoom(float zoomAmount);
    QPoint getScaledPoint(QPoint pos);
    QPointF getScaledPointF(QPointF pos);
    void alterBrushSize(int multiplier);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void lassoEnabled();

private slots:
    //void changeToLasso();

private:
    bool panningEnabled = false;
    bool isPanning = false;
    QPoint lastPanPoint;

    bool inSelection;

    int selectedLayerIndex = 1;
    QImage pngBackground;
    bool isHovering;
    QPointF currentPoint;
    QPointF hoverPoint;
    QPointF pan;

    //LayerManager* layerManager;

    qreal xTilt;
    qreal yTilt;
    bool drawing = false;
    bool usingTablet = false;
    bool isErasing = false;
    bool isDrawing = false;
    int delayCounter;

    QImage brush;

    QImage brushOutline;
    std::string brushType;

    QColor colour = QColor(Qt::red);

    QPoint lastPoint;
    QPointF lastPointF;

    QImage image;
    QImage background;
    QImage originalImage;
    QImage selectedImage;


    QStack<QVector<QImage>> undoStack;
    QStack<QVector<QImage>> redoStack;


    int brushSize = 50;


    void removeLayer(int layer);
    void pushUndo(const QVector<QImage>& layers);
    QPoint mapToImage(const QPoint& p);
    QPointF mapToImageF(const QPointF& p);

    void drawStroke(QPainter& p, const QPointF& from, const QPointF& to, qreal pressure);
    void drawBrush(QPainter& p, const QPointF& pos, qreal pressure);
    QImage adjustBrushColour(const QImage& brush, const QColor& color);
};


