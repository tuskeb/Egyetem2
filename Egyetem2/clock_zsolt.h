#pragma once
#include <ctime>

class Clock {
public:
	Clock() {
		
	}

	int second() {
		time_t now = time(0);
		tm gmtm;
		localtime_s(&gmtm, &now);
		int tm = gmtm.tm_sec;
		return tm;
	}

	int minute() {
		time_t now = time(0);
		tm gmtm;
		localtime_s(&gmtm, &now);
		int tm = gmtm.tm_min;
		return tm;
	}

	int hour() {
		time_t now = time(0);
		tm gmtm;
		localtime_s(&gmtm, &now);
		int tm = gmtm.tm_hour;
		
		return tm;
	}
};