#include "stdafx.h"
#include "ui/usbfiller.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UsbFiller w;
	w.show();
	return a.exec();
}
