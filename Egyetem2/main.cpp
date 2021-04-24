// Egyetem2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// git config --global http.sslverify "false"

#include <iostream>
#include "wincon.h"
using namespace MyConsole;

int main()
{
	MyConsole::Wincon * console = new MyConsole::Wincon();
	console->setForegroundColor(Wincon::Color::aqua);
	console->print("Programozás");
	console->setForegroundColor(Wincon::Color::green);
	console->print("\nRábaközi József\n");
	console->setBackgroundColor(Wincon::Color::blue);
	console->setForegroundColor(Wincon::Color::lightblue);
	console->gotoxy(10, 10);
	console->print(66);
	while (!console->keyavailable()) {
		cout << "asd \n";
		console->sleep(1000);
	}
	cout << console->readkey();	
	delete console;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
