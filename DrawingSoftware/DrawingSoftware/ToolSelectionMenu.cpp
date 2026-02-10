#include <ToolSelectionMenu.h>

ToolSelectionMenu::ToolSelectionMenu(QMainWindow* parent) : QMainWindow(parent)
{
	setWindowFlags(Qt::WindowStaysOnTopHint);
	setFixedSize(80, 1000);
	setWindowTitle("Tools");

	selectedTool = "Brush";
	//refreshTool();

	createToolBar();
}

void ToolSelectionMenu::createToolBar()
{
	QToolBar* toolBar = addToolBar(tr("Tools"));

	toolBar->setMovable(false);
	toolBar->setFloatable(false);
	toolBar->setOrientation(Qt::Vertical);
	toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

	QAction* brushAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/pen.png"),
		tr("&BrushTool"),
		this);
	brushAction->setStatusTip(tr("&Brush Tool"));;
	connect(brushAction, &QAction::triggered, this, [&]() {
		enableBrushTool();
		});
	toolBar->addAction(brushAction);


	QAction* lassoAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/lasso.png"),
		tr("&LassoTool"),
		this);
	lassoAction->setStatusTip(tr("&Lasso Tool"));;
	connect(lassoAction, &QAction::triggered, this, [&]() {
		enableLassoTool();
		});
	toolBar->addAction(lassoAction);

	QAction* bucketAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/bucket.png"),
		tr("&BucketTool"),
		this);
	bucketAction->setStatusTip(tr("&Bucket Tool"));;
	connect(bucketAction, &QAction::triggered, this, [&]() {
		enableBucketTool();
		});
	toolBar->addAction(bucketAction);

	QAction* polygonalAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/polylasso.png"),
		tr("&PolygonalLasso"),
		this);
	polygonalAction->setStatusTip(tr("&Polygonal Lasso Tool"));;
	connect(polygonalAction, &QAction::triggered, this, [&]() {
		enablePolygonalLassoTool();
		});
	toolBar->addAction(polygonalAction);

	QAction* magicWandAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/magicwand.png"),
		tr("&MagicWand"),
		this);
	magicWandAction->setStatusTip(tr("&Magic Wand Tool"));;
	connect(magicWandAction, &QAction::triggered, this, [&]() {
		enableMagicWandTool();
		});
	toolBar->addAction(magicWandAction);

	QAction* rectangularSelectionAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/rectangle.png"),
		tr("&RetangularSelection"),
		this);
	rectangularSelectionAction->setStatusTip(tr("&Rectangular Selection Tool"));;
	connect(rectangularSelectionAction, &QAction::triggered, this, [&]() {
		enableRectangularSelectionTool();
		});
	toolBar->addAction(rectangularSelectionAction);

	QAction* ellipticalSelectionAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/ellipse.png"),
		tr("&EllipticalSelection"),
		this);
	ellipticalSelectionAction->setStatusTip(tr("&Elliptical Selection Tool"));;
	connect(ellipticalSelectionAction, &QAction::triggered, this, [&]() {
		ellipticalSelectionEnabled();
		});
	toolBar->addAction(ellipticalSelectionAction);

	QAction* eraserAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/eraser.png"),
		tr("&Eraser"),
		this);
	eraserAction->setStatusTip(tr("&Eraser Tool"));;
	connect(eraserAction, &QAction::triggered, this, [&]() {
		enableEraserTool();
		});
	toolBar->addAction(eraserAction);
}


void ToolSelectionMenu::disableTool()
{
	if (selectedTool == "Brush")
	{
		emit brushDisabled();
	}
	else if (selectedTool == "Lasso")
	{
		emit lassoDisabled();
	}
	else if (selectedTool == "Bucket")
	{
		emit bucketDisabled();
	}
	else if (selectedTool == "PolygonalLasso")
	{
		emit polygonalLassoDisabled();
	} 
	else if (selectedTool == "MagicWand")
	{
		emit magicWandDisabled();
	}
	else if (selectedTool == "RectangularSelection")
	{
		emit rectangularSelectionDisabled();
	}
	else if (selectedTool == "EllipticalSelection")
	{
		emit ellipticalSelectionDisabled();
	}
	else if (selectedTool == "Eraser")
	{
		emit eraserDisabled();
	}
}

void ToolSelectionMenu::enableBrushTool()
{

	disableTool();
	emit brushEnabled();
	selectedTool = "Brush";

}

void ToolSelectionMenu::enableLassoTool()
{
	disableTool();
	emit lassoEnabled();
	selectedTool = "Lasso";

}

void ToolSelectionMenu::enableBucketTool()
{
	disableTool();
	emit bucketEnabled();
	selectedTool = "Bucket";

}

void ToolSelectionMenu::enablePolygonalLassoTool()
{
	disableTool();
	emit polygonalLassoEnabled();
	selectedTool = "PolygonalLasso";

}

void ToolSelectionMenu::enableMagicWandTool()
{
	disableTool();
	emit magicWandEnabled();
	selectedTool = "MagicWand";

}

void ToolSelectionMenu::enableRectangularSelectionTool()
{
	disableTool();
	emit rectangularSelectionEnabled();
	selectedTool = "RectangularSelection";

}

void ToolSelectionMenu::enableEllipticalSelectionTool()
{
	disableTool();
	emit ellipticalSelectionEnabled();
	selectedTool = "EllipticalSelection";

}

void ToolSelectionMenu::enableEraserTool()
{
	disableTool();
	emit eraserEnabled();
	selectedTool = "Eraser";

}



