#pragma once
#pragma once
#pragma once
#include "observer.h"
#include "Cos.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 100

class CartCRUDRead : public QWidget, public Observer {

private:
	Cos& cart_serv;

public:
	CartCRUDRead(Cos& cart_serv);

	void update() override;

	void paintEvent(QPaintEvent* event) override;

	~CartCRUDRead() {
		this->cart_serv.removeObserver(this);
	}
};


