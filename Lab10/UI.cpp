#include "UI.h"



void UI::begin_print() {
	cout << "*************************AGENTIA DE TURISM TOFAN*************************\n";
	cout << "**                           BINE ATI VENIT!                           **\n";
	cout << "**                                                                     **\n";
	cout << "**                                                                     **\n";
	cout << "**********************************MENIU**********************************\n";
	cout << "** 15 -  Undo                                                          **\n";
	cout << "** 14 -  Export Wishlist(format .csv automat)                          **\n";
	cout << "** 13 -  Raport Tip                                                    **\n";
	cout << "** 12 -  Goleste Wishlist-ul                                           **\n";
	cout << "** 11 -  Adauga n Oferte random in Wishlist                            **\n";
	cout << "** 10 -  Adauga Oferta in Wishlist                                     **\n";
	cout << "** 9  -  Afiseaza Wishlist-ul                                          **\n";
	cout << "** 8  -  Sortare repositorry(denumire, destinatie, tip+pret)           **\n";
	cout << "** 7  -  Filtrare destinatie/pret                                      **\n";
	cout << "** 6  -  Sterge o oferta                                               **\n";
	cout << "** 5  -  Gaseste oferta(dupa denumire)                                 **\n";
	cout << "** 4  -  Adauga 10 oferte (DEBUGGING)                                  **\n";
	cout << "** 3  -  Modifica oferta existenta(denumire, destinatie, tip, pret)    **\n";
	cout << "** 2  -  Afisati ofertele disponibile                                  **\n";
	cout << "** 1  -  Adaugati O Oferta                                             **\n";
	cout << "** 0  -  Parasiti aplicatia                                            **\n";
	cout << "*************************************************************************\n";

}

void UI::print_menu() {
	cout << "**********************************MENIU**********************************\n";
	cout << "** 15 -  Undo                                                          **\n";
	cout << "** 14 -  Export Wishlist(format .csv automat)                          **\n";
	cout << "** 13 -  Raport Tip                                                    **\n";
	cout << "** 12 -  Goleste Wishlist-ul                                           **\n";
	cout << "** 11 -  Adauga n Oferte random in Wishlist                            **\n";
	cout << "** 10 -  Adauga Oferta in Wishlist                                     **\n";
	cout << "** 9  -  Afiseaza Wishlist-ul                                          **\n";
	cout << "** 8  -  Sortare repositorry(denumire, destinatie, tip+pret)           **\n";
	cout << "** 7  -  Filtrare destinatie/pret                                      **\n";
	cout << "** 6  -  Sterge o oferta                                               **\n";
	cout << "** 5  -  Gaseste oferta(dupa denumire)                                 **\n";
	cout << "** 4  -  Adauga 10 oferte (DEBUGGING)                                  **\n";
	cout << "** 3  -  Modifica oferta existenta(denumire, destinatie, tip, pret)    **\n";
	cout << "** 2  -  Afisati ofertele disponibile                                  **\n";
	cout << "** 1  -  Adaugati O Oferta                                             **\n";
	cout << "** 0  -  Parasiti aplicatia                                            **\n";
	cout << "*************************************************************************\n";
}

void UI::exit_print() {
	cout << "*************************AGENTIA DE TURISM TOFAN*************************\n";
	cout << "**                            SE PARASESTE...                          **\n";
	cout << "**                                                                     **\n";
	cout << "*************************************************************************\n";
}

void UI::UI_AddOferta() {
	//denumire, destinatie, tip, pret
	string denumire, destinatie, tip;
	int pret;
	cout << "** Introduceti denumirea ofertei: ";
	cin >> denumire;

	cout << "** Introduceti destinatia ofertei: ";
	cin >> destinatie;

	cout << "** Introduceti tipul ofertei: ";
	cin >> tip;

	cout << "** Introduceti pretul ofertei: ";
	cin >> pret;

	Oferta oferta(denumire, destinatie, tip, pret);

	try {
		service.adauga(oferta);
		cout << "** Oferta a fost introdusa cu succes!" << std::endl;
	}
	catch (RepoException& re) {
		cout << "** Repositorry Exception: " << re.getErrorMessage() << endl;
	}
	catch (ValidationException& v) {
		cout << "** Validation Exception: " << v.getErrorMessage() << endl;
	}
}

