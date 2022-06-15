#include "AgentieGUI.h"
#include "Oferta.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include <qdebug.h>
#include <string>
#include <algorithm>

void AgentieGUI::initGUICmps() {
	setLayout(lyMain);
	setWindowTitle("Agentie Turism Tofan");

	//construim widget-ul din stanga
	//lst = new QListWidget();
	
	QWidget* widgetStanga = new QWidget();
	QVBoxLayout* layoutStanga = new QVBoxLayout();
	layoutStanga->addWidget(tableOferte);
	widgetStanga->setLayout(layoutStanga);

	//crearea primei linii de butoane ( sort )
	QWidget* sortWidget = new QWidget();
	QHBoxLayout* sortLayout = new QHBoxLayout();
	sortWidget->setLayout(sortLayout);
	btnSortByDenumire = new QPushButton("Sort Denumire");
	btnSortByDestinatie = new QPushButton("Sort Destinatie");
	btnSortByTipPret = new QPushButton("Sort Tip+Pret");
	sortLayout->addWidget(btnSortByDenumire);
	sortLayout->addWidget(btnSortByDestinatie);
	sortLayout->addWidget(btnSortByTipPret);
	layoutStanga->addWidget(sortWidget);

	//crearea setului de butoane wishlist menu si raportTip
	QWidget* lastStanga = new QWidget();
	QHBoxLayout* lastLayout = new QHBoxLayout();
	lastStanga->setLayout(lastLayout);
	btnWishlist = new QPushButton("Wishlist");
	btnRaportTip = new QPushButton("Raport Tip");
	lastLayout->addWidget(btnWishlist);
	lastLayout->addWidget(btnRaportTip);
	layoutStanga->addWidget(lastStanga);

	layoutStanga->addWidget(btnHistogram);

	//crearea widget dreapta cu form layout
	QWidget* widgetDreapta = new QWidget();
	QFormLayout* layoutDreapta = new QFormLayout();
	widgetDreapta->setLayout(layoutDreapta);

	QLabel* denumireLabel = new QLabel("Denumire");
	QLabel* destinatieLabel = new QLabel("Destinatie");
	QLabel* tipLabel = new QLabel("Tip");
	QLabel* pretLabel = new QLabel("Pret");
	txtDenumire = new QLineEdit();
	txtDestinatie = new QLineEdit();
	txtTip = new QLineEdit();
	txtPret = new QLineEdit();
	layoutDreapta->addRow(denumireLabel, txtDenumire);
	layoutDreapta->addRow(destinatieLabel, txtDestinatie);
	layoutDreapta->addRow(tipLabel, txtTip);
	layoutDreapta->addRow(pretLabel, txtPret);

	//addbutton, stergebutton, modificabutton
	QWidget* amsWidget = new QWidget();
	QHBoxLayout* amsLayout = new QHBoxLayout();
	amsWidget->setLayout(amsLayout);
	btnAdd = new QPushButton("Adauga");
	btnModificare = new QPushButton("Modifica");
	btnStergere = new QPushButton("Sterge");
	amsLayout->addWidget(btnAdd);
	amsLayout->addWidget(btnModificare);
	amsLayout->addWidget(btnStergere);
	layoutDreapta->addRow(amsWidget);

	//undo button, addWishlistButton
	QWidget* undoWidget = new QWidget();
	QVBoxLayout* undoLayout = new QVBoxLayout();
	undoWidget->setLayout(undoLayout);
	btnUndo = new QPushButton("Undo");
	btnAddWishlist = new QPushButton("Adaugare Wishlist");
	undoLayout->addWidget(btnUndo);
	undoLayout->addWidget(btnAddWishlist);
	layoutDreapta->addRow(undoWidget);
	
	//filtrare
	QWidget* filtrareWidget = new QWidget();
	QHBoxLayout* filtrareLayout = new QHBoxLayout();
	filtrareWidget->setLayout(filtrareLayout);
	btnFiltrareDestinatie = new QPushButton("Filtrare Destinatie");
	QObject::connect(btnFiltrareDestinatie, &QPushButton::clicked, [&]() {
		qDebug() << "Filtrare dupa destinatie";
		auto destinatie = txtDestinatie->text().toStdString();
		reloadList(lst, service.filtrareDestinatie(destinatie));
	});
	btnFiltrarePret = new QPushButton("Filtrare Pret");
	QObject::connect(btnFiltrarePret, &QPushButton::clicked, [&]() {
		try {
			qDebug() << "Filtrare dupa pret!";
			auto pret = txtPret->text().toStdString();
			reloadList(lst, service.filtrarePret(std::stoi(pret)));
		}
		catch (const std::invalid_argument& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
		catch (const std::out_of_range& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
		}
	});
	filtrareLayout->addWidget(btnFiltrareDestinatie);
	filtrareLayout->addWidget(btnFiltrarePret);
	layoutDreapta->addRow(filtrareWidget);

	QWidget* OferteWidget = new QWidget();
	QVBoxLayout* OferteLayout = new QVBoxLayout();
	OferteWidget->setLayout(OferteLayout);
	btnOferte = new QPushButton("Oferte");
	OferteLayout->addWidget(btnOferte);
	layoutDreapta->addRow(OferteWidget);


	lyMain->addWidget(widgetStanga);
	lyMain->addWidget(widgetDreapta);

	btnDyn->setLayout(lyBtnDy);
	lyMain->addWidget(btnDyn);
}

void AgentieGUI::connectSignalsSlots() {

	QObject::connect(btnHistogram, &QPushButton::clicked, [&]() {
		HistogramGUI* histogram = new HistogramGUI(service);
		histogram->show();
	});

	QObject::connect(btnOferte, &QPushButton::clicked, [&]() {
		qDebug() << "Inlocuire oferte!";
		reloadList(lst, service.Oferte());
	});

	QObject::connect(btnSortByDenumire, &QPushButton::clicked, [&]() {
		qDebug() << "Am pornit sortarea dupa denumire!";
		service.SortareDenumire();
		reloadList(lst, service.Oferte());
	});
	
	QObject::connect(btnSortByDestinatie, &QPushButton::clicked, [&]() {
		qDebug() << "Am pornit sortarea dupa destinatie!";
		service.SortareDestinatie();
		reloadList(lst, service.Oferte());
	});
	
	QObject::connect(btnSortByTipPret, &QPushButton::clicked, [&]() {
		qDebug() << "Am pornit sortarea dupa tip si pret!";
		service.SortareTipPret();
		reloadList(lst, service.Oferte());
	});

	QObject::connect(btnRaportTip, &QPushButton::clicked, [&]() {
		qDebug() << "Am pornit raportarea dupa tip!";
		QString mesaj = "";
		map<string, int> raport = service.RaportTip();
		for (const auto& o : raport) {
			mesaj.append(QString::fromStdString(o.first));
			mesaj.append(": ");
			mesaj.append(QString::fromStdString(std::to_string(o.second)));
			mesaj.append("\n");
		}
		QMessageBox::information(nullptr, "Raport Tip Info", mesaj);
	});

	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		qDebug() << "Am pornit undo!";
		try {
			service.undo();
		}
		catch (RepoException& r) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(r.getErrorMessage()));
		}
		reloadList(lst, service.Oferte());
	});

	QObject::connect(btnAddWishlist, &QPushButton::clicked, [&]() {
		qDebug() << "Am pornit add wishlist!";
		try {
			auto denumire = txtDenumire->text().toStdString();
			service.adaugaWishlist(denumire);
			QMessageBox::information(nullptr, "Info", QString::fromStdString("Oferta a fost introdusa in wishlist-ul dumneavoastra!"));
		}
		catch (RepoException& r) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(r.getErrorMessage()));
		}
	});


	
	QObject::connect(btnAdd, &QPushButton::clicked, this, &AgentieGUI::addnewOferta);

	QObject::connect(btnModificare, &QPushButton::clicked, this, &AgentieGUI::modificaOferta);

	QObject::connect(btnStergere, &QPushButton::clicked, this, &AgentieGUI::stergeOferta);

	QObject::connect(btnWishlist, &QPushButton::clicked, this, &AgentieGUI::Wishlist);
	
	/*
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtDenumire->setText("");
			txtDestinatie->setText("");
			txtTip->setText("");
			txtPret->setText("");
		}
		else {
			auto selItem = sel.at(0);

			auto denumire = selItem->text();
			txtDenumire->setText(denumire);
			
			qDebug() << "Oferta cu denumirea " << denumire << " se cauta!";

			auto o = service.gasesteOferta(denumire.toStdString());
			auto destinatie = QString::fromStdString(o.getDest());
			auto tip = QString::fromStdString(o.getTip());
			txtPret->setText(QString::number(o.getPret()));
			txtDestinatie->setText(destinatie);
			txtTip->setText(tip);
		}
	});
	*/
}

