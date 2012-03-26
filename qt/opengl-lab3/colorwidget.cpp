#include <QPaintEvent>
#include <QPainter>
#include <QColorDialog>

#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent), color(Qt::white)
{
}

void ColorWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), color);
    painter.end();
}


void ColorWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QColorDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        setValue(dialog.currentColor());
        this->repaint();
    }
}


void ColorWidget::setValue(const QColor &value)
{
    if (value != color)
    {
        color = value;
        repaint();
        emit valueChanged(value);
    }
}
