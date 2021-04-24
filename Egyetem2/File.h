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

	/*�r�s bin�ris f�jlba. Az adatstrukt�ra bej�r�sa f�gg a t�rol�si elvt�l, ez�rt ezt itt nem lehet kifejteni.*/
	virtual void toBinaryFile(string filename) {
		ofstream fs(filename, ios_base::binary | ios_base::out | ios_base::trunc);
		writeBinary(fs);
		fs.close();
	}

	/*�r�s sz�veges f�jlba. Az adatstrukt�ra bej�r�sa f�gg a t�rol�si elvt�l, ez�rt ezt itt nem lehet kifejteni.*/
	virtual void toTextFile(string filename) {
		ofstream fs(filename, ios_base::out | ios_base::trunc);
		writeText(fs);
		fs.close();
	}

	//Az add met�dus fenti defini�l�sa miatt beolvashat� f�jlb�l a tartalom, mivel csak az add met�dust h�vogatja. Az mindegy, hogy mi a k�dja, a param�terlista sz�m�t csak. Meg persze hogy hozz�f�zze az adatszerkezethez.
	virtual void fromBinaryFile(string filename) {

		//Fontos a binary, mert k�l�nben a 10h 13h p�rokat rosszul kezeli.
		ifstream fs(filename, ios_base::binary | ios_base::in);
		readBinary(fs);
		fs.close();
	}

	//Az add met�dus fenti defini�l�sa miatt beolvashat� f�jlb�l a tartalom, mivel csak az add met�dust h�vogatja. Az mindegy, hogy mi a k�dja, a param�terlista sz�m�t csak. Meg persze hogy hozz�f�zze az adatszerkezethez.//
	//Ehhez defini�lni kell a T t�pus >> oper�tor�t a beolvas�shoz!//
	virtual void fromTextFile(string filename, int skiplines = 0) {
		ifstream fs(filename, ios_base::in);
		readText(fs);
		fs.close();
	}

};