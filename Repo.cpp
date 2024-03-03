#include "Repo.h"
#include <iostream>
#include <map>
#include <assert.h>
#include <random>
using namespace std;

bool Repo::exist(const Produs& p)
{
	const int poz = caut_poz(p.get_nume(), p.get_producator());
	if (poz == -1) return false;
	else return true;
}

void Repo::store(const Produs& p)
{
	if (exist(p))
		throw RepositoryException("Exista deja acest produs!");
	else
		lista.push_back(p);
}

const Produs& Repo::find(const string& nume, const string& producator)
{
	for (const auto& p : lista)
	{
		if (p.get_nume() == nume && p.get_producator() == producator)
		{
			return  p;
		}
	}
	throw RepositoryException("Nu exista acest produs!");
}

vector<Produs> Repo::get_all()
{

	return lista;
}

int Repo::caut_poz(const string& nume, const string& producator)
{

	for (int i = 0; i < lista.size(); i++)
		if (lista[i].get_nume() == nume && lista[i].get_producator() == producator)
			return i;
	return -1;
}

void Repo::sterge(const string& nume, const string& producator)
{
	const int ind = caut_poz(nume, producator);
	if (ind == -1)
		throw RepositoryException("Elementul pe care doriti sa il stergeti nu exista!");
	auto first_element = lista.begin();
	lista.erase(first_element + ind);
}

void Repo::modif(const string& nume, const string& tip_nou, int pret_nou, const string& producator)
{
	const int ind = caut_poz(nume, producator);
	if (ind == -1)
		throw RepositoryException("Elementul pe care doriti sa il modificati nu exista!");
	lista[ind].set_tip(tip_nou);
	lista[ind].set_pret(pret_nou);
}

ostream& operator<<(ostream& out, const RepositoryException& ex) {
	out << ex.erori;
	return out;
}



void repo_test()
{
	Repo repo;
	Produs p1{ "bueno","ciocolata",3,"kinder" }, p2{ "country","ciocolata",2,"kinder" };

	assert(repo.get_all().size() == 0);
	repo.store(p1);
	repo.store(p2);
	assert(repo.get_all().size() == 2);

	try
	{
		repo.store(p1);
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}


	repo.modif("bueno", "cioco", 10, "kinder");
	Produs p_aux = repo.find("bueno", "kinder");
	assert(p_aux.get_nume() == "bueno");
	assert(p_aux.get_tip() == "cioco");
	assert(p_aux.get_pret() == 10);
	assert(p_aux.get_producator() == "kinder");
	try
	{
		repo.modif("bulgarasi", "hochland", 12, "branza");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	try
	{
		p_aux = repo.find("bulgarasi", "hochland");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	int index = repo.caut_poz("country", "kinder");
	assert(index == 1);
	index = repo.caut_poz("delice", "kinder");
	assert(index == -1);

	repo.sterge("country", "kinder");
	assert(repo.get_all().size() == 1);
	try
	{
		repo.sterge("bulgarasi", "hochland");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}
	repo.sterge("bueno", "kinder");
	assert(repo.get_all().size() == 0);
}