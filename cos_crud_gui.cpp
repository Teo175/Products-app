#include "cos_crud_gui.h"


void CartCRUDGUI::create_interface() {
    wnd->setLayout(layout);

    lista->setModel(model);
    layout->addWidget(lista);

    QVBoxLayout* btn = new QVBoxLayout{};
    btn->addWidget(butonCartDelete);
    btn->addWidget(butonCartGenerate);

    layout->addLayout(btn);
}

void CartCRUDGUI::load_data() {
    model->setProduct(cart_serv.get_cos());
    /*
    // model->setProduct(cart_serv.cart_get_all_service());

    vector <Produs> lista = cart_serv.get_cos();
    // map <int, int> frecventa = cart_serv.cart_get_frecventa_service();

    cart_list->clear();
    for (const auto& product : lista)
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(QString::fromStdString(product.get_nume()));
        item->setData(Qt::UserRole + 1, QString::fromStdString(product.get_producator()));
        cart_list->addItem(item);
    }*/
}

void CartCRUDGUI::connect() {

    QObject::connect(butonCartDelete, &QPushButton::clicked, [&]() { GUIdeleteCart(); });

    QObject::connect(butonCartGenerate, &QPushButton::clicked, [&]() { GUIgenerateCart(); });

}

void CartCRUDGUI::update() {

    load_data();
}

void CartCRUDGUI::run() {
    this->cart_serv.addObserver(this);

    create_interface();
    connect();
    update();
    wnd->show();
}

void CartCRUDGUI::GUIdeleteCart()
{
    cart_serv.goleste();
    cart_serv.notify();
}

void CartCRUDGUI::GUIgenerateCart()
{
    try
    {
        cart_serv.genereaza_cos(5, serv.getAll());
        cart_serv.notify();
    }
    catch (RepositoryException)
    {
        QMessageBox::information(nullptr, "Eroare!", "Nu exista produse pe care sa le puteti genera!");
    }
}