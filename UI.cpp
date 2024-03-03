#pragma once
#include "Ui.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;

void Console::tipareste(vector<Produs> lista)
{
	//cout << "\n";
	if (lista.size() == 0)
		cout << "Nu exista produse!\n";
	else
	{
		for (const auto& produs : lista)
		{
			cout << produs.get_nume() << " | " << produs.get_tip() << " | " << produs.get_pret() << " | " << produs.get_producator() << "\n";
		}
		cout << "\n";
	}

}

void Console::adaugaUi()
{
	string nume, tip, pro;
	int pret;
	cout << "Nume: ";
	cin >> nume;
	cout << "Tip: ";
	cin >> tip;
	cout << "Producator: ";
	cin >> pro;
	cout << "Pret: ";
	cin >> pret;
	try
	{
		serv.adauga_produs(nume, tip, pret, pro);
		cout << "\nProdus adaugat cu succes!\n";
	}
	catch (const RepositoryException& er)
	{
		cout << er << "\n";
	}
	catch (validateException err)
	{
		cout << err << '\n';
	}

}

void Console::stergeUI()
{
	string nume, pro;
	cout << "Nume: ";
	cin >> nume;
	cout << "Producator: ";
	cin >> pro;
	try {
		serv.sterge_produs(nume, pro);
		cout << "\nProdusul a fost sters!\n";
	}
	catch (const RepositoryException& e)
	{
		cout << e << "\n";
	}

}

void Console::caut()
{
	string nume, pro;
	cout << "Nume: ";
	cin >> nume;
	cout << "Producator: ";
	cin >> pro;
	try
	{
		const Produs& produs = serv.find_prod(nume, pro);
		cout << produs.get_nume() << " | " << produs.get_tip() << " | " << produs.get_pret() << " | " << produs.get_producator() << "\n";
	}
	catch (const RepositoryException& er)
	{
		cout << er << "\n";
	}
}
void Console::modifUI()
{
	string nume, tip_nou, producator;
	int pret_nou;
	cout << "Introduceti numele produsului pe care doriti sa il modificati: ";
	cin >> nume;
	cout << "Introduceti producatorul: ";
	cin >> producator;
	cout << "Introduceti noul tip: ";
	cin >> tip_nou;
	cout << "Introduceti noul pret: ";
	cin >> pret_nou;
	try
	{
		serv.modifica_produs(nume, tip_nou, pret_nou, producator);
		cout << "Elementul a fost modificat cu succes!\n";
	}
	catch (const RepositoryException& eroare)
	{
		cout << eroare << "\n";
	}
}
void Console::sortari()
{
	int cmd;
	cout << "\nOptiuni\n";
	cout << "1. Sortare dupa nume.\n2. Sortare dupa pret\n3. Sortare dupa nume si tip\n";
	cout << "Introduceti comanda: ";
	cin >> cmd;

	cout << "Lista sortata este:\n";
	if (cmd == 1)
		tipareste(serv.sortare_nume());
	else if (cmd == 2)
		tipareste(serv.sortare_pret());
	else if (cmd == 3)
		tipareste(serv.sortare_nume_tip());
	else cout << "Comanda invalida!\n";


}
void Console::filtrari()
{
	int cmd;
	cout << "Optiuni filtrare\n";
	cout << "1.Produse cu pretul egal cu o valoare data.\n2. Produse cu un anumit nume\n3. Produse ale unui anumit producator\n";
	cout << "Introduceti comanda: ";
	cin >> cmd;
	if (cmd == 1)
		filtrare_pret_ui();
	else if (cmd == 2)
		filtrare_nume_ui();
	else if (cmd == 3)
		filtrare_producator_ui();
	else cout << "Comanda invalida!\n";


}
void Console::filtrare_pret_ui()
{
	cout << "Introduceti pretul: ";
	int pret;
	cin >> pret;
	cout << "Lista de produse filtrate este:\n";
	tipareste(serv.filtrare_pret(pret));
}

void Console::filtrare_nume_ui()
{
	cout << "Introduceti numele dupa care doriti sa filtrati: ";
	string nume;
	cin >> nume;
	cout << "Lista de produse filtrate este:\n";
	tipareste(serv.filtrare_nume(nume));
}

