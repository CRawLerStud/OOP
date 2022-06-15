#include <qwidget.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include "MyTableModel.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include "Service.h"
#include "Oferta.h"
#include <vector>
#include <qlabel.h>
#include "Observer.h"
#include "HistogramGUI.h"

class WishlistGUI : public QWidget, public Observer {
private:
	QLabel* lbl = new QLabel("Nimic");
	QHBoxLayout* wishlistLayout = new QHBoxLayout();
	QTableWidget* table = new QTableWidget(200, 4);
	QPushButton* btnExport = new QPushButton("Export");
	QPushButton* btnGenereaza = new QPushButton("Genereaza");
	QPushButton* btnSterge = new QPushButton("Sterge");
	QPushButton* btnGoleste = new QPushButton("Goleste");
	QLineEdit* txtFisier = new QLineEdit();
	QLineEdit* txtNume = new QLineEdit();
	QLineEdit* txtNumar = new QLineEdit();

	Service& service;

	void update() override {
		reloadTable(table, service.getWishlist().getOferte());
	}

	void initGuiCmps();
	void connect();
	void reloadTable(QTableWidget* lst, const std::vector<Oferta>& oferte);
public:
	WishlistGUI(Service& service) : service{ service } {
		initGuiCmps();
		connect();
		reloadTable(table, service.getWishlist().getOferte());
	}

	void setOferta(const Oferta& o)	{
		lbl->setText(QString::fromStdString(o.getTip()));
	}
};

class AgentieGUI : public QWidget {
private:
	Service& service;
	QHBoxLayout* lyMain = new QHBoxLayout;
	QListWidget* lst;
	QPushButton* btnSortByDenumire;
	QPushButton* btnSortByDestinatie;
	QPushButton* btnSortByTipPret;
	QPushButton* btnFiltrareDestinatie;
	QPushButton* btnFiltrarePret;
	QPushButton* btnRaportTip; // vedem solutie
	QLineEdit* txtDenumire;
	QLineEdit* txtDestinatie;
	QLineEdit* txtTip;;
	QLineEdit* txtPret;
	QPushButton* btnAdd;
	QPushButton* btnModificare;
	QPushButton* btnStergere;
	QPushButton* btnAddWishlist;
	QPushButton* btnUndo;
	QPushButton* btnWishlist;
	QPushButton* btnOferte;
	QVBoxLayout* lyBtnDy = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;

	QPushButton* btnHistogram = new QPushButton("Histogram");
	
	MyTableModel* model;
	QTableView* tableOferte = new QTableView;

	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(QListWidget* lst, const std::vector<Oferta>& oferte);
	void reloadTable(QTableWidget* lst, const std::vector<Oferta>& oferte);
	void addnewOferta();
	void Wishlist();
	void modificaOferta();
	void stergeOferta();
	void adaugaButoane(const std::vector<Oferta>& oferte);

public:
	AgentieGUI(Service& service) : service{ service } {
		initGUICmps();
		this->model = new MyTableModel{ service.Oferte() };
		this->tableOferte->setModel(model);
		connectSignalsSlots();
		reloadList(lst, service.Oferte());
		adaugaButoane(service.Oferte());
	}
};