void UI::UI_PrintOferte(vector<Oferta>& oferte) {

	if (oferte.size() == 0) {
		cout << "** Nu exista oferte introduse!\n";
		return;
	}
	printf("%20s | %20s | %15s | %8s\n", "Denumire", "Destinatie", "Tip", "Pret");

	for (const auto& pachet : oferte)
		if(&pachet != nullptr)
			printf("%20s | %20s | %15s | %8d\n", pachet.getDen().c_str(), pachet.getDest().c_str(), pachet.getTip().c_str(), pachet.getPret());
}

void UI::UI_ModificaOferta() {
	string denumire;
	cout << "** Introduceti denumirea ofertei: ";
	cin >> denumire;
	string camp;
	cout << "** Introduceti numele campului care trebuie modificat(denumire, destinatie, tip, pret): ";
	cin >> camp;
	if (camp.compare("denumire") == 0) {
		string denumireNoua;
		cout << "** Introduceti noua denumire: ";
		cin >> denumireNoua;
		try {
			service.modificareDenumireOferta(denumire, denumireNoua);
			cout << "** Oferta a fost modificata!" << endl;
		}
		catch (RepoException& r) {
			cout << "** RepoException: " << r.getErrorMessage() << endl;
			assert(true);
		}
		catch (ValidationException& v) {
			cout << "** ValidationException: " << v.getErrorMessage() << endl;
			assert(true);
		}
	}
	if (camp.compare("destinatie") == 0) {
		string destinatieNoua;
		cout << "** Introduceti noua destinatie: ";
		cin >> destinatieNoua;
		try {
			service.modificareDestinatieOferta(denumire, destinatieNoua);
			cout << "** Oferta a fost modificata!" << endl;
		}
		catch (RepoException& r) {
			cout << "** RepoException: " << r.getErrorMessage() << endl;
			assert(true);
		}
		catch (ValidationException& v) {
			cout << "** ValidationException: " << v.getErrorMessage() << endl;
			assert(true);
		}
	}
	if (camp.compare("tip") == 0) {
		string tipNou;
		cout << "** Introduceti noul tip: ";
		cin >> tipNou;
		try {
			service.modificareTipOFerta(denumire, tipNou);
			cout << "** Oferta a fost modificata!" << endl;
		}
		catch (RepoException& r) {
			cout << "** RepoException: " << r.getErrorMessage() << endl;
			assert(true);
		}
		catch (ValidationException& v) {
			cout << "** ValidationException: " << v.getErrorMessage() << endl;
			assert(true);
		}
	}
	if (camp.compare("pret") == 0) {
		int pretNou;
		cout << "** Introduceti noul pret: ";
		cin >> pretNou;
		try {
			service.modificarePretOferta(denumire, pretNou);
			cout << "** Oferta a fost modificata!" << endl;
		}
		catch (RepoException& r) {
			cout << "** RepoException: " << r.getErrorMessage() << endl;
			assert(true);
		}
		catch (ValidationException& v) {
			cout << "** ValidationException: " << v.getErrorMessage() << endl;
			assert(true);
		}
	}
}