void Console::filtrare_producator_ui()
{
	cout << "Introduceti numele dupa care doriti sa filtrati: ";
	string pro;
	cin >> pro;
	cout << "Lista de produse filtrate este:\n";
	tipareste(serv.filtrare_producator(pro));
}

//pt cos
void Console::cos_addUI()
{
	string nume, producator;
	cout << "Introduceti numele: ";
	cin >> nume;
	cout << "Introduceti producatorul: ";
	cin >> producator;

	try
	{
		serv.adauga_cos(nume, producator);
		cout << "Produs adaugat cu succes in cos!\n";
		cout << "TOTAL COS CUMPARATURI: " << serv.total_cos() << " lei\n";
	}
	catch (const RepositoryException& eroare)
	{
		cout << eroare << "\n";
	}
	catch (validateException eroare)
	{
		cout << eroare << '\n';
	}
}

void Console::print_cosUI()
{
	vector<Produs> lista = serv.getAllCos();
	if (lista.size() == 0)
	{
		cout << "Cosul este gol!\n";
		cout << "TOTAL COS CUMPARATURI: " << serv.total_cos() << " lei\n";
		return;
	}
	cout << "TOTAL COS CUMPARATURI: " << serv.total_cos() << " lei\n";
	int i = 0;
	for (const auto& product : lista)
	{
		cout << "-> " << product.get_nume() << " | " << product.get_producator() << '\n';
		i++;
	}
}
void Console::randCos()
{
	int nr;
	cout << "Numarul de produse dorite: ";
	cin >> nr;
	try
	{
		serv.genereaza_random_Cos(nr);
		cout << "Cosul a fost generat cu succes!\n";
		cout << "TOTAL COS CUMPARATURI: " << serv.total_cos() << " lei\n";
	}
	catch (const RepositoryException& eroare)
	{
		cout << eroare << '\n';
	}
}
void Console::exp_fisier()
{
	cout << "Introduceti numele fisierului in care doriti sa exportati cosul: ";
	string n;
	cin >> n;
	serv.exporta_cos(n);
	cout << "\nCos exportat cu succes!\n";
}
void Console::start()
{
	int optiune = 1;
	while (optiune != 0)
	{
		cout << "\nComenzi disponibile:\n";
		cout << "1. Adaugare produs\n";
		cout << "2. Tiparire produse\n";
		cout << "3. Cautare produs\n";
		cout << "4. Sterge produs\n";
		cout << "5. Modifica produs\n";
		cout << "6. Sortari\n";
		cout << "7. Filtrari\n";
		cout << "8. Adauga in cos\n";
		cout << "9. Goleste cosul\n";
		cout << "10. Afiseaza cosul\n";
		cout << "11. Genereaza random un cos\n";
		cout << "12. Exporta cos in fisier\n";
		cout << "13. Undo\n";
		cout << "0. Inchidere\n";
		cin >> optiune;
		try
		{
			switch (optiune)
			{
			case 0:
				optiune = 0;
				break;
			case 1:
				adaugaUi();
				break;
			case 2:
				try {
					tipareste(serv.getAll());
					break;
				}
				catch (const RepositoryException& e)
				{
					cout << e << "\n";
				}
			case 3:
				caut();
				break;
			case 4:
				stergeUI();
				break;
			case 5:
				modifUI();
				break;
			case 6:
				sortari();
				break;
			case 7:
				filtrari();
				break;
			case 8:
				cos_addUI();
				break;
			case 9:
				serv.goleste_cos();
				cout << "Cosul a fost golit cu succes!\n";
				cout << "TOTAL COS CUMPARATURI: " << serv.total_cos() << "lei\n";
				break;
			case 10:
				print_cosUI();
				break;
			case 11:
				randCos();
				break;
			case 12:
				exp_fisier();
				break;
			case 13:
				serv.undo();
				cout << "UNDO realizat cu succes!\n";
				tipareste(serv.getAll());
				break;
			default:
				cout << "\nComanda invalida!\n";
			}
		}
		catch (const RepositoryException& ex)
		{
			cout << "\n" << ex << "\n";
		}
		catch (const validateException& ex)
		{
			cout << "\n" << ex << "\n";
		}
	}
}