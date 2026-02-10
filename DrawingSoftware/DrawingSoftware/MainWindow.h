#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QLayout>

#include <ColourWindow.h>
#include <LayerManager.h>
#include <UIManager.h>
#include <ToolSelectionMenu.h>
#include <BrushControlsWindow.h>

#include <BrushTool.h>
#include <LassoTool.h>
#include <BucketTool.h>
#include <PolygonalLassoTool.h>
#include <MagicWandTool.h>
#include <RectangularSelectionTool.h>
#include <EllipticalSelectionTool.h>



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
    MagicWandTool* magicWandTool = nullptr;
    RectangularSelectionTool* rectangularSelectionTool = nullptr;
    EllipticalSelectionTool* ellipticalSelectionTool = nullptr;

    ToolSelectionMenu* toolSelectionMenu = nullptr;
    UIManager* uiManager = nullptr;
    BrushControlsWindow* brushControlsWindow = nullptr;
    void enableBucketTool();
    void enableBrushTool();
    void enableLassoTool();
    void enablePolygonalLassoTool();
    void enableMagicWandTool();
    void enableRectangularSelectionTool();
    void enableEllipticalSelectionTool();
    void enableEraser();

    void disableMagicWandTool();
    void disablePolygonalLassoTool();
    void disableLassoTool();
    void disableBrushTool();
    void disableBucketTool();
    void disableRectangularSelectionTool();
    void disableEllipticalSelectionTool();
    void disableEraser();

    void createDockWindows();

    QWidget currentTool;
};

