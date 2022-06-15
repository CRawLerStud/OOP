#include "Repositorry.h"
#include <assert.h>


void Repositorry::adauga(const Oferta& oferta) {
	if (exists(oferta))
		throw RepoException("Element existent!");
	elems.push_back(oferta);
}

bool Repositorry::exists(const Oferta& oferta) {
	vector<Oferta>::iterator it = std::find_if(elems.begin(), elems.end(), [&](Oferta const off) {
		return off.getDen() == oferta.getDen();
		}
	);

	if (it != elems.end())
		return true;
	else
		return false;

}

const Oferta Repositorry::find(string den) {

	vector<Oferta>::iterator it = std::find_if(elems.begin(), elems.end(), [&](Oferta const off) {
		return off.getDen().compare(den) == 0;
		}
	);

	if (it != elems.end())
		return *it;
	else
		throw RepoException("Element inexistent!");

}

vector<Oferta>& Repositorry::getOferte() noexcept {
	return this->elems;
}

void Repositorry::modificaDenumire(string den, const Oferta& oferta) {
	if (exists(oferta) == true)
		throw RepoException("Element existent!");

	for (auto& elem : Repositorry::getOferte())
		if(&elem != nullptr)
			if (elem.getDen().compare(den) == 0)
				elem = oferta;
}

void Repositorry::modificaOferta(string den, const Oferta& oferta) {
	for (auto& elem : Repositorry::getOferte())
		if(&elem != nullptr)
			if (elem.getDen().compare(den) == 0)
				elem = oferta;
}

//DE MODIFICAT
void Repositorry::stergeOferta(string den) {
	if (exists(find(den)) == false)	throw RepoException("Element inexistent!");

	for (int i = 0; i < elems.size(); i++) 
		if (den.compare(elems.at(i).getDen()) == 0)
			elems.erase(elems.begin() + i);

}

vector<Oferta> Repositorry::filtrareDestinatie(string destinatie) {
	vector<Oferta> vect;

	for (auto& elem : Repositorry::getOferte())
		if(&elem != nullptr)
			if (elem.getDest().find(destinatie.c_str()) != -1)
				vect.push_back(elem);
	
	return vect;
}

vector<Oferta> Repositorry::filtrarePret(int pretMaxim) {
	vector<Oferta> vect;

	for (auto& elem : Repositorry::getOferte())
		if(&elem != nullptr)
			if (elem.getPret() <= pretMaxim)
				vect.push_back(elem);
	return vect;
}

bool cmpDenumire(Oferta off1, Oferta off2) {
	return (off1.getDen() < off2.getDen());
}

bool cmpDestinatie(Oferta off1, Oferta off2) {
	return (off1.getDest() < off2.getDest());
}

bool cmpTipPret(Oferta off1, Oferta off2) {

	if (off1.getTip() == off2.getTip())
		return (off1.getPret() < off2.getPret());
	else return (off1.getTip() < off2.getTip());

}

void Repositorry::sortare(bool (*func)(Oferta, Oferta)) {
	if(func != nullptr)
		std::sort(elems.begin(), elems.end(), func);
}

map<string, int> Repositorry::RaportTip() {
	map <string, int> raport;

	for (auto& elem : elems) {
		if (&elem != nullptr) {
			string tip = elem.getTip();
			raport.insert({ tip, 0 });
		}
	}

	for (auto& elem : elems) {
		if (&elem != nullptr) {
			string tip = elem.getTip();
			raport.at(tip)++;
		}
	}

	return raport;
}

void Repositorry::goleste() noexcept {
	elems.clear();
}

void RepositorryFile::loadFromFile() {
	ifstream fin(this->filename);
	if (!fin.is_open())
		throw RepoException("Nu se poate citi din fisierul " + filename);
	string line;
	while (getline(fin, line)) {
		string denumire, destinatie, tip;
		int pret = 0;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ',')) {
			if (item_no == 0)denumire = current_item;
			if (item_no == 1)destinatie = current_item;
			if (item_no == 2)tip = current_item;
			if (item_no == 3)pret = atoi(current_item.c_str());
			item_no++;
		}
		const Oferta oferta(denumire, destinatie, tip, pret);
		Repositorry::adauga(oferta);
	}
	fin.close();
}

void RepositorryFile::storeToFile() {
	ofstream fout(filename);
	for (auto& oferta : getOferte())
		if(&oferta != nullptr)
			fout << oferta.getDen() << ',' << oferta.getDest() << ',' << oferta.getTip() << ',' << oferta.getPret() << "\n";
	fout.close();
}


void exportToCSV(string fname, vector<Oferta> vectorOferte) {
	ofstream fout(fname);
	for(auto& oferta : vectorOferte)
		if(&oferta != nullptr)
			fout << oferta.getDen() << ',' << oferta.getDest() << ',' << oferta.getTip() << ',' << oferta.getPret() << "\n";
	fout.close();
}
