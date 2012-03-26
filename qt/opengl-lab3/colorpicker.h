#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>

class QColor;

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QWidget
{
    Q_OBJECT

    QColor color;
    
public:
    explicit ColorPicker(QWidget *parent = 0);
    ~ColorPicker();

signals:
    void valueChanged(const QColor& newColor);
    QColor value() const;

public slots:
    void setValue(const QColor& newColor);
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    
private:
    Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H
