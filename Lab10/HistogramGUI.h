#pragma once

#include <qpainter.h>
#include <qwidget.h>
#include "Service.h"
#include "Observer.h"

class HistogramGUI : public QWidget, public Observer
{
private:
	Service& service;
public:

	HistogramGUI(Service& service) :service{ service } {
		service.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 200 + rand() % 50;
		int y = 200 + rand() % 50;
		for (auto o : service.getWishlist().getOferte()) {
			p.drawEllipse(x, y, 30, 30);
			if (rand() % 2 == 1)
			{
				x += rand() % 100;
				y += rand() % 100;
			}
			else {
				x -= rand() % 100;
				y -= rand() % 100;
			}
		}
	}
};
