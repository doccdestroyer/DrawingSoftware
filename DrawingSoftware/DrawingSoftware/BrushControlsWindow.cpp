#include <BrushControlsWindow.h>

BrushControlsWindow::BrushControlsWindow(QMainWindow* parent)
	: QMainWindow(parent)
{
	setWindowTitle("Brush Controls");
	resize(300, 300);
	setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

	controlsList = new QListWidget(this);
	controlsList->addItems({ "Brush Tip Shape", "Scattering", "Pen Pressure"});
	controlsList->setSortingEnabled(true);
	controlsList->setMaximumSize(110, 300);

	//QIcon roundIcon = QIcon(QDir::currentPath() + "/Images/CircleBrush.png");
	//QPushButton* roundBrushButton = new QPushButton(roundIcon, " Round Brush", this);
	//roundBrushButton->setIconSize(QSize(30, 30));
	//roundBrushButton->setMaximumSize(190, 30);

	//QIcon chalkIcon = QIcon(QDir::currentPath() + "/Images/ChalkRot.png");
	//QPushButton* chalkBrushButton = new QPushButton(chalkIcon, " Chalk Brush ", this);
	//chalkBrushButton->setIconSize(QSize(30, 30));
	//chalkBrushButton->setMaximumSize(190, 30);

	//QIcon flatChalkIcon = QIcon(QDir::currentPath() + "/Images/HorizontalBrush.png");
	//QPushButton* flatChalkBrushButton = new QPushButton(flatChalkIcon, " Horizontal Chalk Brush ", this);
	//flatChalkBrushButton->setIconSize(QSize(30, 30));
	//flatChalkBrushButton->setMaximumSize(190, 30);

	//auto* brushLayout = new QVBoxLayout(this);

	//auto* mainLayout = new QHBoxLayout(this);
	//mainLayout->addWidget(controlsList);

	//brushLayout->addWidget(roundBrushButton);
	//brushLayout->addWidget(chalkBrushButton);


	//mainLayout->addLayout(brushLayout);

	
	QDockWidget* generalDock = new QDockWidget(tr("Layers"), this);
	generalDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	generalDock->setWidget(controlsList);
	addDockWidget(Qt::LeftDockWidgetArea, generalDock);

	/*QDockWidget* chalkBrushDock = new QDockWidget(this);
	chalkBrushDock->setWidget(chalkBrushButton);
	addDockWidget(Qt::RightDockWidgetArea, chalkBrushDock);

	QDockWidget* roundBrushDock = new QDockWidget(this);
	roundBrushDock->setWidget(roundBrushButton);
	addDockWidget(Qt::RightDockWidgetArea, roundBrushDock);

	QDockWidget* flatChalkBrushDock = new QDockWidget(this);
	flatChalkBrushDock->setWidget(roundBrushButton);
	addDockWidget(Qt::RightDockWidgetArea, flatChalkBrushDock);

	splitDockWidget(roundBrushDock, chalkBrushDock, Qt::Vertical);
	splitDockWidget(chalkBrushDock, flatChalkBrushDock, Qt::Vertical);*/

	QToolBar* toolBar = addToolBar(tr("Tools"));

	toolBar->setMovable(false);
	toolBar->setFloatable(false);
	toolBar->setOrientation(Qt::Vertical);
	toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

	QAction* chalkAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/ChalkRot.png"),
		tr("&BrushTool"),
		this);
	chalkAction->setStatusTip(tr("&Brush Tool"));;
	connect(chalkAction, &QAction::triggered, this, [&]() {
		emit chalkEnabled();
		});
	toolBar->addAction(chalkAction);

	QAction* roundAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/CircleBrush.png"),
		tr("&BrushTool"),
		this);
	roundAction->setStatusTip(tr("&Brush Tool"));;
	connect(roundAction, &QAction::triggered, this, [&]() {
		emit roundEnabled();
		});
	toolBar->addAction(roundAction);

	QAction* horizontalAction = new QAction(
		QIcon(QDir::currentPath() + "/Images/HorizontalBrush.png"),
		tr("&BrushTool"),
		this);
	horizontalAction->setStatusTip(tr("&Brush Tool"));;
	connect(horizontalAction, &QAction::triggered, this, [&]() {
		emit horizontalChalkEnabled();
		});
	toolBar->addAction(horizontalAction);

	QDockWidget* detailDock = new QDockWidget(tr("Layers"), this);
	detailDock->setWidget(toolBar);
	addDockWidget(Qt::LeftDockWidgetArea, detailDock);

	splitDockWidget(generalDock, detailDock, Qt::Horizontal);

	//controlsList->setCurrentItem(controlsList->item(0));

	//connect(controlsList, &QListWidget::itemClicked,
	//	this, &BrushControlsWindow::onSettingClicked);




	//onLayerClicked(controlsList->item(0));
	//{
	//	int index = 1;

	//};
}


void BrushControlsWindow::onSettingClicked(QListWidgetItem* item)
{
	if (!item) return;
	int index = controlsList->row(item);
}