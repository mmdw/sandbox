#include "stdafx.h"
#include "brackets.h"
#include "HtmlBuilder.h"

#include <QTextCodec>

QTextCodec* codec = QTextCodec::codecForName("Windows-1251");	

brackets::brackets(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{	
    textEdit = new QTextEdit;
    textLine = new QLineEdit;
    hlayout  = new QHBoxLayout;
    vlayout  = new QVBoxLayout;
    button   = new QPushButton("Do");

    aboutWindow   = new AboutWindow(this);
    centralWidget = new QWidget;

    count = 0;

    button->setAutoDefault(true);

    textEdit->setReadOnly(true);
    textEdit->setFontFamily("Courier New");
    textEdit->setFontPointSize(13);
    textLine->setFont(QFont("Courier New", 15,15,false));

    hlayout->addWidget(textLine);
    hlayout->addWidget(button);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(textEdit);	

    connect(button, SIGNAL(clicked()),
            this, SLOT(run()));

    connect(textLine, SIGNAL(returnPressed()),
            button, SLOT(click()));

    createActions();
    createMenu();

    centralWidget->setLayout(vlayout);    
    setCentralWidget(centralWidget);	

	resize(800,400);	
	
	// !
	setFixedWidth(800);		
}

void brackets::about()
{
    aboutWindow->show();
}

void brackets::exit()
{
    this->close();
}

void brackets::createActions()
{
    exitAct  = new QAction("&Exit", this);
    aboutAct = new QAction(codec->toUnicode("О программе"), this);   

    connect(aboutAct, SIGNAL(triggered()),
            this, SLOT(about()));
	
    connect(exitAct, SIGNAL(triggered()),
            this, SLOT(exit()));
}

void brackets::createMenu()
{
//    fileMenu = this->menuBar()->addMenu("&File");
    this->menuBar()->addAction(aboutAct);

//    fileMenu->addAction(exitAct);
//    aboutMenu->addAction(aboutAct);
}


QString brackets::decode(const std::string& istr)
{	
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	return codec->toUnicode(istr.c_str());
}

QString brackets::decode(const char* istr)
{	
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	return codec->toUnicode(istr);
}

void brackets::run()
{	
	if (textLine->text().isEmpty())	return;

	textEdit->moveCursor(QTextCursor::End);		
	QString expr = textLine->text();

	HtmlBuilder hb(expr.toStdString());
	
	//			
	// std::ofstream ofs("out.html");
	// ofs << hb.getHtml();

	if (hb.isValid())
	{
		textEdit->insertHtml(
			"<table border = 1 cellpadding = 7 cellspacing = 0 width = 100%>"
                "<tr>"
				"<td height = 10 bgcolor = #D3EDF6><b>" + decode("Выражение: ") + "</b><tt>" + Qt::escape(expr) + "</tt></td>"
                "</tr>"
                "<tr>"
			    	 "<td>" + QString(hb.getHtml().c_str()) + "</td>"
			    "</tr>"
			"</table>");	
	}
	else
	{
		QString spaces;

		for (int j = 1; j < hb.get_err_pos();++j)
			spaces += "&nbsp;";

		textEdit->insertHtml(
			"<table border = 1 cellpadding = 7 cellspacing = 0 width = 100%>"
				"<tr>"
				"<td height = 10 bgcolor = #D3EDF6><b>" + decode("Выражение: ") + "</b><tt>" + Qt::escape(expr) + "</tt></td>"
				"</tr>"
				"<tr>"
					"<td>"
					"<tt>" +Qt::escape(expr) + "<br>" + spaces + "</tt><b>^</b><br>"
						"<b>" + decode("Ошибка: ")+ "</b>" + decode(hb.get_err_msg()) +									 
					"</td>"
				"</tr>"
			"</table><br>");
	}

	textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
	textEdit->insertHtml("<br>");
	textLine->clear();
}