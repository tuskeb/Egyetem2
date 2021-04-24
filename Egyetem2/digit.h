#pragma once
#include "segment.h"

class digit {
private:
	segment* seg[7];
	int x, y;
	//0bHGFEDCBA
	unsigned char digits[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,  0b00000111, 0b01111111, 0b01101111};
public:
	digit(const int& x, const int& y);
	void set(int num);
	~digit();
};