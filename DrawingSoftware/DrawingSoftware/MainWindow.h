#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include <ColourWindow.h>
#include <LayerManager.h>
#include <BrushTool.h>
#include <LassoTool.h>
#include <BucketTool.h>
#include <PolygonalLassoTool.h>
#include <UIManager.h>
#include <QDockWidget>
#include <ToolSelectionMenu.h>
#include <QHBoxLayout>
#include <QLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    void keyPressEvent(QKeyEvent* event);
    int TESTVARIABLE = 69;
    QDockWidget* dock;


private:

    ColourWindow* colourWindow = nullptr;
    LayerManager* layerManager = nullptr;
    BrushTool* brushTool = nullptr;
    LassoTool* lassoTool = nullptr;
    PolygonalLassoTool* polygonalLassoTool = nullptr;
    BucketTool* bucketTool = nullptr;
    ToolSelectionMenu* toolSelectionMenu = nullptr;
    UIManager* uiManager = nullptr;

    void enableBucketTool();
    void enableBrushTool();
    void enableLassoTool();
    void enablePolygonalLassoTool();

    void disablePolygonalLassoTool();
    void disableLassoTool();
    void disableBrushTool();
    void disableBucketTool();

    void createDockWindows();

    QWidget currentTool;
};

