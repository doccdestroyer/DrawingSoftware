#pragma once

#include <QWidget>
#include <QListWidget>
#include <QStack>


class LayerManager : public QWidget
{
    Q_OBJECT

public:
    explicit LayerManager(QWidget* parent = nullptr);
    void addLayer(int destination, QString& name);
    void undo();
    void redo();
    void pushUndo();
    void updateList();
    void restore(const QStringList& state);
    QListWidget* layersList = nullptr;


signals:
    void layerSelected(const QString& layerName, int& index);
    void layerDeleted(int& index);
    void layerAdded(const int& index);

private slots:
    void onLayerClicked(QListWidgetItem* item);
    void onDeleteClicked();


private:
    QString layer;
    //QListWidget* layersList = nullptr;

    QStack<QListWidget*> undoStack;
    QStack<QListWidget*> redoStack;

    using LayerState = QStringList;

    QStack<LayerState> undoStack2;
    QStack<LayerState> redoStack2;

    bool changingStack;
};



