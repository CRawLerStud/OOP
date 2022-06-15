#include "MainTests.h"

void testAll() {
	testRepo();
	testOferta();
	testValidator();
	testService();
	//testVectorDinamicIterator();
	testFiltrare();
	testSortare();
	testWishlist();
	testRaport();
	testUndo();
}

void testRepo() {
	Repositorry repo;
	//testam adaugarea prin intermediul functiei exists
	Oferta oferta1("Denumire", "Barcelona", "City-Break", 1000);
	Oferta oferta2("AltaDenumire", "Bali", "Sejur", 3000);
	repo.adauga(oferta1); // 1
	assert(repo.exists(oferta1));
	repo.adauga(oferta2); // 2
	assert(repo.exists(oferta2));
	Oferta test = repo.find(oferta1.getDen());
	assert(test.equal(oferta1) == true);
	test = repo.find(oferta2.getDen());
	assert(test.equal(oferta2) == true);
	vector<Oferta> testVector = repo.getOferte();
	assert(testVector.size() == 2);
	//testam exceptiile
	try {
		repo.find("ASDASDASDASD");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	try {
		Oferta sameOferta1("Denumire", "Barcelona", "City-Break", 1000);
		repo.adauga(sameOferta1); // 3
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	//testam modificarea
	try {
		Oferta sameOferta1("Denumire", "Barcelona", "City-Break", 1000);
		repo.modificaDenumire("Denumire", sameOferta1);
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element existent!") == 0);
		assert(true);
	}

	Oferta oferta_inlocuitoare("DenumireNoua", "Hawaii", "Sejur", 2099);
	repo.modificaOferta("Denumire", oferta_inlocuitoare);
	assert(repo.exists(oferta_inlocuitoare) == true);
	assert(repo.find("DenumireNoua").getDen().compare("DenumireNoua") == 0);

	try {
		repo.stergeOferta("DenumireInexistenta"); // denumirea nu exista -> arunca RepoException
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}

	repo.stergeOferta("DenumireNoua");//valid
	assert(repo.getOferte().size() == 1);
	repo.stergeOferta("AltaDenumire");
	assert(repo.getOferte().size() == 0);

	remove("teste.csv");
	std::ofstream("teste.csv");
	RepositorryFile repoFile("teste.csv");
	assert(repoFile.getOferte().size() == 0);
	repoFile.adauga(oferta1);
	assert(repoFile.getOferte().size() == 1);
	repoFile.stergeOferta("Denumire");
	assert(repoFile.getOferte().size() == 0);

	repoFile.adauga(oferta1);
	assert(repoFile.getOferte().size() == 1);
	repo.modificaDenumire("Denumire", oferta2);


	remove("teste.csv");

}

void testOferta() {
	//testam getterii si setterii
	Oferta oferta1("Denumire", "Spania", "Excursie", 500);
	assert(oferta1.getDen().compare("Denumire") == 0);
	assert(oferta1.getDest().compare("Spania") == 0);
	assert(oferta1.getTip().compare("Excursie") == 0);
	assert(oferta1.getPret() == 500);
	string denNou = "OfertaNoua";
	oferta1.setDen(denNou);
	assert(oferta1.getDen().compare(denNou) == 0);
	string destNoua = "Italia";
	oferta1.setDest(destNoua);
	assert(oferta1.getDest().compare(destNoua) == 0);
	string tipNou = "City-Break";
	oferta1.setTip(tipNou);
	assert(oferta1.getTip().compare(tipNou) == 0);
	constexpr int pretNou = 1200;
	oferta1.setPret(pretNou);
	assert(oferta1.getPret() == 1200);
	//testam functia de verificare a egalitatii intre doua oferte
	assert(oferta1.equal(oferta1) == true);
	Oferta oferta2("Barosaneala", "Gioconda", "Vasilica", 300);
	assert(oferta1.equal(oferta2) == false);
}

void testValidator() {
	Validator validator;
	Oferta oferta_valida("Denumire", "Barcelona", "CityBreak", 1200);
	validator.valideazaOferta(oferta_valida);
	//nu da nici o exceptie
	string denumire_invalida = "asdasdasd12312----";
	string denumire_invalida2 = "";
	string destinatie_invalida = "123123123";
	string destinatie_invalida2 = "Barcelonaaa1231";
	string destinatie_invalida3 = "";
	string tip_invalid = "";
	string tip_invalid2 = "1231231";
	constexpr int pret_invalid = -100;
	constexpr int pret_invalid2 = 0;

	try {
		Oferta oferta(denumire_invalida, "Barcelona", "CityBreak", 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta(denumire_invalida2, "Barcelona", "CityBreak", 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta("DENUMIRE", destinatie_invalida, "CityBreak", 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta("DENUMIRE", destinatie_invalida2, "CityBreak", 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	
	try {
		Oferta oferta("DENUMIRE", destinatie_invalida3, "CityBreak", 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta("DENUMIRE", "Barcelona", tip_invalid, 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta("DENUMIRE", "Madrid", tip_invalid2, 1200);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta("DENUMIRE", "Madrid", "City", pret_invalid);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		Oferta oferta("DENUMIRE", "Madrid", "City", pret_invalid2);
		validator.valideazaOferta(oferta);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
}

void testService() {
	Repositorry repo;
	Validator validator;
	remove("teste.csv");
	std::ofstream("teste.csv");
	RepositorryFile wishlist("teste.csv");
	Service service(repo, validator, wishlist);

	Oferta oferta_valida("Denumire", "Bali", "Sejur", 1599);
	service.adauga(oferta_valida); // 4

	Oferta oferta_invalida("123123---asdaz**", "123123***sdasda--", "123123918=as-das-d", -100);
	try {
		service.adauga(oferta_invalida); // 5
		assert(false);
	}
	catch (ValidationException& v) {
		assert(v.getErrorMessage() == "Oferta invalida!");
	}
	Oferta same_oferta("Denumire", "Bali", "Sejureala", 2099);
	try {
		service.adauga(same_oferta); // 6
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.getErrorMessage() == "Element existent!");
	}

	vector<Oferta> oferteAll = service.Oferte();
	assert(oferteAll.size() == 1);
	assert(oferteAll.at(0).getPret() == 1599);
	assert(oferteAll.at(0).getDest().compare("Bali") == 0);
	assert(oferteAll.at(0).getDen().compare("Denumire") == 0);
	assert(oferteAll.at(0).getTip().compare("Sejur") == 0);
	
	//testam modificarea
	service.modificareDenumireOferta("Denumire", "DenumireNoua");
	assert(repo.exists(repo.find("DenumireNoua")) == true);
	try {
		repo.find("Denumire");
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}
	try {
		service.modificareDenumireOferta("DenumireNoua", "=======");
		assert(false);
	}
	catch (ValidationException& v) {
		assert(v.getErrorMessage().compare("Oferta invalida!") == 0);
	}

	service.modificareDestinatieOferta("DenumireNoua", "PiatraNeamt");
	assert(repo.find("DenumireNoua").getDest() == "PiatraNeamt");
	try {
		service.modificareDestinatieOferta("Vasilica", "PiatraCraiului"); // nu exista Vasilica
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}
	try {
		service.modificareDestinatieOferta("DenumireNoua", "DestinatieNoua1231--=="); // invalida destinatia
		assert(false);
	}
	catch (ValidationException& v) {
		assert(v.getErrorMessage().compare("Oferta invalida!") == 0);
	}

	service.modificareTipOFerta("DenumireNoua", "Vaporeala");
	assert(repo.getOferte().at(0).getTip().compare("Vaporeala") == 0);

	try {
		service.modificareTipOFerta("DenumireFalsaInexistenta", "Vaporeala");
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}

	try {
		service.modificareTipOFerta("DenumireNoua", "1231231---====");
		assert(false);
	}
	catch (ValidationException& v) {
		assert(v.getErrorMessage().compare("Oferta invalida!") == 0);
	}

	service.modificarePretOferta("DenumireNoua", 5000);
	assert(repo.find("DenumireNoua").getPret() == 5000);
	try {
		service.modificarePretOferta("INEXISTENT", 1200); // inexistent
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}
	try {
		service.modificarePretOferta("DenumireNoua", -1000); //invalid
		assert(false);
	}
	catch (ValidationException& v) {
		assert(v.getErrorMessage().compare("Oferta invalida!") == 0);
	}

	//testare cautare & stergere

	Oferta ofertaCautare("Oferta1", "Madrid", "Luxury", 1200);
	service.adauga(ofertaCautare); // 7
	Oferta ofertaGasita = service.gasesteOferta("Oferta1"); // valid si exista
	assert(ofertaGasita.getDen().compare("Oferta1") == 0);

	try {
		service.gasesteOferta("OfertaInexistentaSiSmechera"); // inexistent
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}

	try {
		service.stergeOferta("OfertaInexistentaSiJMEKERA"); // inexistent
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
	}
	service.stergeOferta("Oferta1"); // se sterge
	assert(service.Oferte().size() == 1);
	service.undo();
	assert(service.Oferte().size() == 2);

	remove("teste.csv");
	std::ofstream("teste.csv");
	RepositorryFile repoTeste("teste.csv");
	Oferta oferta("Denumire1", "Barcelona", "CityBreak", 1500);
	repoTeste.adauga(oferta);
	Oferta ofertaNoua1("City1", "Villareal", "CityBreak", 1500);
	repoTeste.modificaDenumire("Denumire1", ofertaNoua1);
	Oferta ofertaNoua2("City1", "Villareal", "CityBreak", 1500);
	repoTeste.modificaOferta("City1", ofertaNoua2);
	assert(repoTeste.getOferte().at(0).getDen() == "City1");
	assert(repoTeste.getOferte().at(0).getDest() == "Villareal");
	for (int i = 1; i <= 50; i++) {
		try {
			service.undo();
		}
		catch(RepoException& r) {
			assert(r.getErrorMessage() == "Nu mai exista operatii!");
		}
	}
	remove("teste.csv");
}

/*
void testVectorDinamicIterator() {
	VectorDinamic<int> vect;
	vect.addElement(10);
	assert(vect.getElem(0) == 10);
	vect.addElement(20);
	assert(vect.getElem(1) == 20);
	assert(vect.size() == 2);
	vect.set(0, 100);
	assert(vect.getElem(0) == 100);
	vect.addElement(20);
	vect.addElement(20);
	vect.addElement(20);
	vect.addElement(20);
	vect.addElement(20);
	assert(vect.size() == 7);
	
	Iterator<int> iter(vect);
	assert(iter.valid() == true);
	assert(iter.element() == 100);
	iter.next();
	assert(iter.element() == 20);
	iter.operator++();
	assert(iter.element() == 20);

	Iterator<int> iter2 = vect.end();
	assert(iter2.operator!=(vect.begin()));

	assert(iter.operator*());

}
*/
void testFiltrare() {
	Repositorry repo;
	Oferta oferta1("City1", "Barcelona", "CityBreak", 100);
	Oferta oferta2("City2", "Valencia", "CityBreak", 150);
	Oferta oferta3("City3", "Venetia", "CityBreak", 300);

	repo.adauga(oferta1);
	repo.adauga(oferta2);
	repo.adauga(oferta3);

	vector<Oferta> oferteGasite = repo.filtrareDestinatie("Barcelona");
	assert(oferteGasite.size() == 1);
	assert(oferteGasite.at(0).getDest().compare("Barcelona") == 0);
	assert(oferteGasite.at(0).getPret() == 100);

	oferteGasite = repo.filtrarePret(150);
	assert(oferteGasite.size() == 2);
	assert(oferteGasite.at(0).getPret() <= 150);
	assert(oferteGasite.at(1).getPret() <= 150);

	Validator valid;
	remove("teste.csv");
	std::ofstream("teste.csv");
	RepositorryFile wishlist("teste.csv");
	Service service(repo, valid, wishlist);

	assert(service.filtrareDestinatie("V").size() == 2);
	assert(service.filtrareDestinatie("B").size() == 1);
	assert(service.filtrarePret(150).size() == 2);

	remove("teste.csv");
}

void testSortare() {
	Repositorry repo;
	Validator valid; 
	remove("teste.csv");
	std::ofstream("teste.csv");
	RepositorryFile wishlist("teste.csv");
	Service service(repo, valid, wishlist);

	Oferta oferta1("Denumire1", "Destinatie", "Tip", 100);
	Oferta oferta2("City1", "Madrid", "CityBreak", 250);
	Oferta oferta3("Sejur1", "Bangkok", "Sejur", 350);
	Oferta oferta4("City2", "Barcelona", "CityBreak", 150);
	Oferta oferta5("City3", "PiatraNeamt", "SejurLux", 10000);

	service.adauga(oferta1);
	service.adauga(oferta2);
	service.adauga(oferta3);
	service.adauga(oferta4);
	service.adauga(oferta5);

	service.SortareDenumire();
	assert(repo.getOferte().at(0).getDen().compare("City1") == 0);
	assert(repo.getOferte().at(1).getDen().compare("City2") == 0);

	service.SortareDestinatie();
	assert(repo.getOferte().at(0).getDest().compare("Bangkok") == 0);
	assert(repo.getOferte().at(1).getDest().compare("Barcelona") == 0);

	service.SortareTipPret();
	assert(repo.getOferte().at(0).getTip().compare("CityBreak") == 0);
	assert(repo.getOferte().at(0).getPret() == 150);
	remove("teste.csv");
}

void testWishlist() {
	Repositorry wishlist;
	assert(wishlist.getOferte().size() == 0);
	Repositorry repo;
	
	Oferta oferta1("City1", "Barcelona", "CityBreak", 1200);
	Oferta oferta2("City2", "Venetia", "CityBreak", 1500);
	Oferta oferta3("Sejur1", "Bangkok", "Sejur", 2500);
	repo.adauga(oferta1);
	repo.adauga(oferta2);
	repo.adauga(oferta3);

	wishlist.adauga(repo.find("City1"));
	try {
		wishlist.adauga(repo.find("vasilica"));
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage() == "Element inexistent!");
	}
	assert(wishlist.exists(wishlist.find("City1")));

	try {
		wishlist.adauga(repo.find("City1"));
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage() == "Element existent!");
	}

	assert(wishlist.exists(repo.find("Sejur1")) == false);

	assert(wishlist.getOferte().size() == 1);
	assert(wishlist.getOferte().at(0).getDen() == "City1");

	wishlist.goleste();
	assert(wishlist.getOferte().size() == 0);
	
	Validator validator;
	Service service(repo, validator, wishlist);
	service.adaugaWishlist("City1");
	assert(service.getWishlist().getOferte().size() == 1);
	service.golesteWishlist();
	assert(service.getWishlist().getOferte().size() == 0);
	service.adaugaRandomWishlist(1);
	assert(service.getWishlist().getOferte().size() == 1);
	try {
		service.adaugaRandomWishlist(3);
		assert(false);
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage() == "Numar invalid");
	}

	assert(repo.getOferte().size() == 3);

	service.ExportWishlist("teste.csv");

	assert(repo.exists(oferta1));

}

void testRaport() {
	Repositorry repo;
	Oferta oferta1("City1", "Vaslui", "Sejur", 1500);
	Oferta oferta2("City2", "Iasi", "CityBreak", 2500);
	Oferta oferta3("City3", "Bangkok", "Sejur", 1200);
	Oferta oferta4("City4", "Paris", "CityBreak", 3000);
	Oferta oferta5("City5", "Bejing", "Sejur", 4500);

	repo.adauga(oferta1);
	repo.adauga(oferta2);
	repo.adauga(oferta3);
	repo.adauga(oferta4);
	repo.adauga(oferta5);

	map<string, int> raport = repo.RaportTip();

	assert(raport.at("CityBreak") == 2);
	assert(raport.at("Sejur") == 3);

	Validator valid;
	remove("teste.csv");
	std::ofstream("teste.csv");
	RepositorryFile wishlist("teste.csv");
	Service service(repo, valid, wishlist);

	map<string, int> raportService = service.RaportTip();
	assert(raportService.size() == 2);
	assert(raportService.at("CityBreak") == 2);
	assert(raportService.at("Sejur") == 3);
	remove("teste.csv");
}

void testUndo() {
	Repositorry repo;
	Validator validator;
	Repositorry wishlist;
	Service service(repo, validator, wishlist);

	Oferta oferta1("City1", "Villareal", "CityBreak", 2500);
	Oferta oferta2("City2", "Bilbao", "CityBreak", 3000);
	Oferta oferta3("Sejur3", "Bangkok", "Sejur", 5500);

	service.adauga(oferta1);
	service.modificareDenumireOferta("City1", "City2");
	assert(service.Oferte().at(0).getDen() == "City2");
	service.undo();
	assert(service.Oferte().at(0).getDen() == "City1");
	service.undo();
	assert(service.Oferte().size() == 0);

}