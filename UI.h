#pragma once
#pragma once
#pragma once
#include "Service.h"


class Console
{
	Service& serv;

	void adaugaUi();
	/*
		Citeste de la tastatura si adauga Produs
		arunca exceptie daca produsul nu se poate salva sau nu e valid
	*/

	void tipareste(vector<Produs> lista);
	/*
		Tipareste lista de produse
	*/

	void caut();
	/*
		Cauta un produs in lista de produse
	*/

	void stergeUI();
	/*
	*	Sterge un produs din lista de produse
	*/

	void modifUI();
	/*
	*	Modifica un produs din lista de produse
	*/

	void sortari();
	/*
	*	Sorteaza produsele dupa anumite criterii
	*/

	void filtrari();
	/*
	*	Filtreaza lista de produse dupa anumite criterii
	*/

	void filtrare_pret_ui();
	/*
	*	Filtrarea produselor care au pretul egal cu o valoare data de la tastatura
	*/

	void filtrare_nume_ui();
	/*
	* Filtrarea produselor care au numele egal cu o valoare data de la tastatura
	*/

	void filtrare_producator_ui();
	/*
	* Filtrarea produselor care au producatorul egal cu o valoare data de la tastatura
	*/

	void cos_addUI();

	/*
	* Functia afiseaza ce se afla in cosul de cumparaturi
	*/
	void print_cosUI();

	void randCos();
	void exp_fisier();


public:
	Console(Service& serv) noexcept : serv{ serv } {}
	Console(const Console& c) = delete; //nu permitem copierea obtului de tip consola

	void start();
};