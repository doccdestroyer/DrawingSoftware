#include "LayerManager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <string>

// TODO MAKE A RENAMER


LayerManager::LayerManager(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Layers");
    resize(300, 600);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    layersList = new QListWidget(this);
    layersList->addItems({ "background", "Layer 1" });
    layersList->setSortingEnabled(true);



    auto* layout = new QVBoxLayout(this);

    QPushButton* newLayerButton = new QPushButton("New Layer", this);
    QPushButton* deleteLayerButtton = new QPushButton("Delete", this);


    layout->addWidget(layersList);
    layout->addWidget(newLayerButton);
    layout->addWidget(deleteLayerButtton);

    pushUndo();

    //undoStack.push(layersList);
    //redoStack.clear();

    layersList->setCurrentItem(layersList->item(1));


    onLayerClicked(layersList->item(1));
    {
        int index = 1;
        emit layerSelected(layersList->item(1)->text(), index);
    };
    connect(layersList, &QListWidget::itemClicked,
        this, &LayerManager::onLayerClicked);

    connect(newLayerButton, &QPushButton::clicked, this, [=]() {
        //int newIndex = layersList->count();
        int newIndex = layersList->row(layersList->currentItem()) + 1;
        QString name = QString("Layer %1").arg(newIndex);
        addLayer(newIndex, name);
        });

    //connect(newLayerButton, &QPushButton::clicked, this, [=]() {
    //    int newIndex;
    //    if (layersList->currentItem())
    //        newIndex = layersList->row(layersList->currentItem()) + 1;
    //    else
    //        newIndex = layersList->count(); 
    //    QString name = QString("Layer %1").arg(newIndex);
    //    addLayer(newIndex, name);
    //    });

    connect(deleteLayerButtton, &QPushButton::clicked,
        this, &LayerManager::onDeleteClicked);





    pngBackground = QImage(QDir::currentPath() + "/Images/PNGBackground.png");

    background = QImage(1100, 1100, QImage::Format_ARGB32_Premultiplied);
    image = background;
    image.fill(Qt::transparent);
    originalImage = image;
    background.fill(Qt::white);
    layers = { background, image };
    selectionOverlay = image; 


}

void LayerManager::updateLayers(QVector<QImage> newLayers, QImage newOverlay)
{
    layers = newLayers;
    selectionOverlay = newOverlay;
}

void LayerManager::addLayer(int destination, QString& name)
{
    //pushUndo();
    qDebug() << "SICK " << destination << "LAYERS COUNT: " << layersList->count();
    destination = qBound(0, destination, layersList->count());
    qDebug() << "    new destination: " << destination;


    for (int item = 0; item < layersList->count(); item++) {
        QListWidgetItem* currentItem = layersList->item(item);
        QString oldName = currentItem->text();

        QRegularExpression re("(\\d+)");
        QRegularExpressionMatch match = re.match(oldName);

        if (match.hasMatch()) {
            int num = match.captured(1).toInt();
            oldName.replace(re, QString::number(num + 1));
            name = oldName;
        }
    }
    emit layerAdded(destination);


    layersList->insertItem(destination, name);

    layersList->setCurrentItem(layersList->item(destination));



    pushUndo();
    update();
    qDebug() << layersList->count();

}

//void LayerManager::updateList()
//{
//    QListWidget* oldList = layersList;
//
//    qDebug() << oldList->count();
//    layersList->clear();
//    for (int layerIndex = 0; layerIndex < oldList->count(); layerIndex++) {
//        QString name = oldList->item(layerIndex)->text();
//        addLayer(layerIndex, name);
//        qDebug() << "Added" << name << " at " << layerIndex;
//    }
//
//}

void LayerManager::undo()
{
    //if (undoStack.size() <= 1) return;
    //redoStack.push(undoStack.pop());
    //layersList = undoStack.top();
    //updateList();
    //update();

    if (undoStack2.size() <= 1) return;
    changingStack = true;

    QStringList current;
    for (int i = 0; i < layersList->count(); ++i)
        current << layersList->item(i)->text();

    redoStack2.push(current);
    undoStack2.pop();
    restore(undoStack2.top());

}

void LayerManager::restore(const QStringList& state)
{
    layersList->clear();
    for (const QString& name : state)
        layersList->addItem(name);
}

void LayerManager::redo()
{
    if (redoStack2.isEmpty()) return;
    changingStack = true;

    QStringList current;
    for (int i = 0; i < layersList->count(); ++i)
        current << layersList->item(i)->text();

    undoStack2.push(current);
    restore(redoStack2.pop());
}
void LayerManager::pushUndo()
{
    QStringList state;
    for (int i = 0; i < layersList->count(); ++i)
        state << layersList->item(i)->text();

    undoStack2.push(state);
    redoStack2.clear();
    changingStack = false;
}
void LayerManager::onLayerClicked(QListWidgetItem* item)
{
    if (!item) return;
    layer = item->text();
    int index = layersList->row(item);
    emit layerSelected(layer, index);
}
void LayerManager::onDeleteClicked()
{
    int row = layersList->currentRow();
    if (layersList->count() < 1 || row < 0) return;

    QListWidgetItem* item = layersList->takeItem(row);
    delete item;
    pushUndo();

    if (layersList->count() == 1) {
        layersList->setCurrentRow(0);
        qDebug() << layer;
    }

    layersList->sortItems(Qt::AscendingOrder);
    int newNum = row - 1;
    if (newNum == -1) {
        newNum = 0;
    }
    //onLayerClicked(layersList->item(row - 1));

    //layersList->setCurrentItem(layersList->item(row - 1));


    emit layerDeleted(row);
    update();

    qDebug() << layersList->count();

}