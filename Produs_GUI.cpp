#include "Produs_GUI.h"
#include "Produs.h"
#include "Cos_GUI.h"
#include <QtWidgets/QHBoxLayout>
#include "cos_read_gui.h"
#include "cos_crud_gui.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QRadioButton>
#include <qpalette.h>
#include <qbrush.h>
#include<qdebug.h>
#include <qdialog.h>
#include <string>
#include <algorithm>
#include "Cos_GUI.h"

void Produs_GUI::init_GUI()
{
	setLayout(lyMain); //un box orizontal in caseta mare principala care e goala

	//adaug lista si sub doua butoane de sort

	tabel->setModel(model);

	QWidget* widDreapta = new QWidget; // o caseta 
	QVBoxLayout* vl = new QVBoxLayout; //dispusa vertical
	widDreapta->setLayout(vl); //conectez widgetul cu layoutul in care asez elem

	//aici tabel din lista
	//tabel->setColumnCount(4);
	//vl->addWidget(tabel);

	vl->addWidget(tabel);
	auto formLayout = new QFormLayout{};
	QStringList denumire;
	denumire.append(QString::fromStdString("Nume"));
	denumire.append(QString::fromStdString("Tip"));
	denumire.append(QString::fromStdString("Pret"));
	denumire.append(QString::fromStdString("Producator"));

	//tabel->setHorizontalHeaderLabels(denumire); 

	//lst = new QListWidget; //creez o lista de produse
	//vl->addWidget(lst); //adaug lista in layout

	QWidget* widBtnDreapta = new QWidget;  //un nou widget
	QHBoxLayout* lyBtnsDr = new QHBoxLayout; //un layout orizontal
	widBtnDreapta->setLayout(lyBtnsDr); //conectez widget cu layout

	//butoane pentru sortari le adaug in widget widBtnDreapta
	btnSortByPrice = new QPushButton("Sortare dupa pret");
	lyBtnsDr->addWidget(btnSortByPrice);

	btnSortByName = new QPushButton("Sortare dupa nume");
	lyBtnsDr->addWidget(btnSortByName);

	btnSortByName_Type = new QPushButton("Sortare dupa nume si tip");
	lyBtnsDr->addWidget(btnSortByName_Type);

	QWidget* widBtnFiltrari = new QWidget;  //un nou widget 
	QHBoxLayout* lyBtnsFiltrari = new QHBoxLayout; //un layout orizontal
	widBtnFiltrari->setLayout(lyBtnsFiltrari); //conectez widget cu layout

	btnFilterByName = new QPushButton("Filtrare dupa nume");
	lyBtnsFiltrari->addWidget(btnFilterByName);

	btnFilterByPrice = new QPushButton("Filtrare dupa pret");
	lyBtnsFiltrari->addWidget(btnFilterByPrice);

	btnFilterByProducer = new QPushButton("Filtrare dupa producator");
	lyBtnsFiltrari->addWidget(btnFilterByProducer);


	vl->addWidget(widBtnDreapta); //adaug butoanele in partea dreapta sub lista de prod
	vl->addWidget(widBtnFiltrari);
	lyMain->addWidget(widDreapta); //adaug partea dreapta in widgetul principal

	//fac un form pentru detalii
	QWidget* dr = new QWidget;
	QVBoxLayout* lydr = new QVBoxLayout; //un layout orizontal
	dr->setLayout(lydr);
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtNume = new QLineEdit;
	formLDetalii->addRow(new QLabel("Nume:"), txtNume);
	txtTip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), txtTip);
	txtPret = new QLineEdit;
	formLDetalii->addRow(new QLabel("Pret:"), txtPret);
	txtProducator = new QLineEdit;
	formLDetalii->addRow(new QLabel("Producator:"), txtProducator);


	btnAdd = new QPushButton("Adauga produs");
	btnDelete = new QPushButton("Sterge produs");
	btnUndo = new QPushButton("Undo");
	btnFind = new QPushButton("Cauta produs");
	btnModif = new QPushButton("Modifica");

	QWidget* coss = new QWidget;
	QFormLayout* lycoss = new QFormLayout;
	coss->setLayout(lycoss);

	butonCartCrud = new QPushButton{ "Cos nou:" };
	butonCartRead = new QPushButton{ "Cos READ" };
	btnaddcos = new QPushButton("Adauga in cos");
	btnrandcos = new QPushButton("Cos random");

	lycoss->addWidget(butonCartCrud);
	lycoss->addWidget(butonCartRead);
	lycoss->addWidget(btnaddcos);
	lycoss->addWidget(btnrandcos);


	formLDetalii->addWidget(btnAdd);
	formLDetalii->addWidget(btnFind);
	formLDetalii->addWidget(btnModif);
	formLDetalii->addWidget(btnDelete);
	formLDetalii->addWidget(btnUndo);

	lydr->addWidget(widDetalii);
	lydr->addWidget(coss);
	lyMain->addWidget(dr);


	btnDyn->setLayout(lyBtnDy);
	lyMain->addWidget(btnDyn);

}

