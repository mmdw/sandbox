#ifndef BRACKETS_H
#define BRACKETS_H

#include <QtGui>
#include <string>
#include "aboutwindow.h"

class brackets : public QMainWindow
{
	Q_OBJECT

 private:
    QTextEdit* textEdit;
    QLineEdit* textLine;
    QPushButton* button;
    QHBoxLayout* hlayout;
    QVBoxLayout* vlayout;    

    QMenu* aboutMenu;
//  QMenu* fileMenu;

    QAction* aboutAct;
    QAction* exitAct;

    QWidget* centralWidget;

    AboutWindow* aboutWindow;
    int count;

	QString decode(const std::string&);
	QString decode(const char* istr);

 void createMenu();
 void createActions();

 private slots:
    void run();
    void about();
    void exit();


public:
	brackets(QWidget *parent = 0, Qt::WFlags flags = 0);
	~brackets() {}

};

#endif // BRACKETS_H
