#pragma once

#include <Windows.h>
#include <string>
#include "wincon.h"

class segment {
public:
	static const int NUMBER_LENGTH = 4;

	enum class orientacio {
		fekvo = 0,
		allo = 1
	};
	void bekapcs();
	void kikapcs();
	segment(const int& x, const int& y, const orientacio& ori);


private:
	void megjelenites();
	int x, y;
	orientacio ori;
	bool statusz;


protected:


};