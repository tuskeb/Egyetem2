#include "digit.h"

digit::digit(const int& x, const int& y)
{
	seg[0] = new segment(1 + x, 0 + y, segment::orientacio::fekvo);
	seg[1] = new segment(5 + x, 1 + y, segment::orientacio::allo);
	seg[2] = new segment(5 + x, 6 + y, segment::orientacio::allo);
	seg[3] = new segment(1 + x, 10 + y, segment::orientacio::fekvo);
	seg[4] = new segment(0 + x, 6 + y, segment::orientacio::allo);
	seg[5] = new segment(0 + x, 1 + y, segment::orientacio::allo);
	seg[6] = new segment(1 + x, 5 + y, segment::orientacio::fekvo);

	this->x = x;
	this->y = y;
}

void digit::set(int num)
{
}

digit::~digit()
{
	for (int i = 0; i < 7; i++) {
		delete seg[i];
	}
}
