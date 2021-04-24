#include "segment.h"


void segment::bekapcs()
{
	if (statusz) return; 
	statusz = true;
	megjelenites();
}

void segment::kikapcs()
{
	if (!statusz) return;
	statusz = false;
	megjelenites();
}

segment::segment(const int& x, const int& y, const orientacio& ori)
{
	this->x = x;
	this->y = y;
	this->ori = ori;
	statusz = false;
	megjelenites();
	
}

void segment::megjelenites()
{

}
