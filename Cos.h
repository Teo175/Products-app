#pragma once
//Clasa pentru cosul de cumparaturi
#pragma once
#include "Produs.h"
#include <vector>
#include <string>
#include "observer.h"

using std::vector;

class Cos : public Observable
{
	vector<Produs> cos;
	int total;
public:
	Cos() = default;
	Cos(const vector<Produs>& v) : cos{ v }, total{ 0 } {}
	Cos(const Cos& c) : cos{ c.cos }, total{ c.total } {}

	void adauga(const Produs& p);
	void goleste() noexcept;
	void exp(string nume); //pt exporta
	void genereaza_cos(int nr, const vector<Produs>& v);
	int get_total() const
	{
		return total;
	}
	const vector<Produs>& get_cos() const noexcept;
};

void teste_cos();