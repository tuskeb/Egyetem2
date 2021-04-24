#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>

using namespace std;

class File
{
public:

	virtual void writeBinary(ostream &f) = 0;
	virtual void writeText(ostream &f) = 0;
	virtual void readBinary(istream &f) = 0;
	virtual void readText(istream &f) = 0;

	/*Írás bináris fájlba. Az adatstruktúra bejárása függ a tárolási elvtõl, ezért ezt itt nem lehet kifejteni.*/
	virtual void toBinaryFile(string filename) {
		ofstream fs(filename, ios_base::binary | ios_base::out | ios_base::trunc);
		writeBinary(fs);
		fs.close();
	}

	/*Írás szöveges fájlba. Az adatstruktúra bejárása függ a tárolási elvtõl, ezért ezt itt nem lehet kifejteni.*/
	virtual void toTextFile(string filename) {
		ofstream fs(filename, ios_base::out | ios_base::trunc);
		writeText(fs);
		fs.close();
	}

	//Az add metódus fenti definiálása miatt beolvasható fájlból a tartalom, mivel csak az add metódust hívogatja. Az mindegy, hogy mi a kódja, a paraméterlista számít csak. Meg persze hogy hozzáfûzze az adatszerkezethez.
	virtual void fromBinaryFile(string filename) {

		//Fontos a binary, mert különben a 10h 13h párokat rosszul kezeli.
		ifstream fs(filename, ios_base::binary | ios_base::in);
		readBinary(fs);
		fs.close();
	}

	//Az add metódus fenti definiálása miatt beolvasható fájlból a tartalom, mivel csak az add metódust hívogatja. Az mindegy, hogy mi a kódja, a paraméterlista számít csak. Meg persze hogy hozzáfûzze az adatszerkezethez.//
	//Ehhez definiálni kell a T típus >> operátorát a beolvasáshoz!//
	virtual void fromTextFile(string filename, int skiplines = 0) {
		ifstream fs(filename, ios_base::in);
		readText(fs);
		fs.close();
	}

};