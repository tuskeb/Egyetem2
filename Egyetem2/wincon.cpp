#include "wincon.h"
#include <iostream>
#include <conio.h>
#include <locale.h>


using namespace std;

namespace MyConsole {


	Wincon::Wincon()
	{
		setlocale(LC_ALL, "hun");
		color = Color::black << 4 | Color::lightgreen;
		SetConsoleTextAttribute(handle, color);
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		//cout << "Hello world:)";
	}

	void Wincon::gotoxy(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(handle, coord);
	}

	int Wincon::cursorX()
	{
		CONSOLE_SCREEN_BUFFER_INFO sc;
		GetConsoleScreenBufferInfo(handle, &sc);
		return sc.dwCursorPosition.X;
	}

	int Wincon::cursorY()
	{
		CONSOLE_SCREEN_BUFFER_INFO sc;
		GetConsoleScreenBufferInfo(handle, &sc);
		return sc.dwCursorPosition.Y;
	}

	void Wincon::print(char c) {
		cout << c;
	}

	void Wincon::print(string str) {
		cout << str;
	}

	void Wincon::setBackgroundColor(Color c)
	{
		color = (color & 0x0F) | (c << 4);
		SetConsoleTextAttribute(handle, color);
	}

	void Wincon::setForegroundColor(Color c)
	{
		color = (color & 0xF0) | c;
		SetConsoleTextAttribute(handle, color);
	}

	bool Wincon::keyavailable()
	{
		for (int i = 32; i <= 255; i++) {
			if (GetAsyncKeyState(i)) {
				return true;
			}
		}
		return false;
	}

	char Wincon::readkey() {
		char c;
		c = _getch();
		return c;
	}

	void Wincon::sleep(long msec) {
		Sleep(msec);
	}
}