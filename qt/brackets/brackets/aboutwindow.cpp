#include "StdAfx.h"
#include "aboutwindow.h"

#include <QtGui>

AboutWindow::AboutWindow(QWidget* parent)
{
    vlayout  = new QVBoxLayout;
	textEdit = new QTextBrowser;

	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

	QPalette pal = palette();

	pal.setBrush(QPalette::Base, pal.window());
	
	textEdit->setPalette(pal);
	textEdit->setReadOnly(true);	

	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");		
	textEdit->setHtml(
		"<h2 align = center>" + codec->toUnicode("Скобки") + "</h2>"
		"<br>" + codec->toUnicode("Программа является дополнением к ИДЗ-2 по МЛиТА") + 
		"<br><a href = \"http://sites.google.com/site/gr8373vladimir/\"><br>"+
         codec->toUnicode("Подробнее") + "</a>");
	
	setWindowTitle("about");

    textEdit->setReadOnly(true);	
	textEdit->setFrameStyle(QFrame::NoFrame);
	textEdit->setOpenLinks(true);
	textEdit->setOpenExternalLinks(true);   
    
	vlayout->addWidget(textEdit);
	setLayout(vlayout);  
    setModal(true);   
	setFixedSize(250,150);
}

void AboutWindow::anchorClicked(QUrl url)
{
    QDesktopServices::openUrl(url);
}