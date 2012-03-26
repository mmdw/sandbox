#include <QDebug>
#include <QMouseEvent>

#include <QTimer>
#include "glwindow.h"

#include <cmath>
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923

#include <GL/GLU.h>
#include "glut.h"

GLWindow::GLWindow(QWidget *parent) :
    QGLWidget(parent),
    mousex(0),
    mousey(0),
    posx(0),
    posy(1),
    posz(10),
    pitch(0),
    yaw(0)
{
    for (int i = 0; i < sizeof(keys); ++i)
        keys[i] = false;

    setFocusPolicy(Qt::ClickFocus);


    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(1000/60);
}

void GLWindow::moveLight()
{
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void GLWindow::initializeGL ()
{
    glEnable(GL_DEPTH_TEST);
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void GLWindow::paintGL()
{
    move();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(45, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
            0.0, 0.0, 0.0,
            sin(yaw) * cos(pitch), - sin(pitch), - cos(yaw) * cos(pitch),
            sin(yaw) * sin(pitch),   cos(pitch), - cos(yaw) * sin(pitch)
    );

    glTranslatef(-posx, -posy, -posz);

    moveLight();
    drawGrid();

    glPushMatrix();
    glScalef(1.0, 2.0,1.0);
    glTranslatef(0.0, 0.75, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWindow::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble fH = tan( fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar );
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = mousex - event->x();
    int dy = mousey - event->y();

    mousex = event->x();
    mousey = event->y();

    yaw   -= dx / 300.0;
    pitch -= dy / 300.0;

    if (pitch > M_PI_2)
        pitch = M_PI_2;

    if (pitch < - M_PI_2)
        pitch = - M_PI_2;

    if (yaw > M_PI * 2)
        yaw -= M_PI * 2;
    else
    if (yaw < 0)
        yaw += M_PI * 2;
}

void GLWindow::mousePressEvent(QMouseEvent *event)
{
    mousex = event->x();
    mousey = event->y();
}

void GLWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void GLWindow::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
}

void GLWindow::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
}

void GLWindow::move()
{
    const float moveStep = 0.1;

    if (keys[Qt::Key_W]) {
        posz -= moveStep * cos(yaw) * cos(pitch);
        posx += moveStep * sin(yaw) * cos(pitch);
        posy -= moveStep * sin(pitch);
    }

    if (keys[Qt::Key_S]) {
        posz += moveStep * cos(yaw) * cos(pitch);
        posx -= moveStep * sin(yaw) * cos(pitch);
        posy += moveStep * sin(pitch);
    }

    if (keys[Qt::Key_A]) {
        posz -= moveStep * sin(yaw);
        posx -= moveStep * cos(yaw);
    }

    if (keys[Qt::Key_D]) {
        posz += moveStep * sin(yaw);
        posx += moveStep * cos(yaw);
    }
}

void GLWindow::drawGrid()
{
    glPushAttrib(GL_COLOR | GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (int i = -5; i <= 5; ++i)
    {
        glVertex3f(i, 0.0, -5.0);
        glVertex3f(i, 0.0,  5.0);
        glVertex3f(-5.0, 0.0, i);
        glVertex3f( 5.0, 0.0, i);
    }
    glEnd();
    glPopAttrib();
}

void GLWindow::setAmbient(const QColor &ambient)
{
    GLfloat mat_ambient[] = {
        ambient.redF(),
        ambient.greenF(),
        ambient.blueF(), 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
}

void GLWindow::setSpecular(const QColor &specular)
{
    GLfloat mat_specular[] = {
        specular.redF(),
        specular.greenF(),
        specular.blueF(), 1.0 };

    glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
}

void GLWindow::setDiffuse(const QColor &diffuse)
{
    GLfloat mat_diffuse[] = {
        diffuse.redF(),
        diffuse.greenF(),
        diffuse.blueF(), 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
}

void GLWindow::setMaterialDiffuse(const QColor &diffuse)
{
    GLfloat mat_diffuse[] = {
        diffuse.redF(),
        diffuse.greenF(),
        diffuse.blueF(), 1.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

void GLWindow::setMaterialSpecular(const QColor &specular)
{
    GLfloat mat_specular[] = {
        specular.redF(),
        specular.greenF(),
        specular.blueF(), 1.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
}

void GLWindow::setMaterialAmbient(const QColor &ambient)
{
    GLfloat mat_ambient[] = {
        ambient.redF(),
        ambient.greenF(),
        ambient.blueF(), 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
}

void GLWindow::setShininess(const double shininess)
{
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
