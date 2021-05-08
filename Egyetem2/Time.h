#pragma once
class Time {
public:
	int hour;
	int minute;
	int second;

	Time() {

	}

	Time(int h, int m, int s) {
		hour = h;
		minute = m;
		second = s;
	}

	friend istream& operator>>(istream& is, Time t) {
		return is;
	}

	friend ostream& operator<<(ostream& os, Time t) {
		os << t.hour << " " << t.minute << t.second;
		return os;
	}

	bool operator<(const Time& other) {
		return false;
	}

	bool operator>(const Time& other) {
		return false;
	}

	bool operator==(const Time& other) {
		return false;
	}

	bool operator!=(const Time& other) {
		return false;
	}

};