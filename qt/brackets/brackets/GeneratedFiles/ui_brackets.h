/********************************************************************************
** Form generated from reading UI file 'brackets.ui'
**
** Created: Sun 3. Jan 13:09:14 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRACKETS_H
#define UI_BRACKETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bracketsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *bracketsClass)
    {
        if (bracketsClass->objectName().isEmpty())
            bracketsClass->setObjectName(QString::fromUtf8("bracketsClass"));
        bracketsClass->resize(600, 400);
        menuBar = new QMenuBar(bracketsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        bracketsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(bracketsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        bracketsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(bracketsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        bracketsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(bracketsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        bracketsClass->setStatusBar(statusBar);

        retranslateUi(bracketsClass);

        QMetaObject::connectSlotsByName(bracketsClass);
    } // setupUi

    void retranslateUi(QMainWindow *bracketsClass)
    {
        bracketsClass->setWindowTitle(QApplication::translate("bracketsClass", "brackets", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class bracketsClass: public Ui_bracketsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRACKETS_H
