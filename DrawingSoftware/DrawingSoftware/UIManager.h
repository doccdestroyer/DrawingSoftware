#pragma once
#pragma once

#include <ColourWindow.h>
#include <UndoManager.h>


class UIManager : public QWidget
{
    Q_OBJECT

public:
    explicit UIManager(QWidget* parent = nullptr);
    ColourWindow* colourWindow;
    UndoManager* undoManager;
};

