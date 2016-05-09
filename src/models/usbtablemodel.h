#pragma once
#include <QtCore/QAbstractTableModel>

class UsbTableModel : public QAbstractTableModel {
	Q_OBJECT

public:
	enum class Columns {
		Letter,
		Label,
		Status,
		Progress,
		Info
	};

	UsbTableModel(QObject * parent = Q_NULLPTR);
	~UsbTableModel();

private:
	
};