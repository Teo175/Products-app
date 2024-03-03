#include "Produs.h"
#include <assert.h>
bool cmp_nume(const Produs& p1, const Produs& p2)
{
	return p1.get_nume() < p2.get_nume();
}

bool cmp_pret(const Produs& p1, const Produs& p2) noexcept
{
	return p1.get_pret() < p2.get_pret();
}

bool cmp_producator(const Produs& p1, const Produs& p2)
{
	return p1.get_producator() < p2.get_producator();
}

bool cmp_nume_tip(const Produs& p1, const Produs& p2)
{
	if (p1.get_nume() == p2.get_nume())
		return p1.get_tip() < p2.get_tip();
	else
		return p1.get_nume() < p2.get_nume();
}

void testProdus()
{

	Produs p1{ "bueno","ciocolata",5,"kinder" }, p2{ "country","ciocolata",2,"kkinder" };
	assert(p1.get_nume() == "bueno");
	assert(p1.get_tip() == "ciocolata");
	assert(p1.get_producator() == "kinder");
	assert(p1.get_pret() == 5);

	Produs aux = p1;
	assert(p1.get_nume() == aux.get_nume());

	p2.set_pret(2);
	assert(p2.get_pret() == 2);

	p2.set_tip("cioco");
	assert(p2.get_tip() == "cioco");

	assert(cmp_nume(p1, p2) == true);
	assert(cmp_pret(p1, p2) == false);
	assert(cmp_nume_tip(p1, p2) == true);
	assert(cmp_producator(p1, p2) == true);
}