void UI::UI_AdaugaOferteDebug() {

	Oferta oferta1("City1", "Barcelona", "CityBreak", 1200);
	Oferta oferta2("City2", "Valencia", "CityBreak", 800);
	Oferta oferta3("City3", "Viena", "CityBreak", 1300);
	Oferta oferta4("City4", "Venetia", "CityBreak", 2000);
	Oferta oferta5("Sejur1", "Atena", "Sejur", 2500);
	Oferta oferta6("Sejur2", "Bangkok", "Sejur", 3000);
	Oferta oferta7("Sejur3", "Tokyo", "Sejur", 4000);
	Oferta oferta8("Sejur4", "BuenosAires", "Sejur", 5000);
	Oferta oferta9("Sejur5", "Reykjavik", "Sejur", 2500);
	Oferta oferta10("City5", "Cairo", "CityBreak", 2000);

	try {
		service.adauga(oferta1);
		service.adauga(oferta2);
		service.adauga(oferta3);
		service.adauga(oferta4);
		service.adauga(oferta5);
		service.adauga(oferta6);
		service.adauga(oferta7);
		service.adauga(oferta8);
		service.adauga(oferta9);
		service.adauga(oferta10);
	}
	catch (RepoException&) {
		cout << "** (DEBUG)Au fost adaugate deja ofertele pentru debug!\n";
		return;
	}

	cout << "** (DEBUG)10 Oferte au fost adaugate in baza de date!\n";
}

void UI::UI_FindOferta() {
	string denumire;
	cout << "** Introduceti denumirea: ";
	cin >> denumire;
	try {
		Oferta ofertaGasita = service.gasesteOferta(denumire);
		printf("%20s | %20s | %15s | %8s\n", "Denumire", "Destinatie", "Tip", "Pret");
		printf("%20s | %20s | %15s | %8d\n", ofertaGasita.getDen().c_str(), ofertaGasita.getDest().c_str(), ofertaGasita.getTip().c_str(), ofertaGasita.getPret());
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
		cout << "** Nu exista oferta cu denumirea introdusa!" << endl;
	}
}

void UI::UI_StergeOferta() {
	string denumire;
	cout << "** Introduceti denumirea ofertei: ";
	cin >> denumire;
	try {
		service.stergeOferta(denumire);
		cout << "** Oferta a fost stearsa!" << endl;
	}
	catch (RepoException& r) {
		assert(r.getErrorMessage().compare("Element inexistent!") == 0);
		cout << "** Nu exista nici o oferta cu denumirea introdusa!" << endl;
	}
}

void UI::UI_Filtrare() {
	cout << "** Introduceti filtrul (destinatie/pret): ";
	string metoda;
	cin >> metoda;
	if (metoda.compare("destinatie") == 0) {
		string destinatie;
		cout << "** Introduceti destinatia cautata: ";
		cin >> destinatie;
		vector<Oferta> vect = service.filtrareDestinatie(destinatie);
		printf("%20s | %20s | %15s | %8s\n", "Denumire", "Destinatie", "Tip", "Pret");
		for(auto& elem : vect)
			if(&elem != nullptr)
				printf("%20s | %20s | %15s | %8d\n", elem.getDen().c_str(), elem.getDest().c_str(), elem.getTip().c_str(), elem.getPret());

	}
	else if (metoda.compare("pret") == 0) {
		int pret;
		cout << "** Introduceti pretul maxim: ";
		cin >> pret;
		vector<Oferta> vect = service.filtrarePret(pret);
		printf("%20s | %20s | %15s | %8s\n", "Denumire", "Destinatie", "Tip", "Pret");
		for (auto& elem : vect)
			if(&elem != nullptr)
				printf("%20s | %20s | %15s | %8d\n", elem.getDen().c_str(), elem.getDest().c_str(), elem.getTip().c_str(), elem.getPret());
	}
	else cout << "** Filtru necunoscut!\n";
}

void UI::UI_Sortare() {
	string mod;
	cout << "** Introduceti modul de sortare(denumire, destinatie, tip+Pret): ";
	cin >> mod;
	if (mod.compare("denumire") == 0) {
		service.SortareDenumire();
		UI_PrintOferte(service.Oferte());
	}
	else if (mod.compare("destinatie") == 0) {
		service.SortareDestinatie();
		UI_PrintOferte(service.Oferte());
	}
	else if (mod.compare("tip+Pret") == 0) {
		service.SortareTipPret();
		UI_PrintOferte(service.Oferte());
	}
	else cout << "** Mod necunoscut!\n";
}

