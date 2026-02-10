#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>
#include <QIcon>
#include <QDockWidget>
#include <QToolBar>

class BrushControlsWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit BrushControlsWindow(QMainWindow* parent = nullptr);

signals:
	void chalkEnabled();
	void horizontalChalkEnabled();
	void roundEnabled();
private:
	//QDockWidget* dock;
	QListWidget* controlsList = nullptr;
	void onSettingClicked(QListWidgetItem* item);

};