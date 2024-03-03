#pragma once
#pragma once
#pragma once
#include <QWidget.h>
#include "Cos.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QtWidgets/qpushbutton.h>
#include "Service.h"

class CosGUI : public QWidget {
private:
	Service& srv;
	void initGUIcmps();
	void connectSignalsSlots();
	void reloadList(const vector<Produs>& prod);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QListWidget* prodWidget = new QListWidget;
	QPushButton* btngolireCos = new QPushButton("Golire cos");


public:
	CosGUI(Service& srv) : srv{ srv }
	{
		initGUIcmps();
		connectSignalsSlots();
		reloadList(srv.getAllCos());
	}
	void golire();
};