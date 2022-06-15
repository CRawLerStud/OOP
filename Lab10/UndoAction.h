#pragma once
#include "Oferta.h"
#include "Repositorry.h"
class UndoAction
{
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdauga : public UndoAction {
private:
	Oferta ofertaAdaugata;
	Repositorry& repo;
public:
	UndoAdauga(Repositorry& repo, const Oferta& oferta) : repo{ repo }, ofertaAdaugata{ oferta }{}
	void doUndo() override {
		repo.stergeOferta(ofertaAdaugata.getDen());
	}
};

class UndoSterge : public UndoAction {
private:
	Oferta ofertaStearsa;
	Repositorry& repo;
public:
	UndoSterge(Repositorry& repo, const Oferta& oferta) : repo{ repo }, ofertaStearsa{ oferta }{}
	void doUndo() override {
		repo.adauga(ofertaStearsa);
	}
};

class UndoModifica : public UndoAction {
private:
	Oferta ofertaVeche;
	Oferta ofertaNoua;
	Repositorry& repo;
public:
	UndoModifica(Repositorry& repo, const Oferta& ofertaVeche, const Oferta& ofertaNoua) : repo{ repo }, ofertaVeche{ ofertaVeche }, ofertaNoua{ ofertaNoua }{}
	void doUndo() override {
		repo.stergeOferta(ofertaNoua.getDen());
		repo.adauga(ofertaVeche);
	}
};