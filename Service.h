#pragma once
#pragma once
#pragma once

#include "Repo.h"
#include "RepoLab.h"
#include "Validator.h"
#include "Cos.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <functional>

using std::function;
using std::vector;
using std::string;
using std::make_unique;
using std::unique_ptr;

class Service
{
	RepoAbstract& rep;
	//Repo& rep;
	ProdusValidator& val;
	Cos& cos;
	vector<unique_ptr<UndoAction>> undoActions;
	vector<Produs> sortare(bool (*cmpF)(const Produs&, const Produs&));
	/*
	* Functie generala de sortare
	* * cmpF - functie care compara 2 Produse
	* returneaza o lista sortata dupa criteriu dat ca paramatru
	*/

	vector<Produs> filtrare(function<bool(const Produs&)> fct);
	/*
	* Functie generala de filtrare
	* fct - poate fi o functie
	* returneaza doar produsele care indeplinesc cerinta de filtrare
*/

public:
	Service(RepoAbstract& rep, ProdusValidator& val, Cos& cos) noexcept : rep{ rep }, val{ val }, cos{ cos } {}

	Service(const Service& serv) = delete;


	int total_cos()
	{
		return cos.get_total();
	}
	//pt produse
	vector<Produs>getAll()
	{
		/*
			returneaza toate produsele in ordinea adaugarii
		*/
		return rep.get_all();
	}
	const vector<Produs>& getAllCos() noexcept
	{
		/*
			returneaza toate produsele din cos
		*/
		return cos.get_cos();
	}
	void goleste_cos();
	/*
		Goleste cosul
	*/

	void adauga_cos(const string& nume, const string& producator);
	/*
		Adauga un produs in cos
	*/

	void genereaza_random_Cos(int nr);
	/*
		Genereaza un cos cu nr produse
	*/

	void exporta_cos(const string& numeFisier);
	/*
		Exporta cosul in fisier
	*/
	void undo();

	void adauga_produs(const string& nume, const string& tip, int pret, const string& producator);
	/*
		Adauga un produs nou
		arunca exceptie daca nu se poate salva sau nu este valid
	*/

	const Produs& find_prod(const string& nume, const string& producator)const;
	/*
		Cauta un produs
	*/

	void sterge_produs(const string& nume, const string& producator);
	/*
		Sterge un produs
	*/
	void modifica_produs(const string& nume, const string& tip_nou, int pret_nou, const string& producator);
	/*
		Modifica un produs, modificand tipul si pretul
	*/

	vector <Produs> sortare_nume();
	/*
	*	Sortare dupa nume
	*/

	vector <Produs> sortare_pret();
	/*
	*	Sortare dupa pret
	*/

	vector <Produs> sortare_nume_tip();
	/*
	*	Sortare dupa nume si tip
	*/

	vector<Produs> filtrare_pret(int pret);
	/*
	* Filtreaza lista astfel incat toate produsele sa fie egale cu pretul dat
	*/

	vector<Produs> filtrare_nume(const string& nume);
	/*
	* Filtreaza lista astfel incat toate produsele sa aiba acelasi nume
	*/

	vector<Produs> filtrare_producator(const string& producator);
	/*
	* Filtreaza lista astfel incat toate produsele sa aiba acelasi producator
	*/


};

void service_test();
