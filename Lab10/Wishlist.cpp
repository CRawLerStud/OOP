#include "Wishlist.h"

void Wishlist::addOferta(Repositorry& repo, string denumire) {
	Oferta off = repo.find(denumire); // poate arunca RepoException("Element inexistent!")
	for (const auto& elem : wElems)
		if(&elem != nullptr)
			if (elem.getDen() == denumire)
				throw RepoException("Element existent!");
	wElems.push_back(off);
}

void Wishlist::goleste() noexcept{
	wElems.clear();
}

bool Wishlist::exists(string denumire){
	for (auto& element : wElems)
		if (&element != nullptr)
			if (element.getDen().compare(denumire) == 0)
				return true;
	return false;
}

void Wishlist::addRandom(Repositorry& repo, int n) {
	int i = 1;
	while( i <= n ){
		const int pos = rand() % repo.getOferte().size(); // genereaza un numar intre 0 si numarul de oferte(<nrOff , nu <=nrOff)
		Oferta off = repo.getOferte().at(pos);
		if (exists(off.getDen()) == false) {
			wElems.push_back(off);
			i++;
		}
	}
}

void Wishlist::exportWishlist(Repositorry& repo, string filename) {
	ofstream fout(filename);
	if (!fout.is_open())
		throw RepoException("Nu se poate deschide fisierul " + filename);
	for (auto& oferta : repo.getOferte()) 
		if(&oferta != nullptr)
			fout << oferta.getDen() << "," << oferta.getDest() << "," << oferta.getTip() << "," << oferta.getPret() << "\n";
	fout.close();
}