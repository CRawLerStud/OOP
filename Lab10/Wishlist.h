#pragma once
#include <vector>
#include <fstream>
#include <random>
#include "Repositorry.h"
#include "Oferta.h"

using std::vector;
using std::ofstream;

class Wishlist {
private:
	vector<Oferta> wElems;
public:
	/*
	* Adauga oferta in wishlist
	* Param denumire: denumirea unei oferte (string)
	* Return:-
	* Preconditii: Exista o oferta cu denumirea denumire in repositorry-ul aplicatiei
	*/
	void addOferta(Repositorry& repo, string denumire);

	/*
	* Goleste wishlist-ul
	* Return:-
	* Postconditii: Lista de oferte este goala
	*/
	void goleste() noexcept;

	/*
	* Verifica daca un element cu denumirea denumire exista in wishlist deja
	* Param denumire: denumirea elementului cautat
	* Return: true- daca exista, false - daca nu exista
	*/
	bool exists(string denumire) ;

	/*
	* Adauga n oferte random in wishlist
	* Param n: numarul de oferte adaugate
	* Return:-
	* Preconditii: n <= numarul de oferte din repositorry
	*/
	void addRandom(Repositorry& repo, int n);

	/*
	* returneaza o lista cu toate ofertele din wishlist
	* Return: lista cu ofertele din wishlist
	*/
	vector<Oferta> get_oferte() {
		return wElems;
	}

	/*
	* Introduce ofertele din wishlist intr-un fisier al carui nume este citit de la tastatura
	* Param filename: numele fisierului in care se trimit datele
	* Param repo: Repositorry-ul din care se preiau ofertele
	* Return:-
	* Throws:	RepoException - daca nu se poate deschide fisierul
	*/
	void exportWishlist(Repositorry& repo, string filename);

};

