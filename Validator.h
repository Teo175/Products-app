#pragma once
#pragma once

#include "Repo.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class validateException
{
	vector<string>msgs;
public:
	validateException(const vector<string>& errors) : msgs{ errors } {}
	vector<string> getMsgs()const
	{
		return msgs;
	}
	friend ostream& operator<<(ostream& out, const validateException& ex);
};

ostream& operator<<(ostream& out, const validateException& ex);

class ProdusValidator
{
public:
	void validate(const Produs& p);
	void validate_cart(const string& name, const string& producer);
};

void testValidator();
void cos_validate();