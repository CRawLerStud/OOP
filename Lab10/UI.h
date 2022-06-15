#pragma once
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <crtdbg.h>
#include <assert.h>
#include "MainTests.h"
#include "Service.h"
using namespace std;

class UI {
private:
	Service service;
public:

	UI(Service& service) noexcept :service{ service } {};

	//sorteaza lista dupa denumire, destinatie, tip+pret la algere
	void UI_Sortare();

	//filtreaza dupa denumire sau pret lista
	void UI_Filtrare();

	//sterge oferta a carui denumire e citita de la tastatura
	void UI_StergeOferta();

	//gaseste oferta cu o denumire citita de la tastatura
	void UI_FindOferta();

	//adauga 10 oferte predefinite
	void UI_AdaugaOferteDebug();

	//modifica o oferta
	void UI_ModificaOferta();

	//afiseaza toate ofertele
	void UI_PrintOferte(vector<Oferta>& oferte);

	//adauga o oferta a caror parametrii sunt cititi de la tastatura
	void UI_AddOferta();

	//'design' pt inceput
	void begin_print();

	//printeaza meniul aplicatiei
	void print_menu();

	//afisare exit message
	void exit_print();

	//afiseaza wishlist-ul
	void UI_PrintWishlist();

	//adauga oferta in wishlist dupa o denumire citita de la tastatura
	void UI_AddWishlist();

	//adauga un numar de oferte citit de la tastatura in wishlist
	void UI_AddRandom();

	//goleste wishlist-ul
	void UI_WishlistGoleste();

	//printeaza raportul pentru tip
	void UI_RaportTip();

	//salveaza wishlist-ul intr-un fisier citit de la tastatura ( numele sau )
	void UI_ExportWishlist();

	//undo la ultima actiune
	void UI_undo();

	void run();
};