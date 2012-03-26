#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QtGui>

class AboutWindow: public QDialog
{
    Q_OBJECT

 private:
    QVBoxLayout* vlayout;
	QTextBrowser* textEdit;

 private slots:

 void anchorClicked(QUrl);

 public:
    AboutWindow (QWidget* parent = 0);
	~AboutWindow () {};
};

#endif // ABOUTWINDOW_H
