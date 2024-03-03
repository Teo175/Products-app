#include "Service.h"
#include <functional>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstring>
using namespace std;
void Service::adauga_produs(const string& nume, const string& tip, int pret, const string& producator)
{
	Produs p{ nume,tip,pret,producator };
	val.validate(p);
	rep.store(p);
	undoActions.push_back(make_unique<UndoAdauga>(rep, p));
}

const Produs& Service::find_prod(const string& nume, const string& producator)const
{
	return rep.find(nume, producator);
}

void Service::sterge_produs(const string& nume, const string& producator)
{
	Produs p = rep.find(nume, producator);
	rep.sterge(nume, producator);
	undoActions.push_back(make_unique<UndoSterge>(rep, p));
}

void Service::modifica_produs(const string& nume, const string& tip_nou, int pret_nou, const string& producator)
{
	Produs p1 = rep.find(nume, producator);
	Produs p2{ p1.get_nume(),tip_nou,pret_nou,p1.get_producator() };
	rep.modif(nume, tip_nou, pret_nou, producator);
	undoActions.push_back(make_unique<UndoModifica>(rep, p1, p2));
}

//SORTARI+FILTRARI
vector <Produs> Service::sortare(bool (*cmpF)(const Produs&, const Produs&))
{
	vector<Produs> copy_list{ rep.get_all() };
	for (int i = 0; i < copy_list.size() - 1; i++)
		for (int j = i + 1; j < copy_list.size(); j++)
			if (!cmpF(copy_list[i], copy_list[j]))
			{
				Produs aux = copy_list[i];
				copy_list[i] = copy_list[j];
				copy_list[j] = aux;
			}
	return copy_list;
}

vector <Produs> Service::sortare_nume()
{
	return sortare(cmp_nume);
}

vector <Produs> Service::sortare_pret()
{
	return sortare(cmp_pret);
}
vector <Produs> Service::sortare_nume_tip()
{
	return sortare(cmp_nume_tip);
}

//Filtrare
vector<Produs> Service::filtrare(function<bool(const Produs&)> fct)
{
	vector <Produs> sol;
	for (const auto& p : rep.get_all())
		if (fct(p)) sol.push_back(p);
	return sol;
}

vector<Produs> Service::filtrare_pret(int price)
{
	return filtrare([price](const Produs& p) noexcept
		{
			return p.get_pret() == price;
		});
}

vector<Produs> Service::filtrare_nume(const string& nume)
{
	return filtrare([nume](const Produs& p)
		{
			return p.get_nume() == nume;
		});
}

vector<Produs> Service::filtrare_producator(const string& producator)
{
	return filtrare([producator](const Produs& p)
		{
			return p.get_producator() == producator;
		});
}
void Service::adauga_cos(const string& nume, const string& producator)
{
	Produs p = find_prod(nume, producator);
	cos.adauga(p);
}


void Service::goleste_cos()
{
	cos.goleste();
}


void Service::exporta_cos(const string& nume_fisier)
{
	cos.exp(nume_fisier);
}
void Service::genereaza_random_Cos(int nr)
{
	cos.genereaza_cos(nr, getAll());
}
void Service::undo()
{
	if (undoActions.empty())
	{
		throw RepositoryException("Nu se mai poate face undo!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
void service_test()
{
	Repo repo;
	ProdusValidator valid;
	Cos cos;
	Service serv{ repo, valid,cos };

	try
	{
		serv.undo();
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);

	}
	try
	{
		serv.genereaza_random_Cos(4); assert(false);
	}
	catch (const RepositoryException&) { assert(true); };
	assert(serv.getAllCos().size() == 0);

	serv.adauga_produs("bueno", "ciocolata", 3, "kinder");
	serv.adauga_produs("country", "ciocolata", 1, "kinder");
	assert(serv.getAll().size() == 2);
	serv.undo();
	assert(serv.getAll().size() == 1);
	serv.adauga_produs("country", "ciocolata", 1, "kinder");


	serv.adauga_cos("bueno", "kinder");
	assert(serv.getAllCos().size() == 1);
	//cv ce nu exista
	try
	{
		serv.adauga_cos("apa", "dorna");
		assert(false);
	}
	catch (const RepositoryException&) { assert(true); };

	serv.goleste_cos();
	assert(serv.getAllCos().size() == 0);

	assert(serv.getAll().size() == 2);
	try //adaug cv invalid 
	{
		serv.adauga_produs("", "", -1, "");
		assert(false);
	}
	catch (validateException&)
	{
		assert(true);
	}

	try //adaug cv existent deja
	{
		serv.adauga_produs("bueno", "cioco", 3, "kinder");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	assert(serv.getAll().size() == 2);

	try //modific cv inexistent
	{
		serv.modifica_produs("bulgarasi", "hochland", 5, "branza");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	Produs prod = serv.find_prod("bueno", "kinder");
	assert(prod.get_tip() == "ciocolata");
	serv.modifica_produs("bueno", "vanilia", 3, "kinder");
	Produs nou = serv.find_prod("bueno", "kinder");
	assert(nou.get_tip() == "vanilia");
	serv.undo();

	serv.modifica_produs("bueno", "vanilia", 3, "kinder");
	Produs aux = serv.find_prod("bueno", "kinder");
	assert(aux.get_nume() == "bueno");
	assert(aux.get_pret() == 3);
	assert(aux.get_tip() == "vanilia");



	try
	{
		aux = serv.find_prod("aa", "aa");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	try
	{
		serv.sterge_produs("cc", "cc");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}
	assert(serv.getAll().size() == 2);
	serv.sterge_produs("bueno", "kinder");
	assert(serv.getAll().size() == 1);  //ramane doar k=country kinder
	serv.undo();
	assert(serv.getAll().size() == 2);
	serv.sterge_produs("bueno", "kinder");

	serv.adauga_produs("bueno", "ciocolata", 3, "kinder");
	serv.adauga_produs("delice", "ciocolata", 2, "kinder");
	serv.adauga_produs("guma", "guma", 1, "orbit");
	serv.adauga_produs("bueno", "ciocolata", 3, "kinder white");

	vector <Produs> v;
	v = serv.filtrare_nume("bueno");
	assert(v.size() == 2);

	v = serv.filtrare_pret(2);
	assert(v.size() == 1);

	v = serv.filtrare_producator("kinder");
	assert(v.size() == 3);

	v = serv.sortare_nume();
	assert(v[0].get_nume() == "bueno");
	assert(v[1].get_nume() == "bueno");
	assert(v[2].get_nume() == "country");
	assert(v.size() == 5);

	v = serv.sortare_nume_tip();
	assert(v[0].get_nume() == "bueno");
	assert(v[1].get_nume() == "bueno");
	assert(v[2].get_nume() == "country");
	assert(v.size() == 5);

	v = serv.sortare_pret();
	assert(v[0].get_nume() == "guma");
	assert(v[1].get_nume() == "country");
	assert(v[2].get_nume() == "delice");

	serv.goleste_cos();
	serv.adauga_cos("guma", "orbit");
	assert(serv.getAllCos().size() == 1);
	serv.exporta_cos("fisier");




}
