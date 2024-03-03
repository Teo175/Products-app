#pragma once
#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
class Produs
{
	//Produs: nume, tip, pre?, producãtor
	string nume;
	string tip;
	int pret;
	string producator;
public:
	//constructor+constructor copie
	Produs() = default;
	Produs(const string nume, const string tip, const int pret, const string producator) : nume{ nume }, tip{ tip }, pret{ pret }, producator{ producator } {}
	Produs(const Produs& other) : nume{ other.nume }, tip{ other.tip }, pret{ other.pret }, producator{ other.producator } { /*cout << "copy.constr.called\n"; */ }

	//getteri
	string get_nume() const
	{
		return nume;  //sau this->nume
	}
	string get_tip() const
	{
		return tip;
	}
	int get_pret() const noexcept
	{
		return pret;
	}
	string get_producator() const
	{
		return producator;
	}
	//setteri
	void set_tip(const string& tip_nou) { tip = tip_nou; }


	void set_pret(int pret_nou) noexcept { pret = pret_nou; }
};

bool cmp_nume(const Produs& p1, const Produs& p2);
/*
	Compara dupa nume
	return: true daca p1.nume e mai mic decat p2.nume
*/

bool cmp_pret(const Produs& p1, const Produs& p2) noexcept;
/*
	Compara dupa pret
	return: true daca p1.pret e mai mic decat p2.pret
*/

bool cmp_producator(const Produs& p1, const Produs& p2);
/*
	Compara dupa producator
	return: true daca p1.producator e mai mic decat p2.producator (lexicografic)
*/

bool cmp_nume_tip(const Produs& p1, const Produs& p2);
/*
	Compara dupa nume + tip
	return: 1 daca p1.nume e mai mic decat p2.nume (daca sunt egale, returneaza true daca p1.tip e mai mic decat p2.tip
*/

void testProdus();

