
#include <MainWindow.h>

MainWindow::MainWindow()
{
        setWindowTitle("Bad Apple");
        setFixedSize(1920, 1080);
        setStyleSheet("background-color: rgb(30,30,30);");
        setAttribute(Qt::WA_TabletTracking);
        setAttribute(Qt::WA_MouseTracking);
        setMouseTracking(true);

        //setFocusPolicy(Qt::StrongFocus);


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
        lassoTool = new LassoTool(this);
        bucketTool = new BucketTool(this);

        toolSelectionMenu = new ToolSelectionMenu(this);


        colourWindow = brushTool->colourWindow;
        //colourWindow->show();

        layerManager = brushTool->layerManager;
        //layerManager->show();

        //toolSelectionMenu->show();
        createDockWindows();



        connect(brushTool, &BrushTool::brushDisabled,
            this, [&]()
            {
                disableBrushTool();
            });

        connect(lassoTool, &LassoTool::lassoDisabled,
            this, [&]()
            {
                disableLassoTool();
            });




        connect(brushTool, &BrushTool::lassoEnabled,
            this, [&]()
            {
                enableLassoTool();
            });
        connect(brushTool, &BrushTool::bucketEnabled,
            this, [&]()
            {
                enableBucketTool();
            });
        connect(lassoTool, &LassoTool::brushEnabled,
            this, [&]()
            {
                enableBrushTool();
            });

        connect(toolSelectionMenu, &ToolSelectionMenu::brushEnabled,
            this, [&]()
            {
                enableBrushTool();
            });
        connect(toolSelectionMenu, &ToolSelectionMenu::lassoEnabled,
            this, [&]()
            {
                enableLassoTool();
            });


    }

void MainWindow::disableBrushTool()
{
    layerManager->updateLayers(brushTool->layers,
        brushTool->overlay,
        brushTool->zoomPercentage,
        brushTool->panOffset,
        brushTool->selectionsPath);
}

void MainWindow::disableLassoTool()
{
    layerManager->updateLayers(lassoTool->layers, 
        lassoTool->overlay, 
        lassoTool->zoomPercentage, 
        lassoTool->panOffset, 
        lassoTool->selectionsPath);
}

void MainWindow::enableLassoTool()
{
    dock->setWidget(lassoTool);
    lassoTool->layers = layerManager->layers;
    lassoTool->zoomPercentage = layerManager->zoomPercentage;
    lassoTool->panOffset = layerManager->panOffset;
    lassoTool->selectionsPath = layerManager->selectionsPath;
    lassoTool->overlay = layerManager->selectionOverlay;
}

void MainWindow::enableBrushTool()
{
    dock->setWidget(brushTool);
    brushTool->layers = layerManager->layers;
    brushTool->zoomPercentage = layerManager->zoomPercentage;
    brushTool->panOffset = layerManager->panOffset;
    brushTool->selectionsPath = layerManager->selectionsPath;
    brushTool->overlay = layerManager->selectionOverlay;
}




void MainWindow::enableBucketTool()
{
    //layerManager->updateLayers(brushTool->layers, brushTool->overlay);
    //brushTool->zoomPercentage = lassoTool->zoomPercentage;
    //brushTool->panOffset = lassoTool->panOffset;
    //brushTool->selectionsPath = lassoTool->selectionsPath;

    dock->setWidget(bucketTool);
    bucketTool->layers = layerManager->layers;
    //bucketTool->overlay = layerManager->selectionOverlay;
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    //if (event->key() == 61 && event->modifiers() & Qt::ControlModifier)
    //    brushTool->zoomIn();
    //if (event->key() == 45 && event->modifiers() & Qt::ControlModifier)
    //    brushTool->zoomOut();

    //if (event->key() == Qt::Key_0 && event->modifiers() & Qt::ControlModifier)
    //    brushTool->resetZoom();

    //if (event->key() == Qt::Key_Z && event->modifiers() & Qt::ControlModifier)
    //    brushTool->undo();
    //layerManager->undo();
    //if (event->key() == Qt::Key_Y && event->modifiers() & Qt::ControlModifier)
    //    brushTool->redo();
    //layerManager->redo();

    //if (event->key() == Qt::Key_Space)
    //{
    //    //panningEnabled = true;
    //    setCursor(Qt::OpenHandCursor);
    //}

    //if (event->key() == Qt::Key_E)
    //{
    //    /*  if (isErasing == true) {
    //          isErasing = false;
    //          colour = colourWindow->updateColour();
    //      }
    //      else {

    //          isErasing = true;
    //      }*/
    //}
    //if (event->key() == Qt::Key_L)
    //{
    //    layerManager->updateLayers(brushTool->layers, brushTool -> overlay);
    //    dock->setWidget(lassoTool);
    //    lassoTool->layers = layerManager->layers;
    //    lassoTool->overlay = layerManager->selectionOverlay;


    //}
    //if (event->key() == Qt::Key_B)
    //{
    //    layerManager->updateLayers(lassoTool->layers, lassoTool->overlay);
    //    dock->setWidget(brushTool);
    //    brushTool->layers = layerManager->layers;
    //    brushTool->overlay = layerManager->selectionOverlay;
   
    //    //if (brushType == "chalk") {
   
    //    //    brush = QImage(QDir::currentPath() + "/Images/CircleBrush.png");
    //    //    brushOutline = QImage(QDir::currentPath() + "/Images/CircleBrush_Outline.png");
    //    //    brushType = "circle";
    //    //}
    //    //else {
    //    //    brush = QImage(QDir::currentPath() + "/Images/ChalkRot.png");
    //    //    brushTool->brushOutline = QImage(QDir::currentPath() + "/Images/ChalkRot_Outline.png");
    //    //    brushType = "chalk";
   
    //    //}
    //}

    //if (event->key() == 91)
    //{
    //    //alterBrushSize(-1);
    //}

    //if (event->key() == 93)
    //{
    //    //alterBrushSize(1);
    //}

}

void MainWindow::createDockWindows()
{
    dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    colourWindow->setMinimumSize(200, 200);
    dock->setWidget(colourWindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);



    dock = new QDockWidget(tr("Paragraphs"), this);
    dock->setWidget(layerManager);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    QWidget *centralWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(centralWidget);

    QDockWidget* ToolDock = new QDockWidget(tr("Tools"), this);
    ToolDock->setWidget(toolSelectionMenu);
    addDockWidget(Qt::LeftDockWidgetArea, ToolDock);
    //layout->addWidget(toolSelectionMenu);

    dock = new QDockWidget(tr("WindowFileName"), this);
    dock->setWidget(brushTool);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    //layout->addWidget(brushTool);
    //dock->setLayout(layout);

    splitDockWidget(ToolDock, dock, Qt::Horizontal);
    //addDockWidget(Qt::LeftDockWidgetArea, dock);

}
