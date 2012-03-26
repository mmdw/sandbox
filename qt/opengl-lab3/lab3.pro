#-------------------------------------------------
#
# Project created by QtCreator 2012-03-08T19:36:43
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = lab3
TEMPLATE = app

LIBS += glut32.lib
LIBS += -LG:\opt\glut-3.7.6-bin\

SOURCES += main.cpp\
        mainwindow.cpp \
    glwindow.cpp \
    colorwidget.cpp \
    colorpicker.cpp

HEADERS  += mainwindow.h \
    glwindow.h \
    colorwidget.h \
    colorpicker.h

INCLUDEPATH += G:\opt\glut-3.7.6-bin\

FORMS    += mainwindow.ui \
    colorpicker.ui

OTHER_FILES += \
    res/grass.png

RESOURCES +=
