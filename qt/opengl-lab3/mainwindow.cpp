#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->ambientWidget, SIGNAL(valueChanged(QColor)),
            ui->glwindow, SLOT(setAmbient(QColor)));
    connect(ui->diffuseWidget, SIGNAL(valueChanged(QColor)),
            ui->glwindow, SLOT(setDiffuse(QColor)));
    connect(ui->specularWidget, SIGNAL(valueChanged(QColor)),
            ui->glwindow, SLOT(setSpecular(QColor)));

    connect(ui->materialAmbient, SIGNAL(valueChanged(QColor)),
            ui->glwindow, SLOT(setMaterialAmbient(QColor)));
    connect(ui->materialDiffuse, SIGNAL(valueChanged(QColor)),
            ui->glwindow, SLOT(setMaterialDiffuse(QColor)));
    connect(ui->materialSpecular, SIGNAL(valueChanged(QColor)),
            ui->glwindow, SLOT(setMaterialSpecular(QColor)));
//    connect(ui->shininess, SIGNAL(valueChanged(double)),
//            ui->glwindow, SLOT(setShininess(double)));

    ui->ambientWidget->setValue(QColor(25, 25, 25));
    ui->diffuseWidget->setValue(QColor(255, 255, 255));
    ui->specularWidget->setValue(QColor(255, 255, 255));

    ui->materialAmbient->setValue(QColor(25, 25, 25));
    ui->materialDiffuse->setValue(QColor(255, 255, 255));
    ui->materialSpecular->setValue(QColor(255, 255, 255));
}

MainWindow::~MainWindow()
{
    delete ui;
}
