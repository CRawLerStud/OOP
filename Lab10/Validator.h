#pragma once
#include "Oferta.h"

class Validator {
public:
	/*
	* Valideaza oferta transmisa ca parametru
	* Return: - daca este valid
	* Throws: Validation Error daca nu este valida oferta
	* DENUMIREA ESTE VALIDA DACA lungimea este mai mare decat 0 si daca are in componenta sa doar litere si numere
	* DESTINATIA ESTE VALIDA DACA lungimea sa este mai mare decat 0 si daca are in componenta sa doar litere si cratima
	* TIPUL ESTE VALID DACA lungimea sa este mai mare decat 0 si daca are in componenta sa doar litere
	* PRETUL ESTE VALID DACA valoarea sa este mai mare decat 0 strict
	*/
	void valideazaOferta(Oferta oferta);
};


class ValidationException {
private:
	string msg;
public:
	ValidationException(string errorMsg) : msg{ errorMsg } {};
	string getErrorMessage() {
		return this->msg;
	}
};