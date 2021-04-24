#include "digit.h"
#include <iostream>
using namespace std;

digit::digit(const int& x, const int& y)
{
	seg[0] = new segment(1 + x, 0 + y, segment::orientacio::fekvo); //A
	seg[1] = new segment(5 + x, 1 + y, segment::orientacio::allo); //B
	seg[2] = new segment(5 + x, 6 + y, segment::orientacio::allo); //C
	seg[3] = new segment(1 + x, 10 + y, segment::orientacio::fekvo); //D
	seg[4] = new segment(0 + x, 6 + y, segment::orientacio::allo); //E
	seg[5] = new segment(0 + x, 1 + y, segment::orientacio::allo); //F
	seg[6] = new segment(1 + x, 5 + y, segment::orientacio::fekvo); //G

	this->x = x;
	this->y = y;
}

void digit::set(int num)
{
	unsigned char c = digits[num];
	for (int i = 0; i < 7; i++) {
		if (c & 1 == 1) {
			seg[i]->bekapcs();
		}
		else {
			seg[i]->kikapcs();
		}
		c >>= 1;
	}
}

digit::~digit()
{
	for (int i = 0; i < 7; i++) {
		delete seg[i];
	}
}
