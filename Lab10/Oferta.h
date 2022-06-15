#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Oferta {
	std::string denumire;
	std::string destinatie;
	std::string tip;
	int pret;
public:
	
	/*
	* Functie care creeaza o oferta a carui atribute sunt transmise ca parametru
	* Param den: denumirea ofertei(string)
	* Param dest: destinatia ofertei (string)
	* Param t: tipul ofertei (string)
	* Param p: pretul ofertei (int)
	* Return: o oferta a carui atribute sunt cele de mai sus
	*/

	Oferta() = default;

	Oferta(const string den, const string dest, const string t, const int p) :denumire{ den }, destinatie{ dest }, tip{ t }, pret{ p }{};

	Oferta(const Oferta& o) : denumire{ o.denumire }, destinatie{ o.destinatie }, tip{ o.tip }, pret{ o.pret }{
		//cout << "AM APELAT COPIATORUL\n";
	};

	~Oferta() = default;

	//returneaza denumirea ofertei
	string getDen() const;

	//returneaza destinatia ofertei
	string getDest() const;

	//returneaza tipul ofertei
	string getTip() const;

	//returneaza pretul ofertei
	int getPret() const noexcept;

	//seteaza numele ofertei la demNou
	void setDen(const string denNou);
	
	//seteaza destinatia ofertei la destNou
	void setDest(const string destNou);

	//seteaza tipul ofertei la tipNou
	void setTip(const string tipNou);

	//seteaza pretul ofertei la pretNou
	void setPret(int pretNou) noexcept;

	//verifica daca doua oferte sunt egale
	bool equal(Oferta off2);

};