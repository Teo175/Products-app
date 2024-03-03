#pragma once
#pragma once
#pragma once
#pragma once
#include <QTableWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h> //pt forme de tip eticheta+camp
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <vector>
#include <string>
#include "Service.h"
#include "Cos_GUI.h"
#include "custom_model.h"


using namespace std;
class Produs_GUI : public QWidget
{
public:
    Produs_GUI(Service& srv, Cos& cart) :srv{ srv }, cart{ cart }
    { //constructorul
     //e ca un fel de UI Produs_GUI(serv)
        reloadTable(srv.getAll());
        init_GUI(); //pt design
        connectSignalsSlots();
    }
    void add_auto();

private:
    Service& srv;
    Cos& cart;

    QListWidget* filter_layout = new QListWidget;
    QTableView* tabel = new QTableView;
    CustomTableModel* model = new CustomTableModel{ srv.getAll()};

    QHBoxLayout* lyMain = new QHBoxLayout; //un box orizontal in care imi pun widgeturile
    //butoanele
    QPushButton* btnSortByPrice;
    QPushButton* btnSortByName;
    QPushButton* btnSortByName_Type;
    QPushButton* btnFilterByName;
    QPushButton* btnFilterByPrice;
    QPushButton* btnFilterByProducer;
    QPushButton* btnModif;
    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnUndo;
    QPushButton* btnFind;
    QPushButton* btnaddcos;
    QPushButton* btnrandcos;

    //QListWidget* lst = new QListWidget;  //lista de produse
     //QTableWidget* tabel = new QTableWidget{}; //tabel de produse

     //campuri text
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;
    QLineEdit* txtProducator = new QLineEdit;


    QVBoxLayout* lyBtnDy = new QVBoxLayout; //un nou box vertical pentru butoane
    QWidget* btnDyn = new QWidget; //o casuta unde vor fi dispuse butoanele


    QListWidget* lista_filtrare = new QListWidget;

    CosGUI* cosGUI = new CosGUI{ srv };

    QPushButton* butonCartCrud;
    QPushButton* butonCartRead;

    void reloadList(const std::vector<Produs>& prod);
    void reloadListFiltrare(const std::vector<Produs>& prod);
    void addProduct();
    void Delete();
    void Undo();
    void findProduct();
    void modifProduct();
    // void adaugaButoane(const std::vector<Produs>& prod);


    void gui_addTip();
    void reloadTable(const std::vector<Produs>& prod);
    void init_GUI();
    void connectSignalsSlots();

    void GUIopencartCrud();
    void GUIopencartRead();

};