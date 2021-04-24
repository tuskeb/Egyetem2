#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>

using namespace std;

/*Minden adatszerkezet õse a példában. Mivel minden adatszerkezetnek ezeket a metódusokat támogatnia kell.*/
template<typename T>
class Storage {
public:
	/*Ameyik metódus =0-val van definiálva, azt a leszármazott osztályban kell majd kifejteni. Ezek más nyelven az absztrakt metódusok.*/
	/*Minden adatszerkezetnek kell tudni a következõket:*/

	/*T típusú adat felvitele. Bemenet T típus, visszaadott érték pedig maga az adatszerkezet lesz annak érdekében, hogy újabb függvény hívható legyen belõle. Pl.: ll.add(7).add(5)...*/
	virtual Storage<T>& add(const T&) = 0;

	/*Valahányadik adat eltávolítása. Ez a kérdés egy bináris fa esetén nem is egyszerû:)*/
	virtual Storage<T>& remove(const int&) = 0;

	/*Minden adatszerkezethez tartozik egy függvény, amellye az összes elem törölhetõ. Sajnos nem lehet meghívni a Storage osztály destruktorában, tehát mindenhol gondoskodni kell róla.*/
	virtual Storage<T>& clear() = 0;

	/*Valahányadik adat kiolvasása. Ez a kérdés egy bináris fa esetén nem is egyszerû:)*/
	virtual T& get(const int&) = 0;

	/*Az eltárolt adatok megszámolása is függvény dolga. Ez az adatstrukturáknak megfelelõen lehet többféle is.*/
	virtual int size() const = 0;

	/*Érték alapján keresés. Ehhez a metódushoz a T típusnak az összehasonlító operátorokat definiálni kell. Mivel bizonyos adatszerkezetek támogatják az értékek egyenlõségét (kapcsolt lista), bizonyosak pedig nem (bináris fa), ezért van értelme az elõfordulás keresés kezdetének a helyét megadni.*/
	//virtual T& getByValue(const T&) = 0;


	/*Több adat felvitele egyszerre. Ez kifejthetõ itt, mert az add metódus már fent definiálásra került. Bár a tartalmát a leszármazott osztályok fogják majd megadni.*/
	virtual Storage<T>& addAll(int count, const T ...) {
		va_list vl;
		va_start(vl, count);
		for (int i = 0; i < count; add(va_arg(vl, T)), i++);
		return *this;
	}

};



