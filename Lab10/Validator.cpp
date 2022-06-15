#include "Validator.h"

void Validator::valideazaOferta(Oferta oferta) {
	string denumire = oferta.getDen();
	if (denumire.empty() == true)
		throw ValidationException("Oferta invalida!");

	for (int i = 0; i < denumire.size(); i++) 
		if (!(tolower(denumire.at(i)) >= 'a' && tolower(denumire.at(i) <= 'z') || (denumire.at(i) >= '0' && denumire.at(i) <= '9')))
			throw ValidationException("Oferta invalida!");

	string destinatie = oferta.getDest();
	if (destinatie.empty() == true)
		throw ValidationException("Oferta invalida!");

	for (int i = 0; i < destinatie.size(); i++)
		if (!(tolower(destinatie.at(i)) >= 'a' && tolower(destinatie.at(i) <= 'z') || destinatie.at(i) == '-'))
			throw ValidationException("Oferta invalida!");

	string tip = oferta.getTip();
	if (tip.empty() == true)
		throw ValidationException("Oferta invalida!");

	for (int i = 0; i < tip.size(); i++)
		if (!(tolower(tip.at(i)) >= 'a' && tolower(tip.at(i)) <= 'z'))
			throw ValidationException("Oferta invalida!");

	const int pret = oferta.getPret();
	if (pret <= 0)
		throw ValidationException("Oferta invalida!");
}