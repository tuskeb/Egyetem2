#pragma once
#include "segment.h"

class digit {
private:
	segment* seg[7];
	int x, y;
public:
	digit(const int& x, const int& y);
	void set(int num);
	~digit();
};