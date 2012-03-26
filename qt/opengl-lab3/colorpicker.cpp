#include "colorpicker.h"
#include "ui_colorpicker.h"

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);

    connect(ui->redSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setRed(int)));

    connect(ui->greenSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setGreen(int)));

    connect(ui->blueSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setBlue(int)));

    connect(this, SIGNAL(valueChanged(QColor)),
            ui->colorWidget, SLOT(setValue(QColor)));

    connect(ui->colorWidget, SIGNAL(valueChanged(QColor)),
            this, SLOT(setValue(QColor)));
}

ColorPicker::~ColorPicker()
{
    delete ui;
}

void ColorPicker::setValue(const QColor &newColor)
{
    if (newColor != color)
    {
        color = newColor;
        ui->redSlider->setValue(newColor.red());
        ui->greenSlider->setValue(newColor.green());
        ui->blueSlider->setValue(newColor.blue());
        emit valueChanged(newColor);
    }
}

void ColorPicker::setRed(int red)
{
    if (red != color.red())
    {
        color.setRed(red);
        emit valueChanged(color);
    }
}

void ColorPicker::setGreen(int green)
{
    if (green != color.red())
    {
        color.setGreen(green);
        emit valueChanged(color);
    }
}

void ColorPicker::setBlue(int blue)
{
    if (blue != color.blue())
    {
        color.setBlue(blue);
        emit valueChanged(color);
    }
}