void Produs_GUI::connectSignalsSlots()
{
	QObject::connect(btnaddcos, &QPushButton::clicked, [&]()
		{
			try {
				Produs p = srv.find_prod(txtNume->text().toStdString(), txtProducator->text().toStdString());
				cart.adauga(p);
				cart.notify();

			}
			catch (RepositoryException& ex)
			{
				QMessageBox::warning(this, "Avertizare", QString::fromStdString(ex.getMsg()));
			}
		});
	QObject::connect(butonCartCrud, &QPushButton::clicked, [&]() { GUIopencartCrud(); });

	QObject::connect(butonCartRead, &QPushButton::clicked, [&]() { GUIopencartRead(); });

	QObject::connect(btnrandcos, &QPushButton::clicked, [&]() {

		cosGUI->show();
		srv.genereaza_random_Cos(5);


		});

	//cand se emite semnalul clicked de pe buton reincarc lista
	//sortari
	QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {
		//qDebug() << "am ajuns aici!!!";
		//reloadList(srv.sortare_pret());
		reloadTable(srv.sortare_pret());
		});

	QObject::connect(btnSortByName, &QPushButton::clicked, [&]() {
		//reloadList(srv.sortare_nume());
		reloadTable(srv.sortare_nume());
		});

	QObject::connect(btnSortByName_Type, &QPushButton::clicked, [&]() {
		//reloadList(srv.sortare_nume_tip());
		reloadTable(srv.sortare_nume_tip());
		});


	QObject::connect(btnAdd, &QPushButton::clicked, this, &Produs_GUI::addProduct);

	QObject::connect(btnDelete, &QPushButton::clicked, this, &Produs_GUI::Delete);

	QObject::connect(btnUndo, &QPushButton::clicked, this, &Produs_GUI::Undo);

	QObject::connect(btnFind, &QPushButton::clicked, this, &Produs_GUI::findProduct);

	QObject::connect(btnModif, &QPushButton::clicked, this, &Produs_GUI::modifProduct);

	QObject::connect(btnFilterByName, &QPushButton::clicked, [&]() {

		auto fereastra_noua = new QWidget;
		fereastra_noua->setObjectName("Filtrare");
		fereastra_noua->show();

		QVBoxLayout* lyy = new QVBoxLayout;
		fereastra_noua->setLayout(lyy);

		QLabel* lbl = new QLabel{ "Lista produselor filtrate dupa nume este: " };


		lyy->addWidget(lbl);
		lyy->addWidget(lista_filtrare);

		auto nume = txtNume->text();
		reloadListFiltrare(srv.filtrare_nume(nume.toStdString()));
		}
	);
	QObject::connect(btnFilterByPrice, &QPushButton::clicked, [&]() {

		auto fereastra_noua = new QWidget;
		fereastra_noua->setObjectName("Filtrare");
		fereastra_noua->show();

		QVBoxLayout* lyy = new QVBoxLayout;
		fereastra_noua->setLayout(lyy);

		QLabel* lbl = new QLabel{ "Lista produselor filtrate dupa nume este: " };

		lyy->addWidget(lbl);
		lyy->addWidget(lista_filtrare);

		auto pret = txtPret->text();
		reloadListFiltrare(srv.filtrare_pret(pret.toInt()));
		}
	);
	QObject::connect(btnFilterByProducer, &QPushButton::clicked, [&]() {

		auto fereastra_noua = new QWidget;
		fereastra_noua->setObjectName("Filtrare");
		fereastra_noua->show();

		QVBoxLayout* lyy = new QVBoxLayout;
		fereastra_noua->setLayout(lyy);

		QLabel* lbl = new QLabel{ "Lista produselor filtrate dupa nume este: " };


		lyy->addWidget(lbl);
		lyy->addWidget(lista_filtrare);

		auto producator = txtProducator->text();
		reloadListFiltrare(srv.filtrare_producator(producator.toStdString()));
		}
	);

	QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (tabel->selectionModel()->selectedIndexes().isEmpty()) {
			txtNume->setText("");
			txtTip->setText("");
			txtPret->setText("");
			txtProducator->setText("");
			return;
		}

		int selected_row = tabel->selectionModel()->selectedIndexes().at(0).row();
		auto first_cel = tabel->model()->index(selected_row, 0);
		auto second_cel = tabel->model()->index(selected_row, 1);

		auto name = tabel->model()->data(first_cel, Qt::DisplayRole).toString();
		auto producer = tabel->model()->data(second_cel, Qt::DisplayRole).toString();

		txtNume->setText(name);
		txtProducator->setText(producer);
		auto produs = srv.find_prod(name.toStdString(), producer.toStdString());
		txtPret->setText(QString::number(produs.get_pret()));
		txtTip->setText(QString::fromStdString(produs.get_tip()));
		/*
		if (tabel->selectedItems().isEmpty()) {
			txtNume->setText("");
			txtTip->setText("");
			txtPret->setText("");
			txtProducator->setText("");
			return;
		}

		auto selectedRow = tabel->selectedItems().at(0)->row();
		auto nume = tabel->item(selectedRow, 0)->text();
		auto tip = tabel->item(selectedRow, 1)->text();
		auto pret = tabel->item(selectedRow, 2)->text();
		auto producator = tabel->item(selectedRow, 3)->text();

		txtNume->setText(nume);
		txtTip->setText(tip);
		txtPret->setText(pret);
		txtProducator->setText(producator);
		*/
		});

	/*
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty())
		{
			txtNume->setText("");
			txtTip->setText("");
			txtPret->setText("");
			txtProducator->setText("");
		}

		else {

			auto item_selected = sel.at(0);
			auto name = item_selected->text();
			auto producer = item_selected->data(Qt::UserRole).toString();

			txtNume->setText(name);
			txtProducator->setText(producer);
			auto produs = srv.find_prod(name.toStdString(), producer.toStdString());

			txtPret->setText(QString::number(produs.get_pret()));
			txtTip->setText(QString::fromStdString(produs.get_tip()));
		}
		});
	*/
}

