#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QWidget>
#include <QIcon>
#include <QDir>
#include <QAction>

#include <QVBoxLayout>
#include <QDockWidget>


#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QIcon>

#include <QActionGroup>
class ToolSelectionMenu : public QMainWindow
{
    Q_OBJECT
public:

    ToolSelectionMenu(QMainWindow* parent = nullptr);
    QDockWidget* dock;

signals:
    void brushEnabled();
    void lassoEnabled();

private:
    QIcon icon;

    //void createToolBars();
    void createToolBar();
    //void updateTool();
    //void refreshTool();

    void enableBrushTool();
    void enableLassoTool();



    //std::string selectedTool;
};