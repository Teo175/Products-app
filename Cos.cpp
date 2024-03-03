#include "Cos.h"
#include <fstream>
#include <random>
#include "Repo.h"
#include "Service.h"
#include <assert.h>
using std::ofstream;

void Cos::adauga(const Produs& p)
{
	total += p.get_pret();
	cos.push_back(p);
}

void Cos::goleste() noexcept
{
	total = 0;
	cos.clear();
}

const vector<Produs>& Cos::get_cos() const noexcept
{
	return cos;
}


void Cos::genereaza_cos(int nr, const vector<Produs>& v)
{
	if (v.size() < 1)
		throw RepositoryException("Nu se poate genera un cos de produse!");

	const int lungime = int(v.size());
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(1, lungime - 1);
	//std::uniform_int_distribution<> frecv(1, 10);

	while (nr)
	{
		const int ind_produs = dist(mt);
		total += v[ind_produs].get_pret();
		//const int nr_produse = frecv(mt);
		adauga(v[ind_produs]);
		nr--;
	}

}

void Cos::exp(string nume)
{
	nume.append(".csv");
	ofstream f(nume);
	f << "Produs" << "Producator" << "Pret";
	for (const auto& c : cos)
	{
		f << c.get_nume() << " " << c.get_producator() << " " << c.get_pret() << " lei" << "\n";
	}

}

void teste_cos()
{
	Cos c;
	vector <Produs> v;
	assert(c.get_total() == 0);
	Repo repo;
	ProdusValidator valid;
	Service serv{ repo, valid,c };
	try
	{
		c.genereaza_cos(4, v); assert(false);
	}
	catch (const RepositoryException&) { assert(true); };


	Produs p1{ "bueno", "ciocolata",3,"kinder" };
	Produs p2{ "country", "ciocolata", 1, "kinder" };

	serv.adauga_produs("bueno", "ciocolata", 3, "kinder");
	serv.adauga_produs("country", "ciocolata", 1, "kinder");
	serv.adauga_produs("delice", "ciocolata", 2, "kinder");
	serv.adauga_produs("guma", "guma", 2, "orbit");

	assert(serv.total_cos() == 0);

	assert(c.get_cos().size() == 0);
	c.adauga(p1);
	c.adauga(p2);
	c.adauga(p1);
	assert(serv.total_cos() == 7);

	assert(c.get_cos().size() == 3);


	c.goleste();
	assert(c.get_cos().size() == 0);

	c.genereaza_cos(3, repo.get_all());
	assert(c.get_cos().size() > 0);

	c.goleste();
}