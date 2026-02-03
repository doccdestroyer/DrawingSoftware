#include <ToolSelectionMenu.h>

ToolSelectionMenu::ToolSelectionMenu(QMainWindow* parent) : QMainWindow(parent)
{
	setWindowFlags(Qt::WindowStaysOnTopHint);
	setFixedSize(80, 1000);
	setWindowTitle("Tools");

	//selectedTool = "Brush";
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
		QIcon(QDir::currentPath() + "/Images/Icons/pen.png"),  // icon path (Qt resource or file)
		tr("&BrushTool"),
		this);
	brushAction->setStatusTip(tr("&Brush Tool"));;
	connect(brushAction, &QAction::triggered, this, [&]() {
		enableBrushTool();
		});	
	toolBar->addAction(brushAction);


	QAction* lassoAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/Icons/lasso.png"),  // icon path (Qt resource or file)
		tr("&BrushTool"),
		this);
	lassoAction->setStatusTip(tr("&Brush Tool"));;
	connect(lassoAction, &QAction::triggered, this, [&]() {
		enableLassoTool();
		});
	toolBar->addAction(lassoAction);
}



void ToolSelectionMenu::enableBrushTool()
{
	emit brushEnabled();
}

void ToolSelectionMenu::enableLassoTool()
{
	emit lassoEnabled();
}