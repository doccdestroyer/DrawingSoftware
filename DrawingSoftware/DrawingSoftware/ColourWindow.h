#pragma once

#include <QWidget>
#include <QPainter>
#include <HueDial.h>
#include <QPainterPath>


class ColourWindow : public QWidget
{
public:

    ColourWindow(QWidget* parent = nullptr);

    int angle;
    int hueAngle();

    QColor updateColour() const;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void createWheel();
    void mousePressEvent(QMouseEvent* event) override;

    void paintEvent(QPaintEvent*) override;

private:
    HueDial* dial = new HueDial(this);
    QRectF windowArea;

};