void Produs_GUI::reloadListFiltrare(const std::vector<Produs>& prod)
{
	lista_filtrare->clear(); //curatam widgetul lst, ca sa actualizam lista de carti


	for (const auto& c : prod)
	{
		QListWidgetItem* rand = new QListWidgetItem();

		// create a new widget to hold the items in the row
		QWidget* rowWidget = new QWidget();
		QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);

		QLabel* item1 = new QLabel(QString::fromStdString(c.get_nume()));
		QLabel* item2 = new QLabel(QString::fromStdString(c.get_producator()));

		rowLayout->addWidget(item1);
		rowLayout->addWidget(item2);


		// set the size hint for the row
		rand->setSizeHint(QSize(rowWidget->sizeHint().width() + 4, rowWidget->sizeHint().height()));

		// add the row and items to the list widget
		lista_filtrare->addItem(rand);
		lista_filtrare->setItemWidget(rand, rowWidget);

	}
}

void Produs_GUI::reloadTable(const std::vector<Produs>& prod)
{
	model->setProduct(prod);
	/*
	tabel->clear();
	int i = 0;
	tabel->setRowCount(prod.size());
	//QMessageBox::information(nullptr, "avertisment", QString::number (prod.size()));
	for (const auto& p : prod)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()));
		item->setData(Qt::UserRole, QString::fromStdString(p.get_producator()));
		//tabel->insertRow(tabel->rowCount());
		tabel->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_nume())));
		tabel->setItem(i , 1, new QTableWidgetItem(QString::fromStdString(p.get_tip())));
		tabel->setItem(i, 2, new QTableWidgetItem(QString::number(p.get_pret())));
		tabel->setItem(i , 3, new QTableWidgetItem(QString::fromStdString(p.get_producator())));
		i++;
	}*/

}
void Produs_GUI::reloadList(const std::vector<Produs>& prod)
{
	model->setProduct(prod);
	/*
	lst->clear();
	for (const auto& p : prod)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()));
		item->setData(Qt::UserRole, QString::fromStdString(p.get_producator()));
		lst->addItem(item);

	}*/
}
void Produs_GUI::modifProduct()
{
	try {
		srv.modifica_produs(txtNume->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toInt(), txtProducator->text().toStdString());
		//reloadList(srv.getAll());
		reloadTable(srv.getAll());
		gui_addTip();
		txtNume->clear();
		txtTip->clear();
		txtPret->clear();
		txtProducator->clear();
	}
	catch (RepositoryException& ex)
	{
		QMessageBox::warning(this, "Avertizare", QString::fromStdString(ex.getMsg()));
	}
	catch (validateException& mesaje)
	{
		auto m = mesaje.getMsgs();
		for (const auto& er : m)
		{
			QMessageBox::warning(this, "Avertizare", QString::fromStdString(er));
		}

	}

}
void Produs_GUI::findProduct()
{
	try {
		//auto selectie = lst->selectedItems();
		//auto item_selected = selectie.at(0);
		//auto name = item_selected->text();
		//auto producer = item_selected->data(Qt::UserRole).toString();
		auto produs = srv.find_prod(txtNume->text().toStdString(), txtProducator->text().toStdString());
		txtPret->setText(QString::number(produs.get_pret()));
		txtTip->setText(QString::fromStdString(produs.get_tip()));
	}
	catch (RepositoryException& ex)
	{
		QMessageBox::warning(this, "Avertizare", QString::fromStdString(ex.getMsg()));
	}

}
void Produs_GUI::Undo()
{
	try {
		srv.undo();
		//reloadList(srv.getAll());
		reloadTable(srv.getAll());
		gui_addTip();
	}
	catch (RepositoryException& ex) {
		QMessageBox::warning(this, "Avertizare", "Nu se mai poate realiza undo!!");
	}
}
void Produs_GUI::Delete()
{
	try {
		srv.sterge_produs(txtNume->text().toStdString(), txtProducator->text().toStdString());
		//reloadList(srv.getAll());
		reloadTable(srv.getAll());
		gui_addTip();

	}
	catch (RepositoryException& ex)
	{
		QMessageBox::warning(this, "Avertizare", QString::fromStdString(ex.getMsg()));
	}
}
void Produs_GUI::addProduct()
{
	try {
		srv.adauga_produs(txtNume->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toInt(), txtProducator->text().toStdString());
		//reloadList(srv.getAll());
		reloadTable(srv.getAll());
		gui_addTip();

		txtNume->clear();
		txtTip->clear();
		txtPret->clear();
		txtProducator->clear();
	}
	catch (RepositoryException& ex)
	{
		QMessageBox::warning(this, "Avertizare", QString::fromStdString(ex.getMsg()));
	}
	catch (validateException& mesaje)
	{
		auto m = mesaje.getMsgs();
		for (const auto& er : m)
		{
			QMessageBox::warning(this, "Avertizare", QString::fromStdString(er));
		}

	}
}
void Produs_GUI::add_auto()
{
	Produs p1{ "apa","plata",5,"dorna" };
	Produs p2{ "telefon","smartphone",3000,"Samsung" };
	Produs p3{ "ciocolata","vanilie",15,"Milka" };
	srv.adauga_produs(p1.get_nume(), p1.get_tip(), p1.get_pret(), p1.get_producator());
	reloadTable(srv.getAll());
	//reloadList(srv.getAll());
	gui_addTip();
	srv.adauga_produs(p2.get_nume(), p2.get_tip(), p2.get_pret(), p2.get_producator());
	reloadTable(srv.getAll());
	gui_addTip();
	srv.adauga_produs(p3.get_nume(), p3.get_tip(), p3.get_pret(), p3.get_producator());
	//srv.adauga_produs(txtNume->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toInt(), txtProducator->text().toStdString());
	//reloadList(srv.getAll()); 
	reloadTable(srv.getAll());
	gui_addTip();
}
void Produs_GUI::gui_addTip()
{
	vector<Produs> lista = srv.getAll();
	vector<std::pair<string, int>> tipuri;
	for (auto p : lista)
	{
		bool ok = false;
		int i = 0;
		for (auto t : tipuri) {
			if (t.first == p.get_tip())
			{
				ok = true;
				break;
			}
		}
		if (ok == true)
			tipuri[i].second++;
		else tipuri.emplace_back(p.get_tip(), 1);
	}
	QLayoutItem* item;
	while ((item = lyBtnDy->takeAt(0)) != NULL)
	{
		delete item->widget();
		delete item;
	}

	for (auto t : tipuri) {
		string tip = t.first;
		int nr = t.second;
		auto item = new QRadioButton(QString::fromStdString(tip));

		QObject::connect(item, &QRadioButton::clicked, [nr] {
			string n = std::to_string(nr);
			auto* lbl = new QLabel(QString::fromStdString(n));
			lbl->show();
			});
		lyBtnDy->addWidget(item);
	}
}
void Produs_GUI::GUIopencartCrud()
{
	auto* newWindow = new CartCRUDGUI{ srv,cart };
	newWindow->run();
}
void Produs_GUI::GUIopencartRead()
{

	auto* newWindow = new CartCRUDRead{ cart };
	newWindow->show();
}