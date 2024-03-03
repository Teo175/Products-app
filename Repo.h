#pragma once
#pragma once
#include "Produs.h"
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <map>
using std::string;
using std::vector;
using std::ostream;
using std::map;

class RepoAbstract
{
private:

public:

	virtual void store(const Produs& p) = 0;

	virtual const Produs& find(const string& nume, const string& producator) = 0;

	virtual vector<Produs> get_all() = 0;

	virtual void sterge(const string& name, const string& producer) = 0;

	virtual int caut_poz(const string& nume, const string& producator) = 0;

	virtual void modif(const string& nume, const string& tip_nou, int pret_nou, const string& producator) = 0;
};


class Repo : public RepoAbstract
{
	vector <Produs> lista;  //lista de produse
	bool exist(const Produs& p);
	/*
	functie privata ce verifica daca p exista deja in repository
	*/
public:
	Repo() = default;
	Repo(const Repo& repo) = delete;  //nu se permite copierea

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


//Clasa pentru erori ale repository-ului
class RepositoryException
{
private:
	string erori;
public:
	//Constructorul clasei
	RepositoryException(string mesaj) : erori{ mesaj } {}

	//Pentru a putea avea acces la campul erori
	string getMsg()const
	{
		return erori;
	}
	friend ostream& operator<<(ostream& out, const RepositoryException& mesaj);
};

//Functia trimite erorile ca mesaj
ostream& operator<<(ostream& out, const RepositoryException& mesaj);


void repo_test();
void repo_labtest();