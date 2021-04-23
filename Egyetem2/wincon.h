#pragma once
#include <Windows.h>
#include <string>

using namespace std;

namespace MyConsole {
	class Wincon {

	private:
		HANDLE handle;
		int color;

	public:
		enum Color
		{
			black = 0,
			blue = 1,
			green = 2,
			aqua = 3,
			red = 4,
			purlple = 5,
			yellow = 6,
			lightgray = 7,
			gray = 8,
			lightblue = 9,
			lightgreen = 10,
			lightaqua = 11,
			lightred = 12,
			lightpurlple = 13,
			lightyellow = 14,
			white = 15,

		};

		Wincon();
		void gotoxy(int x, int y);
		void print(char c);
		void print(string str);
		void setBackgroundColor(Color c);
		void setForegroundColor(Color c);
		bool keyavailable();
		char readkey();
		void sleep(long msec);
	};
}