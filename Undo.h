#pragma once
#pragma once
#pragma once
#include "Service.h"

class UndoAction {
public:
	virtual void doUndo() {};  virtual ~UndoAction() {};
};

class UndoAdauga : public UndoAction {
private:
	Produs produsAdaugat;
	RepoAbstract& rep;
public:
	UndoAdauga(RepoAbstract& rep, const Produs& p) : rep{ rep }, produsAdaugat{ p } {}
	void doUndo() override {
		rep.sterge(produsAdaugat.get_nume(), produsAdaugat.get_producator());
	}
};

class UndoSterge : public UndoAction {
private:
	Produs produsSters;
	RepoAbstract& rep;
public:
	UndoSterge(RepoAbstract& rep, const Produs& p) : rep{ rep }, produsSters{ p } {}
	void doUndo() override {
		rep.store(produsSters);
	}
};

class UndoModifica : public UndoAction {
private:
	Produs ProdusVechi;
	Produs ProdusModif;
	RepoAbstract& rep;
public:
	UndoModifica(RepoAbstract& rep, const Produs& p1, const Produs& p2) : rep{ rep }, ProdusVechi{ p1 }, ProdusModif{ p2 } {}
	void doUndo() override {
		rep.modif(ProdusVechi.get_nume(), ProdusVechi.get_tip(), ProdusVechi.get_pret(), ProdusVechi.get_producator());
	}
};