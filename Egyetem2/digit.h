#pragma once
#include "segment.h"

class digit {
private:
	segment* seg[7];
	int x, y;
	//0bHGFEDCBA
	unsigned char digits[10] = {54, 88, 0b01011011, 44, 55, 66, 22,  93, 123, 200};
public:
	digit(const int& x, const int& y);
	void set(int num);
	~digit();
};