void AgentieGUI::addnewOferta() {
	try {
		Oferta oferta(txtDenumire->text().toStdString(), txtDestinatie->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toInt());
		service.adauga(oferta);
		reloadList(lst, service.Oferte());
	}
	catch (ValidationException& v) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(v.getErrorMessage()));
	}
	catch (RepoException& r) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(r.getErrorMessage()));
	}
}

void AgentieGUI::modificaOferta() {
	if (txtDenumire->text().toStdString() == "")
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti un nume!"));
		return;
	}
	try {
		qDebug() << "Se cauta oferta";
		auto denumire = txtDenumire->text().toStdString();
		Oferta oferta = service.gasesteOferta(denumire);
		auto destinatie = txtDestinatie->text().toStdString();
		auto tip = txtTip->text().toStdString();
		string pret = txtPret->text().toStdString();
		if (destinatie == oferta.getDest() && tip == oferta.getTip() && std::stoi(pret) == oferta.getPret())
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString("Nimic de modificat"));
			return;
		}

		if (destinatie != oferta.getDest()) {
			service.modificareDestinatieOferta(denumire, destinatie);
			QMessageBox::information(nullptr, "Info", "Destinatie ofertei a fost modificata cu succes!");
		}
		if (std::stoi(pret) != oferta.getPret()) {
			service.modificarePretOferta(denumire, std::stoi(pret));
			QMessageBox::information(nullptr, "Info", "Pretul ofertei a fost modificat cu succes!");
		}
		if (tip != oferta.getTip()) {
			service.modificareTipOFerta(denumire, tip);
			QMessageBox::information(nullptr, "Info", "Tipul ofertei a fost modificat cu succes!");
		}

		QMessageBox::information(nullptr, "Info", "Modificarea a fost efectuata cu succes!");
		qDebug() << "Am modificat!";
	}
	catch (RepoException& r) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(r.getErrorMessage()));
		return;
	}
	catch (ValidationException& v) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(v.getErrorMessage()));
		return;
	}
	catch (const std::invalid_argument& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti un intreg"));
		return;
	}
	catch (const std::out_of_range& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti un intreg"));
		return;
	}

}

