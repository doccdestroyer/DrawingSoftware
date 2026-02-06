#include <UndoManager.h>
#include <LayerManager.h>

UndoManager::UndoManager(QWidget* parent)
    : QWidget(parent)
{
    layerManager = new LayerManager(this);

    selectionOverlay = layerManager->selectionOverlay;

    layers = layerManager->layers;
    undoLayerStack.push(layers);

    undoSelectionStack.push(selectionOverlay);
}

void UndoManager::pushUndo(const QVector<QImage>& layers)
{
    undoLayerStack.push(layers);
    if (undoLayerStack.size() > 50) undoLayerStack.remove(0);

    undoSelectionStack.push(selectionOverlay);
    if (undoSelectionStack.size() > 50) undoSelectionStack.remove(0);
}

void UndoManager::undo()
{
    if (undoLayerStack.size() <= 1) return;
    if (undoSelectionStack.size() <= 1) return;

    redoLayerStack.push(undoLayerStack.pop());
    layers = undoLayerStack.top();
    layerManager->layers = layers;

    redoSelectionStack.push(undoSelectionStack.pop());
    selectionOverlay = undoSelectionStack.top();
    layerManager->selectionOverlay = selectionOverlay;
    //layerManager->undo();
    update();
}

void UndoManager::redo()
{
    if (redoLayerStack.isEmpty()) return;
    if (redoSelectionStack.isEmpty()) return;

    layers = redoLayerStack.pop();
    undoLayerStack.push(layers);
    layerManager->layers = layers;

    selectionOverlay = redoSelectionStack.pop();
    undoSelectionStack.push(selectionOverlay);
    layerManager->selectionOverlay = selectionOverlay;
    //layerManager->redo();
    update();
}


