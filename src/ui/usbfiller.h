#ifndef USBFILLER_H
#define USBFILLER_H

#include <QtWidgets/QWidget>
#include "ui_usbfiller.h"

class UsbFiller : public QWidget
{
	Q_OBJECT

public:
	UsbFiller(QWidget *parent = 0);
	~UsbFiller();

private:
	Ui::UsbFiller ui;
};

#endif // USBFILLER_H
