// Egyetem2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// git config --global http.sslverify "false"

#include <iostream>
#include "wincon.h"
#include "digit.h"
#include <stdlib.h>
#include "clock_zsolt.h"
using namespace MyConsole;


int main()
{
	MyConsole::Wincon* console = new MyConsole::Wincon();
	console->setBackgroundColor(Wincon::Color::black);
	system("cls");
	Clock clk;
	cout << clk.second();
	digit * digits[6];

	for (int i = 0; i < 6; i++) {
		digits[i] = new digit(i * 7, 5);
	}

	while (!console->keyavailable()) {
		console->sleep(100);
		digits[0]->set(clk.hour() / 10);
		digits[1]->set(clk.hour() % 10);
		digits[2]->set(clk.minute() / 10);
		digits[3]->set(clk.minute() % 10);
		digits[4]->set(clk.second() / 10);
		digits[5]->set(clk.second() % 10);
	}

	for (int i = 0; i < 6; i++) {
		delete digits[i];
	}


	//time_t now = time(0);
	//tm* ltm = localtime(&now);

	/*
	segment a(0,0,segment::orientacio::fekvo);
	segment b(5, 10, segment::orientacio::allo);
	segment c(15, 7, segment::orientacio::allo);
	c.bekapcs();
	a.kikapcs();
	*/
	/*
	segment a(1, 0, segment::orientacio::fekvo);
	segment b(5, 1, segment::orientacio::allo);
	segment c(5, 6, segment::orientacio::allo);
	segment d(1, 10, segment::orientacio::fekvo);
	segment e(0, 6, segment::orientacio::allo);
	segment f(0, 1, segment::orientacio::allo);
	segment g(1, 5, segment::orientacio::fekvo);
	
	a.bekapcs();
	b.bekapcs();
	c.bekapcs();
	d.bekapcs();
	e.bekapcs();
	f.bekapcs();
	g.bekapcs();
	*/



	/*console->setForegroundColor(Wincon::Color::aqua);
	console->print("Programozás");
	console->print("\nKern Zsolt\n");
	console->setForegroundColor(Wincon::Color::green);
	console->print("\nRábaközi József\n");
	console->setForegroundColor(Wincon::Color::red);
	console->print("\nErcsi Nóra\n");
	console->setBackgroundColor(Wincon::Color::blue);
	console->setForegroundColor(Wincon::Color::lightblue);
	console->gotoxy(10, 15);
	cout << console->cursorX() << endl;
	cout << console->cursorY() << endl;
	console->print(66);
	while (!console->keyavailable()) {
		cout << "asd \n";
		console->sleep(1000);
	}
	cout << console->readkey();	
	delete console;*/
	//console->readkey();
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
