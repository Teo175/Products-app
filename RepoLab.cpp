#include "RepoLab.h"
#include <iostream>
#include <map>
#include <assert.h>
#include <random>
using namespace std;

bool RepoLab::exist(const Produs& p)
{
	const int poz = caut_poz(p.get_nume(), p.get_producator());
	if (poz == -1) return false;
	else return true;
}

void RepoLab::store(const Produs& p)
{
	generare_double();

	if (exist(p))
		throw RepositoryException("Exista deja acest produs!");
	else
		lista[(int)lista.size()] = p;

}

const Produs& RepoLab::find(const string& nume, const string& producator)
{
	generare_double();
	for (int i = 0; i < lista.size(); i++)
	{
		if (lista[i].get_nume() == nume && lista[i].get_producator() == producator)
		{
			return  lista[i];
		}
	}
	throw RepositoryException("Nu exista acest produs!");
}

vector<Produs> RepoLab::get_all()
{
	generare_double();
	vector<Produs> v;
	for (int i = 0; i < lista.size(); i++)
	{
		v.push_back(lista[i]);
	}
	return v;
}

int RepoLab::caut_poz(const string& nume, const string& producator)
{
	generare_double();
	for (int i = 0; i < lista.size(); i++)
		if (lista[i].get_nume() == nume && lista[i].get_producator() == producator)
			return i;
	return -1;
}
void RepoLab::sterge(const string& nume, const string& producator)
{
	generare_double();
	const int ind = caut_poz(nume, producator);
	if (ind == -1)
		throw RepositoryException("Elementul pe care doriti sa il stergeti nu exista!");
	auto first_element = lista.begin();
	lista.erase(ind);

}

void RepoLab::modif(const string& nume, const string& tip_nou, int pret_nou, const string& producator)
{
	generare_double();
	const int ind = caut_poz(nume, producator);
	if (ind == -1)
		throw RepositoryException("Elementul pe care doriti sa il modificati nu exista!");
	lista[ind].set_tip(tip_nou);
	lista[ind].set_pret(pret_nou);

}

void RepoLab::generare_double()
{
	double lower_bound = 0;
	double upper_bound = 1;

	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	default_random_engine re;
	double random_double = unif(re);
	if (random_double < prob)
		throw RepositoryException("Nu se poate efectua aceasta operatie!");
}

/*
* void repo_labtest()
{
	RepoLab repo{ 0.1 };
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


*/
