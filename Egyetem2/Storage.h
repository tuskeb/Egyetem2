#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>

using namespace std;

/*Minden adatszerkezet �se a p�ld�ban. Mivel minden adatszerkezetnek ezeket a met�dusokat t�mogatnia kell.*/
template<typename T>
class Storage {
public:
	/*Ameyik met�dus =0-val van defini�lva, azt a lesz�rmazott oszt�lyban kell majd kifejteni. Ezek m�s nyelven az absztrakt met�dusok.*/
	/*Minden adatszerkezetnek kell tudni a k�vetkez�ket:*/

	/*T t�pus� adat felvitele. Bemenet T t�pus, visszaadott �rt�k pedig maga az adatszerkezet lesz annak �rdek�ben, hogy �jabb f�ggv�ny h�vhat� legyen bel�le. Pl.: ll.add(7).add(5)...*/
	virtual Storage<T>& add(const T&) = 0;

	/*Valah�nyadik adat elt�vol�t�sa. Ez a k�rd�s egy bin�ris fa eset�n nem is egyszer�:)*/
	virtual Storage<T>& remove(const int&) = 0;

	/*Minden adatszerkezethez tartozik egy f�ggv�ny, amellye az �sszes elem t�r�lhet�. Sajnos nem lehet megh�vni a Storage oszt�ly destruktor�ban, teh�t mindenhol gondoskodni kell r�la.*/
	virtual Storage<T>& clear() = 0;

	/*Valah�nyadik adat kiolvas�sa. Ez a k�rd�s egy bin�ris fa eset�n nem is egyszer�:)*/
	virtual T& get(const int&) = 0;

	/*Az elt�rolt adatok megsz�mol�sa is f�ggv�ny dolga. Ez az adatstruktur�knak megfelel�en lehet t�bbf�le is.*/
	virtual int size() const = 0;

	/*�rt�k alapj�n keres�s. Ehhez a met�dushoz a T t�pusnak az �sszehasonl�t� oper�torokat defini�lni kell. Mivel bizonyos adatszerkezetek t�mogatj�k az �rt�kek egyenl�s�g�t (kapcsolt lista), bizonyosak pedig nem (bin�ris fa), ez�rt van �rtelme az el�fordul�s keres�s kezdet�nek a hely�t megadni.*/
	//virtual T& getByValue(const T&) = 0;


	/*T�bb adat felvitele egyszerre. Ez kifejthet� itt, mert az add met�dus m�r fent defini�l�sra ker�lt. B�r a tartalm�t a lesz�rmazott oszt�lyok fogj�k majd megadni.*/
	virtual Storage<T>& addAll(int count, const T ...) {
		va_list vl;
		va_start(vl, count);
		for (int i = 0; i < count; add(va_arg(vl, T)), i++);
		return *this;
	}

};



