#include "Validator.h"
#include "Repo.h"
#include <assert.h>
#include <sstream>

void ProdusValidator::validate(const  Produs& p)
{
	vector<string>msgs;  //un vector de mesaje
	if (p.get_pret() < 0) msgs.push_back("Pret negativ!");
	if (p.get_nume().size() == 0) msgs.push_back("Nume vid!");
	if (p.get_tip().size() == 0) msgs.push_back("Tip vid!");
	if (p.get_producator().size() == 0) msgs.push_back("Producator vid!");
	if (msgs.size() > 0)
	{
		throw validateException(msgs);
	}
}

void ProdusValidator::validate_cart(const string& name, const string& producer)
{
	vector<string> errors;
	if (name.size() == 0) errors.push_back("Eroare! Nume invalid!");
	if (producer.size() == 0) errors.push_back("Eroare! Producator invalid!");
	if (errors.size() > 0) throw validateException(errors);
}


ostream& operator<<(ostream& out, const validateException& ex)
{
	for (const auto& msg : ex.msgs)
	{ //afisarea fiecarui mesaj
		out << msg << " ";

	}
	return out;
}


void testValidator()
{
	ProdusValidator v;
	Produs p{ "","",-1,"" };
	try {
		v.validate(p);
	}
	catch (const validateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("Nume") >= 0);
		assert(mesaj.find("invalid") >= 0);

	}



}

void cos_validate()
{
	ProdusValidator v;
	try {
		v.validate_cart("", "");
	}
	catch (const validateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("Eroare!") >= 0);
		assert(mesaj.find("Tip") >= 0);
		assert(mesaj.find("Pret") >= 0);
		assert(mesaj.find("Producator") >= 0);
	}
}