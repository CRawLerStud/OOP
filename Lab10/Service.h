#pragma once
#include "Repositorry.h"
#include "Wishlist.h"
#include "Validator.h"
#include "UndoAction.h"
#include <memory>
#include <vector>
#include "Observer.h"

using std::shared_ptr;

class Service : public Observable {
private:
	Repositorry& repo;
	Repositorry& wishlist;
	Validator& validator;

	vector<shared_ptr<UndoAction>> undoActions;
public:
	//contructor
	Service(Repositorry& repo, Validator& validator, Repositorry& wish) noexcept :repo{ repo }, validator{ validator }, wishlist{ wish }{};

	/*
	* Adauga oferta in repositorry-ul aplicatiei
	* Param oferta: oferta care trebuie adaugata in repositorry
	* Return: - daca a functionat cu succes
	* Throws:	RepoException - daca exista in repositorry deja
	*			ValidationException - daca nu este valida oferta transmisa ca parametru
	*/
	void adauga(Oferta oferta);

	/*
	* returneaza lista cu toate ofertele existente
	* Return: lista cu toate ofertele
	* Throws: -
	*/
	vector<Oferta>& Oferte() noexcept ;

	/*
	* modifica o oferta din repo a carui denumire este den - i se schimba denumirea
	* Param den: denumirea obiectului care trebuie modificat
	* Param denumireNoua: denumireaNoua
	* Return:-
	* Throws:	ValidationException - "Oferta invalida!" - daca nu este valida denumirea noua
	*			RepoException - "Element inexistent!" - daca nu exista oferta cu denumirea den
	*								 - "Element existent!" - daca exista deja oferta cu denumirea noua
	*/
	void modificareDenumireOferta(string den, string denumireNoua);

	/*
	* modifica o oferta din repo a carui denumire este den - i se schimba destinatia
	* Param den: denumirea obiectului care trebuie modificat
	* Param destinatieNoua: destinatia Noua a ofertei cu denumirea den
	* Return:-
	* Throws:	ValidationException - "Oferta invalida!" - daca nu este valida destinatia noua
	*			RepoException - "Element inexistent!" - daca nu exista oferta cu denumirea den
	*/
	void modificareDestinatieOferta(string den, string destinatieNoua);

	/*
	* modifica o oferta din repo a carui denumire este den - i se schimba tipul
	* Param den: denumirea obiectului care trebuie modificat
	* Param tipNou: tipul Nou al ofertei cu denumirea den
	* Return:-
	* Throws:	ValidationException - "Oferta invalida!" - daca nu este valid tipul nou
	*			RepoException - "Element inexistent!" - daca nu exista oferta cu denumirea den
	*/
	void modificareTipOFerta(string den, string tipNou);

	/*
	* modifica o oferta din repo a carui denumire este den - i se schimba pretul
	* Param den: denumirea obiectului care trebuie modificat
	* Param pretNou: pretul Nou al ofertei cu denumirea den
	* Return: -
	* Throws:	ValidationException - "Oferta invalida!" - daca nu este valid pretul nou
	*			RepoException - "Element inexistent!" - daca nu exista obiectul cu denumirea den
	*/
	void modificarePretOferta(string den, int pretNou);

	/*
	* Gaseste oferta a carui denumire este den si o returneaza
	* Param den: denumirea ofertei cautate
	* Return: Oferta a carui denumire este den daca exista
	* Throws: RepoException - "Element inexistent" - daca nu exista oferta cu denumirea den
	*/
	Oferta gasesteOferta(string den);

	/*
	* Sterge o oferta a carui denumire este den
	* Param den: denumirea ofertei care trebuie stearsa
	* Return: -
	* Throws: RepoException - "Element inexistent" - daca nu exista oferta cu denumirea den
	*/
	void stergeOferta(string den);

	/*
	* Returneaza o lista cu oferte a caror destinatie este un sir de caractere transmis ca parametru
	* Param destinatie: destinatia cautata
	* Return: o lista cu ofertele a caror destinatie este destinatie
	*/
	vector<Oferta> filtrareDestinatie(string destinatie);

	/*
	* Returneaza o lista cu oferte a caror pret este mai mic sau egal decat pretul transmis ca parametru
	* Param pret: pretul maxim admis
	* Return: o lista cu ofertele care indeplinesc conditia data
	*/
	vector<Oferta> filtrarePret(int pret);

	/*
	* Sorteaza crescator dupa denumire repositorry-ul
	* Param func: functia folosita pentru sortare;
	* Postconditii: repositorry-ul este sortat
	*/
	void SortareDenumire();

	void SortareDestinatie();
	
	void SortareTipPret();
	
	/*
	* adauga elementul a carui denumire este denumire in lista de wishlist
	* Param denumire: denumirea ofertei cautate
	* Return: - 
	* Throws:	RepoException - nu exista elementul cautat
	*			RepoException - exista deja in wishlist elementul cautat
	*/
	void adaugaWishlist(string denumire);

	/*
	* sterge elementul a carui denumire este denumire din lista de wishlist
	* Param denumire: denumirea ofertei cautate
	* Return: -
	* Throws:	RepoException - nu exista elementul cautat
	*/
	void stergeWishlist(string denumire);

	/*
	* Adauga random n elemente din repositorry in wishlist
	* Param n : numarul de oferte de adaugat
	* Return: -
	* Throws:	Daca n + wishlist.size() > nrOferte  -> RepoException("Numar invalid")
	*/
	void adaugaRandomWishlist(int n);

	/*
	* Goleste wishlist-ul
	* Return:-
	* Postconditii: wishlist-ul este gol
	*/
	void golesteWishlist() noexcept;

	/*
	* returneaza wishlist-ul
	* return: wishlist-ul
	*/
	Repositorry& getWishlist() noexcept{
		return wishlist;
	}

	/*
	* Returneaza un raport pentru tip
	* Return: raport pentru tip ( map )
	*/
	map<string, int> RaportTip() {
		return repo.RaportTip();
	}

	/*
	* Transmite datele din Wishlist intr-un fisier al carui nume este transmis ca parametru
	*/
	void ExportWishlist(string filename);

	/*
	* Face invers ultimul pas
	*/
	void undo();

};