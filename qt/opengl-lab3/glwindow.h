#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>

class QColor;
class GLWindow : public QGLWidget
{
    Q_OBJECT

    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

    float mousex;
    float mousey;

    float posx, posy, posz;
    float pitch, yaw;

    bool keys[256];

    void move();
    void drawGrid();
    void moveLight();

public:
    explicit GLWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void setAmbient(const QColor& ambient);
    void setDiffuse(const QColor& diffuse);
    void setSpecular(const QColor& specular);

    void setMaterialAmbient(const QColor& ambient);
    void setMaterialDiffuse(const QColor& diffuse);
    void setMaterialSpecular(const QColor& specular);

    void setShininess(const double shininess);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
};

#endif // GLWINDOW_H