void UI::UI_PrintWishlist() {
	if (service.getWishlist().getOferte().size() == 0) {
		cout << "** Nu exista oferte in wishlist!\n";
		return;
	}
	printf("%20s | %20s | %15s | %8s\n", "Denumire", "Destinatie", "Tip", "Pret");
	for(auto& elem : service.getWishlist().getOferte())
		if(&elem != nullptr)
			printf("%20s | %20s | %15s | %8d\n", elem.getDen().c_str(), elem.getDest().c_str(), elem.getTip().c_str(), elem.getPret());
}

void UI::UI_AddWishlist() {
	string denumire;
	cout << "** Introduceti denumirea: ";
	cin >> denumire;
	try {
		service.adaugaWishlist(denumire);
		cout << "** Oferta cu denumirea '" << denumire << "' a fost introdusa in Wishlist!\n";
	}
	catch (RepoException& r) {
		cout << "** Oferta cu denumirea '" << denumire << "' exista deja in wishlist sau nu exista in baza de date!\n";
		assert(r.getErrorMessage() == "Element inexistent!" || r.getErrorMessage() == "Element existent!");
	}
}

void UI::UI_RaportTip() {
	map<string, int> raport = service.RaportTip();
	if (raport.size() == 0) {
		cout << "** Nu exista oferte introduse!\n";
		return;
	}
	for (auto& elem : raport) {
		if (&elem != nullptr)
			cout << "** " << elem.first << ' ' << elem.second << endl;
	}
}

void UI::UI_AddRandom() {
	int n;
	cout << "** Introduceti numarul de oferte: ";
	cin >> n;
	try {
		service.adaugaRandomWishlist(n);
		cout <<"** " << n << " oferte au fost adaugate cu succes in wishlist!\n";
	}
	catch(RepoException& r) {
		cout << "** Numarul introdus nu este valid! ( nu se pot adauga inca n oferte in wishlist)\n";
		assert(r.getErrorMessage() == "Numar invalid");
	}
}

void UI::UI_WishlistGoleste() {
	service.golesteWishlist();
	cout << "** Wishlist-ul a fost golit!\n";
}

void UI::UI_ExportWishlist() {

	if (service.getWishlist().getOferte().size() == 0) {
		cout << "** Cosul dumneavoastra este gol!\n";
		return;
	}

	cout << "** Introduceti numele fisierului ( in care se salveaza wishlist-ul ): ";
	string filename;
	cin >> filename;

	try {
		service.ExportWishlist(filename + ".csv");
		cout << "** Wishlist-ul a fost exportat in fisierul " << filename << endl;
	}
	catch (RepoException& r) {
		cout << "** RepoException " << r.getErrorMessage() << endl;
	}
	return;
}

void UI::UI_undo() {
	try {
		service.undo();
		cout << "** Undo efectuat\n";
	}
	catch (RepoException& r) {
		cout << "** " << r.getErrorMessage() << endl;
	}
}

void UI::run() {

	begin_print();
	while (true) {
		int situation = 0;
		cout << "** Input: ";
		cin >> situation;

		switch (situation) {
		case 0:
			exit_print();
			return;
		case 1:
			UI_AddOferta();
			break;
		case 2:
			UI_PrintOferte(service.Oferte());
			break;
		case 3:
			UI_ModificaOferta();
			break;
		case 4:
			UI_AdaugaOferteDebug();
			break;
		case 5:
			UI_FindOferta();
			break;
		case 6:
			UI_StergeOferta();
			break;
		case 7:
			UI_Filtrare();
			break;
		case 8:
			UI_Sortare();
			break;
		case 9:
			UI_PrintWishlist();
			break;
		case 10:
			UI_AddWishlist();
			break;
		case 11:
			UI_AddRandom();
			break;
		case 12:
			UI_WishlistGoleste();
			break;
		case 13:
			UI_RaportTip();
			break;
		case 14:
			UI_ExportWishlist();
			break;
		case 15:
			UI_undo();
			break;
		default:
			cout << "** Comanda introdusa nu este cunoscuta!\n";
			break;
		}
		print_menu();
	}
}