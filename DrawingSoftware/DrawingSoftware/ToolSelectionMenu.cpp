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


