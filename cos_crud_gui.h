#pragma once
#pragma once
#pragma once
#include "Observer.h"
#include "service.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qdialog.h>
#include <QTableWidget>
#include <QListWidget>
#include <qfont.h>
#include <qmessagebox.h>
#include <qlabel>
#include <vector>
#include <QListView>
#include <QStandardItemModel>
#include "custom_model.h"

class CartCRUDGUI : public QWidget, public Observer {

private:

	Service& serv;
	Cos& cart_serv;

	QHBoxLayout* layout = new QHBoxLayout{};
	QWidget* wnd = new QWidget;
	QPushButton* butonCartDelete = new QPushButton{ "&Goleste cos" };
	QPushButton* butonCartGenerate = new QPushButton{ "&Genereaza cos" };
	QListWidget* cart_list = new QListWidget;

	CustomTableModel* model = new CustomTableModel{ cart_serv.get_cos() };
	QListView* lista = new QListView;


	void create_interface();

	void load_data();

	void connect();

	void GUIdeleteCart();

	void GUIgenerateCart();

public:

	explicit CartCRUDGUI(Service& serv, Cos& cart_serv) : serv{ serv }, cart_serv{ cart_serv } {}

	void run();

	void update() override;

	~CartCRUDGUI() {
		this->cart_serv.removeObserver(this);
	}
};

