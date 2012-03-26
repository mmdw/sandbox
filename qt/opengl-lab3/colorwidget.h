#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

class QColorDialog;
class QColor;

class ColorWidget : public QWidget
{
    Q_OBJECT

    QColor color;

public:
    explicit ColorWidget(QWidget *parent = 0);
    
signals:
    void valueChanged(const QColor& newColor);
    QColor value() const;

public slots:
    void mouseDoubleClickEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);
    void setValue(const QColor& value);
};

#endif // COLORWIDGET_H
