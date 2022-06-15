#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <qfont.h>
#include "Oferta.h"
#include <vector>
#include <qdebug.h>
#include <vector>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Oferta> oferte;
public:
	MyTableModel(const std::vector<Oferta>& oferte) :oferte{ oferte } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return oferte.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;

		if (role == Qt::ForegroundRole) {
			auto oferta = this->oferte[index.row()];
			if (oferta.getTip() == "CityBreak") {
				return QBrush(Qt::magenta);
			}
		}
		if (role == Qt::FontRole) {
			QFont f;
			f.setItalic(index.row() % 10 == 1);
			f.setBold(index.row() % 10 == 1);
			return f;
		}
		if (role == Qt::BackgroundRole) {

			int row = index.row();
			QModelIndex i = index.sibling(index.row(), 1);
			if (i.data().toString() == "Atena") {
				QBrush bg(Qt::yellow);
				return bg;
			}
		}

		if (role == Qt::DisplayRole) {

			Oferta p = oferte[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getDen());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getDest());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getTip());
			}
			else if (index.column() == 3) {
				return QString::number(p.getPret());
			}
		}

		return QVariant{};
	}

	void setOferte(const vector<Oferta> oferte) {
		this->oferte = oferte;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Denumire");
				case 1:
					return tr("Destinatie");
				case 2:
					return tr("Tip");
				case 3:
					return tr("Pret");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};
