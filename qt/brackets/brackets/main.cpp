#include "stdafx.h"
#include "brackets.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	QApplication a(argc, argv);
	a.setStyle(new QPlastiqueStyle);
	brackets w;
	w.show();
	return a.exec();
}
