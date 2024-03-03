#pragma once
#pragma once
#include "Repo.h"

class RepoLab : public RepoAbstract
{
	map<int, Produs> lista;  //lista de produse
	double prob;
	bool exist(const Produs& p);
	/*
	functie privata ce verifica daca p exista deja in repository
	*/
public:
	RepoLab() = default;
	RepoLab(double n) : prob{ n } {} //constructor
	RepoLab(const RepoLab& repo) = delete;  //nu se permite copierea

	void generare_double();
	void store(const Produs& p) override;
	/*
	Adaugare produs
	arunca exceptie daca mai exista un produs cu acelasi tip, nume si producator
	*/

	const Produs& find(const string& nume, const string& producator) override;
	/*
	Cauta
	arunca exceptie daca nu exista produs
	*/

	vector <Produs> get_all() override;
	/*
	returneaza toate produsele salvate
	*/

	void sterge(const string& name, const string& producer) override;
	/*
	*	Sterge un produs din lista de produse,daca nu exista produsul respectiv se arunca exceptie
	*/

	int caut_poz(const string& nume, const string& producator) override;
	/*
	*	Caut pozitia unui produs in lista de produse dupa nume si producator, returneaza -1 daca nu il gaseste
	*/

	void modif(const string& nume, const string& tip_nou, int pret_nou, const string& producator) override;
	/*
	*	Modific un produs din lista de produse, modificand pretul si tipul, daca nu exista se arunca exceptie
	*/

};