void AgentieGUI::stergeOferta() {
	if (txtDenumire->text().toStdString() == "")
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Introduceti un nume!"));
		return;
	}
	auto denumire = txtDenumire->text().toStdString();
	try {
		Oferta oferta = service.gasesteOferta(denumire);
		service.stergeOferta(denumire);
		reloadList(lst, service.Oferte());
	}
	catch (RepoException& r) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(r.getErrorMessage()));
	}
}

void AgentieGUI::adaugaButoane(const std::vector<Oferta>& oferte) {
	for (const auto& o : oferte) {
		if (o.getTip() == "CityBreak") {
			auto btn = new QPushButton(QString::fromStdString(o.getDen()));
			lyBtnDy->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [this, btn, o]() {
				QMessageBox::information(nullptr, "Info", QString::fromStdString("Pret: ") + QString::number(o.getPret()));
				delete btn;
			});
		}
	}
}


void AgentieGUI::Wishlist() {
	WishlistGUI* wishlistWindow = new WishlistGUI(service);
	service.addObserver(wishlistWindow);
	wishlistWindow->show();
}
void AgentieGUI::reloadList(QListWidget* lst, const std::vector<Oferta>& oferte) {
	/*
	lst->clear();
	for (const auto& o : oferte) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(o.getDen()));
		item->setSizeHint(QSize(0, 30));
		item->setData(Qt::UserRole, QString::fromStdString(o.getTip()));
		if (o.getPret() > 2500) {
			item->setData(Qt::BackgroundRole, QBrush(Qt::yellow, Qt::SolidPattern));
		}
		lst->addItem(item);
	}
	*/
	model->setOferte(oferte);
}

