#include <iostream>
#include "wincon.h"
#include "segment.h"
#include <stdlib.h>
using namespace MyConsole;


int main()
{
	MyConsole::Wincon* console = new MyConsole::Wincon();
	console->setBackgroundColor(Wincon::Color::black);
	system("cls");	
	segment a(0, 0, segment::orientacio::fekvo);
	segment b(5, 10, segment::orientacio::allo);
	segment c(15, 7, segment::orientacio::allo);
	c.bekapcs();
	a.kikapcs();
	console->readkey();
	delete console;
}