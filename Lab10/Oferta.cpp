#include "Oferta.h"

string Oferta::getDen() const {
	return denumire;
}

void Oferta::setDen(const string denNou) {
	denumire = denNou;
}

string Oferta::getDest() const {
	return destinatie;
}

void Oferta::setDest(const string destNou) {
	destinatie = destNou;
}

string Oferta::getTip() const {
	return tip;
}

void Oferta::setTip(const string tipNou) {
	tip = tipNou;
}

int Oferta::getPret() const noexcept{
	return pret;
}

void Oferta::setPret(int pretNou) noexcept{
	pret = pretNou;
}

bool Oferta::equal(Oferta off2) {
	return denumire.compare(off2.getDen()) == 0;
}