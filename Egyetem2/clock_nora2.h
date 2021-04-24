#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


class clock {
	int sec, min, hour;


public:
	clock(int sec, int min, int hour);
	~clock();
};
