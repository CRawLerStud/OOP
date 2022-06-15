#pragma once
#include "Oferta.h"

#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using std::vector;
using std::map;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::stringstream;

class Repositorry {
private:
	vector<Oferta> elems;
public:
	//constructor Repositorry
	Repositorry()  = default;

	//constructor de copiere
	Repositorry(const Repositorry& ot) = delete;

	virtual ~Repositorry() = default;

	/*
	* Adauga o oferta in repositorry
	* param oferta: oferta care urmeaza sa fie adauga in repo
	* return: -
	* post: oferta va fi adauga in lista
	* throws: RepoException daca exista deja o oferta cu acelasi nume
	*/
	virtual void adauga(const Oferta& oferta);

	/*
	* Returneaza o lista cu toate ofertele din repositorry
	* return: lista cu ofertele
	*/
	vector<Oferta>& getOferte() noexcept ;

	/*
	* cauta oferta cu denumirea den transmisa ca parametru
	* param den: denumirea ofertei cautate
	* return: oferta cu denumirea den
	* throws: RepoException daca nu exista oferta cu denumirea den
	*/
	const Oferta find(string den);

	/*
	* Verifica daca o oferta exista in repositorry
	* param oferta: oferta care se cauta in repositorry
	* return: true, daca exista, false daca nu exista
	*/
	bool exists(const Oferta& oferta);

	/*
	* modifica denumirea ofertei a carui denumire este den cu oferta oferta transmisa ca parametru
	* Param den: denumirea ofertei care trebuie modificata
	* Param oferta: oferta care inlocuieste oferta cu denumirea den
	* Return: - 
	* Preconditii: oferta este valida
	* Postconditii: oferta cu denumirea den devine oferta (transmisa ca parametru)
	* Throws:	RepoException - oferta noua exista deja (Element existent)
	*/
	virtual void modificaDenumire(string den, const Oferta& oferta);

	/*
	* modifica tip/pret/destinatie ofertei a carui denumire este den
	* Param den: denumirea ofertei care trebuie modificata
	* Param oferta: oferta care inlocuieste oferta cu denumirea den
	* Return: -
	* Preconditii: oferta este valida
	* Postconditii: oferta cu denumirea den devine oferta (transmisa ca parametru)
	*/
	virtual void modificaOferta(string den, const Oferta& oferta);

	/*
	* Sterge oferta a carui denumire este den
	* Param den: denumirea ofertei care trebuie stearsa
	* Return: -
	* Throws:	RepoException - "Element inexistent" - daca nu exista oferta cu denumirea den
	*/
	virtual void stergeOferta(string den);

	/*
	* Returneaza o lista cu oferte a caror destinatie contine substring-ul destinatie transmis ca parametru
	* Param destinatie: substringul care se cauta
	* Return: o lista cu ofertele a caror destinatie contine substringul destinatie
	*/
	vector<Oferta> filtrareDestinatie(string destinatie);

	/*
	* Returneaza o lista cu oferte a caror pret este mai mic decat unul dat ca parametru
	* Param pretMaxim: pretul maxim admis
	* Return: o lista cu ofertele a caror pret este mai mic decat pretMaxim
	*/
	vector<Oferta> filtrarePret(int pretMaxim);

	/*
	* Sortare crescatoare a repositorry-ului
	* Param: functia de comparare a ofertelor
	*/
	void sortare(bool (*func)(Oferta, Oferta));

	/*
	* Returneaza un dictionar - raport - cate oferte sunt de un anume tip
	* Return: un dictionar raport
	*/
	map<string, int> RaportTip();

	//sterge toate elementele din repositorry
	void goleste() noexcept;
};


class RepositorryFile : public Repositorry {
private:
	string filename;

	//incarca din fisierul filename
	void loadFromFile();

	//stocheaza datele in fisierul filename
	void storeToFile();

public:
	RepositorryFile(string fname) :Repositorry(), filename(fname) {
		loadFromFile();
	}

	void adauga(const Oferta& oferta) override {
		Repositorry::adauga(oferta);
		storeToFile();
	}

	void stergeOferta(string denumire)override {
		Repositorry::stergeOferta(denumire);
		storeToFile();
	}
	void modificaDenumire(string den, const Oferta& oferta) override {
		Repositorry::modificaDenumire(den, oferta);
		storeToFile();
	}
	void modificaOferta(string den, const Oferta& oferta) override {
		Repositorry::modificaOferta(den, oferta);
		storeToFile();
	}
	
};


class RepoException {
private:
	string msg;
public:
	RepoException(string errorMsg) : msg{ errorMsg } {};
	string getErrorMessage() {
		return this->msg;
	}
};


bool cmpDenumire(Oferta off1, Oferta off2);

bool cmpDestinatie(Oferta off1, Oferta off2);

bool cmpTipPret(Oferta off1, Oferta off2);

void exportToCSV(string fname, vector<Oferta> vectorOferte);