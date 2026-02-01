#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include <ColourWindow.h>
#include <LayerManager.h>
#include <BrushTool.h>
#include <LassoTool.h>
#include <QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    void keyPressEvent(QKeyEvent * event);
    int TESTVARIABLE = 69;
    QDockWidget* dock;

private:

    ColourWindow* colourWindow = nullptr;
    LayerManager* layerManager = nullptr;
    BrushTool* brushTool = nullptr;
    LassoTool* lassoTool = nullptr;
 
    void createDockWindows();
};