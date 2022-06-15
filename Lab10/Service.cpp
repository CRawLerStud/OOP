#include "Service.h"

void Service::adauga(Oferta oferta) {
	validator.valideazaOferta(oferta);
	repo.adauga(oferta);

	undoActions.push_back(std::make_shared<UndoAdauga>(repo, oferta));
}

vector<Oferta>& Service::Oferte() noexcept {
	return repo.getOferte();
}

void Service::modificareDenumireOferta(string den, string denumireNoua) {
	//Oferta ofertaNoua = repo.find(den); // arunca exceptie daca nu exista
	//ofertaNoua.setDen(denumireNoua);
	Oferta ofertaNoua(denumireNoua, repo.find(den).getDest(), repo.find(den).getTip(), repo.find(den).getPret()); // arunca exceptie daca nu exista
	validator.valideazaOferta(ofertaNoua); // arunca exceptie daca nu este valida oferta cu denumirea Noua
	Oferta ofertaVeche = repo.find(den);
	repo.modificaDenumire(den, ofertaNoua); // arunca exceptie daca exista deja oferta cu denumireaNoua
	//oferta este modificata daca totul a functionat corect

	undoActions.push_back(std::make_shared<UndoModifica>(repo, ofertaVeche, ofertaNoua));
}

void Service::modificareDestinatieOferta(string den, string destinatieNoua) {
	//Oferta ofertaNoua = repo.find(den); // arunca exceptie daca nu exista
	//ofertaNoua.setDest(destinatieNoua);
	Oferta ofertaNoua(repo.find(den).getDen(), destinatieNoua, repo.find(den).getTip(), repo.find(den).getPret());
	validator.valideazaOferta(ofertaNoua); // arunca exceptie daca nu este valida oferta cu denumirea Noua
	Oferta ofertaVeche = repo.find(den);
	repo.modificaOferta(den, ofertaNoua); 

	undoActions.push_back(std::make_shared<UndoModifica>(repo, ofertaVeche, ofertaNoua));
}

void Service::modificareTipOFerta(string den, string tipNou) {
	//Oferta ofertaNoua = repo.find(den);
	//ofertaNoua.setTip(tipNou);
	Oferta ofertaNoua(repo.find(den).getDen(), repo.find(den).getDest(), tipNou, repo.find(den).getPret());
	validator.valideazaOferta(ofertaNoua);
	Oferta ofertaVeche = repo.find(den);
	repo.modificaOferta(den, ofertaNoua);

	undoActions.push_back(std::make_shared<UndoModifica>(repo, ofertaVeche, ofertaNoua));
}

void Service::modificarePretOferta(string den, int pretNou) {
	//Oferta ofertaNoua = repo.find(den);
	//ofertaNoua.setPret(pretNou);
	Oferta ofertaNoua(repo.find(den).getDen(), repo.find(den).getDest(), repo.find(den).getTip(), pretNou);
	validator.valideazaOferta(ofertaNoua);
	Oferta ofertaVeche = repo.find(den);
	repo.modificaOferta(den, ofertaNoua);

	undoActions.push_back(std::make_shared<UndoModifica>(repo, ofertaVeche, ofertaNoua));
}

Oferta Service::gasesteOferta(string den) {
	return repo.find(den); // arunca exceptie daca nu exista
}

void Service::stergeOferta(string den) {
	Oferta ofertaGasita = repo.find(den); // arunca exceptie daca nu exista
	repo.stergeOferta(den); 

	undoActions.push_back(std::make_shared<UndoSterge>(repo, ofertaGasita));
}

vector<Oferta> Service::filtrareDestinatie(string destinatie) {
	return repo.filtrareDestinatie(destinatie);
}

vector<Oferta> Service::filtrarePret(int pret) {
	return repo.filtrarePret(pret);
}

void Service::SortareDenumire() {
	repo.sortare(cmpDenumire);
}

void Service::SortareDestinatie(){
	repo.sortare(cmpDestinatie);
}

void Service::SortareTipPret() {
	repo.sortare(cmpTipPret);
}

void Service::adaugaWishlist(string denumire) {
	Oferta ofertaGasita = repo.find(denumire);
	wishlist.adauga(ofertaGasita);
	notify();
}

void Service::stergeWishlist(string denumire)
{
	Oferta ofertaGasita = repo.find(denumire);
	wishlist.stergeOferta(ofertaGasita.getDen());
	notify();
}

void Service::adaugaRandomWishlist(int n) {
	if (n + wishlist.getOferte().size() > repo.getOferte().size())
		throw RepoException("Numar invalid");
	int i = 1;
	while (i <= n) {
		const int pos = rand() % repo.getOferte().size(); // genereaza un numar intre 0 si numarul de oferte(<nrOff , nu <=nrOff)
		Oferta off = repo.getOferte().at(pos);
		if (wishlist.exists(off) == false) {
			wishlist.adauga(off);
			i++;
		}
	}
	notify();
}

void Service::golesteWishlist() noexcept{
	wishlist.goleste();
	notify();
}

void Service::ExportWishlist(string filename) {
	filename += ".csv";
	exportToCSV(filename, wishlist.getOferte());
}

void Service::undo() {
	if (undoActions.empty())
		throw RepoException("Nu mai exista operatii!");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