void WishlistGUI::initGuiCmps()
{
	setLayout(wishlistLayout);	
	wishlistLayout->addWidget(table);

	QWidget* rWidget = new QWidget();
	QFormLayout* rLayout = new QFormLayout();
	QLabel* fisierLabel = new QLabel("Nume Fisier");
	QLabel* denumireOferta = new QLabel("Denumire Oferta");
	QLabel* numarGenerare = new QLabel("Numar Oferte");
	rLayout->addRow(fisierLabel, txtFisier);
	rLayout->addWidget(btnExport);
	rLayout->addRow(numarGenerare, txtNumar);
	rLayout->addWidget(btnGenereaza);
	rLayout->addRow(denumireOferta, txtNume);
	rLayout->addWidget(btnSterge);
	rLayout->addRow(btnGoleste);
	rWidget->setLayout(rLayout);

	wishlistLayout->addWidget(rWidget);
}

void WishlistGUI::connect()
{
	QObject::connect(btnExport, &QPushButton::clicked, [&]() {
		auto nume = txtFisier->text().toStdString();
		service.ExportWishlist(nume);
		QMessageBox::information(nullptr, "Info", QString::fromStdString("Wishlist exportat in fisierul " + nume + "!"));
	});

	QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
		auto numarOferte = txtNumar->text().toInt();
		try {
			service.adaugaRandomWishlist(numarOferte);
			reloadTable(table, service.getWishlist().getOferte());
		}
		catch (RepoException& r) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Nu exista atatea oferte disponibile!"));
		}
	});

	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
		auto denumire = txtNume->text().toStdString();
		try {
			service.stergeWishlist(denumire);
			reloadTable(table, service.getWishlist().getOferte());
		}
		catch (RepoException& r) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Oferta inexistenta!"));
		}
	});

	QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
		service.golesteWishlist();
		reloadTable(table, service.getWishlist().getOferte());
	});
}

void WishlistGUI::reloadTable(QTableWidget* lst, const std::vector<Oferta>& oferte)
{
	lst->clear();
	int i = 0;
	for (const auto& o : oferte) {
		QTableWidgetItem* denumire = new QTableWidgetItem(QString::fromStdString(o.getDen()));
		lst->setItem(i, 0, denumire);
		QTableWidgetItem* destinatie = new QTableWidgetItem(QString::fromStdString(o.getDest()));
		lst->setItem(i, 1, destinatie);
		QTableWidgetItem* tip = new QTableWidgetItem(QString::fromStdString(o.getTip()));
		lst->setItem(i, 2, tip);
		QTableWidgetItem* pret = new QTableWidgetItem(QString::fromStdString(std::to_string(o.getPret())));
		lst->setItem(i, 3, pret);
		i++;
	}
}
