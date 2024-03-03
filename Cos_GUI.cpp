#include "Cos_GUI.h"
#include <qtimer.h>

void CosGUI::initGUIcmps()
{
	setLayout(mainLayout);
	mainLayout->addWidget(prodWidget);
	mainLayout->addWidget(btngolireCos);
}

void CosGUI::connectSignalsSlots()
{
	QObject::connect(btngolireCos, &QPushButton::clicked, this, &CosGUI::golire);
	QTimer* refreshTimer = new QTimer;
	QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
		reloadList(srv.getAllCos());
		});

	refreshTimer->start(1000);


}
void CosGUI::golire()
{
	srv.goleste_cos();
	reloadList(srv.getAllCos());
}
void CosGUI::reloadList(const vector<Produs>& prod)
{
	prodWidget->clear();
	for (const auto& p : prod)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()));
		item->setData(Qt::UserRole, QString::fromStdString(p.get_tip()));
		if (p.get_pret() > 100)
		{
			item->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
		}
		prodWidget->addItem(item);

	}
}