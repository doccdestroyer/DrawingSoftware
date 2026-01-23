/********************************************************************************
** Form generated from reading UI file 'DrawingSoftware.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWINGSOFTWARE_H
#define UI_DRAWINGSOFTWARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawingSoftwareClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DrawingSoftwareClass)
    {
        if (DrawingSoftwareClass->objectName().isEmpty())
            DrawingSoftwareClass->setObjectName("DrawingSoftwareClass");
        DrawingSoftwareClass->resize(600, 400);
        menuBar = new QMenuBar(DrawingSoftwareClass);
        menuBar->setObjectName("menuBar");
        DrawingSoftwareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DrawingSoftwareClass);
        mainToolBar->setObjectName("mainToolBar");
        DrawingSoftwareClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DrawingSoftwareClass);
        centralWidget->setObjectName("centralWidget");
        DrawingSoftwareClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DrawingSoftwareClass);
        statusBar->setObjectName("statusBar");
        DrawingSoftwareClass->setStatusBar(statusBar);

        retranslateUi(DrawingSoftwareClass);

        QMetaObject::connectSlotsByName(DrawingSoftwareClass);
    } // setupUi

    void retranslateUi(QMainWindow *DrawingSoftwareClass)
    {
        DrawingSoftwareClass->setWindowTitle(QCoreApplication::translate("DrawingSoftwareClass", "DrawingSoftware", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrawingSoftwareClass: public Ui_DrawingSoftwareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWINGSOFTWARE_H
