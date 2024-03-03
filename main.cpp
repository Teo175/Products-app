#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h> //pt forme de tip eticheta+camp
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <vector>
#include <string>
#include "Produs_GUI.h"
#include "Cos_GUI.h"
#include "Service.h"
#include "UI.h"
using std::vector;
using std::string;


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Repo rep; //RepoLab rep{ 0.5 };
    ProdusValidator val;
    Cos cos;
    Service serv{ rep,val,cos };
    Console console{ serv };
    //  console.start();


    Produs_GUI p{ serv ,cos };
    p.add_auto();
    p.show();

    return a.exec();
}
