#include "segment.h"
#include <iostream>

using namespace MyConsole;

void segment::bekapcs() {
	if (statusz) return;
	statusz = true;
	megjelenites();
}

void segment::kikapcs() {
	if (!statusz) return;
	statusz = false;
	megjelenites();
}

segment::segment(const int& x, const int& y, const orientacio& ori) {
	this->x = x;
	this->y = y;
	this->ori = ori;
	statusz = false;
	megjelenites();

}

void segment::megjelenites() {
	Wincon c;
	if (statusz == true) {
		c.setBackgroundColor(Wincon::Color::green);

	}
	else{
		c.setBackgroundColor(Wincon::Color::gray);
	}

	if (ori == segment::orientacio::allo) {
		for (int i = 0; i < NUMBER_LENGTH; i++) {
			c.gotoxy(x, y + i);
			c.print(" ");
		}
	}
	else {
		for (int i = 0; i < NUMBER_LENGTH; i++) {
			c.gotoxy(x + i, y);
			c.print(" ");
		}
	}
}

	