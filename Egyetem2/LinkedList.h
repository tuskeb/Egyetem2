#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "Storage.h"

//#define debug

using namespace std;

/*Minden adatszerkezet õsébõl leszármaztatott kapcsolt lista adatszerkezetet megvalósító generikus osztály. Bármilyen T adatszerkezettel használható.*/
template<typename T>
class LinkedList : public Storage<T> {

protected:

	/* Belsõ osztály létrehozása a láncolt lista szerkezet tárolására.
	Azért szükséges, mert az adat mellé, amely T típusú, meg kell határozni a következõ adatra való hivatkozást a láncolat miatt.*/
	template <typename T>
	class Data {
	public:
		//A hordozott adat
		T data;

		//A láncolás a következõ elemre mutat majd. Amennyiben nincs következõ, NULL értékû lesz.
		Data<T>* next;

		//A beágyazott osztályból úgy hozható létre példány, hogy átadjuk neki a hordozott adatot. Errõl másolatot készít.
		Data(T data) {
			this->data = data;
			next = NULL;
#ifdef debug
			cout << "A Data belso osztaly peldanya letrejott.\n";
#endif
		}

		Data(T data, Data<T>* next) : Data(data) {
			this->next = next;
		}

		//Amikor törlünk egy adatot, a destruktora lefut.
		~Data() {
#ifdef debug
			cout << "A Data belso osztaly peldanya megszunt.\n";
#endif
		}
	};

	/*A láncolt lista legelsõ elemét tárolja. Amikor üres a lista, az értéke NULL*/
	Data<T>* first = NULL;

	/*Valahányadik elemre mutató pointernek a refenciáját adja meg. Ezen keresztül módosítható lesz a pointer értéke is, azaz ezen keresztül is lehet majd a láncot módosítani.*/
	inline Data<T>*& getDataPtrReference(const int& index) {
		static Data<T>* iterator;
		iterator = first;
		int count = 0;
		while (iterator != NULL)
		{
			if (count == index) {
				return iterator;
			}
			iterator = iterator->next;
			count++;
		}
		throw "Az index a lista határain kívülre mutat.";
	}


public:

	/*Üres konstruktor*/
	LinkedList<T>() {}

	//Copy konstruktor, másolat készítése egy listáról. A memóriában lévõ teljes láncolatot lemásolja. Ez persze több lépés.
	LinkedList<T>(const LinkedList<T>& other) {
		Data<T>* iterator = other.first;
		while (iterator != NULL)
		{
			add(iterator->data);
			iterator = iterator->next;
		}
	}

	/*Új lista készítése elemek hozzáadásával. Ez csak megkönnyíti a használatát.*/
	LinkedList<T>(int countOfEllipsis, const T ...) {
		va_list vl;
		va_start(vl, countOfEllipsis);
		for (int i = 0; i < countOfEllipsis; add(va_arg(vl, T)), i++);
	}

	/*A destruktor törli a listát a memóriából, hogy ne maradjon szemét utána. Ha ez nem lenne, akkor csak az elsõ elem pointere törlõdne, az pedig probléma.*/
	~LinkedList() {
		clear();
	}


	LinkedList<T>& add(const T& data) {
		//Ha az elsõ elem üres, akkor az elsõ elem lesz az új elem.
		if (first == NULL) {
			first = new Data<T>(data);
			return *this;
		}
		//Ha az elsõ elem nem üres, akkor meg kell keresni azt, aminek a következõje üres. Indulás az elsõ emeltõl.
		Data<T>* iterator = first;
		while (iterator->next != NULL)
		{
			iterator = iterator->next;
		}
		//Az utolsó elem következõje lesz az új elem.
		iterator->next = new Data<T>(data);
		return *this;
	}


	LinkedList<T>& insert(const T& data, const int& index) {
		//Ha az elsõ elem helyére akarunk beszúrni, akkor az elsõ elem pointerét kell átállítani az új elemre.
		//Az új elem következõje pedig az elsõ lesz.
		if (index == 0) {
			//Elõször jegyezzük meg az elsõ elem pointerét
			Data<T>* d = first;
			//Majd az elsõ elem pinterét állítsuk az újra, és annak a következõ pointere az elsõ elemre mutasson.
			first = new Data<T>(data, d);
		}
		else {
			//Ha nem az elsõ elem helyére akarunk, akkor keressük meg a kívánt elem pointerét.
			//d értéke az elem, ami után beszúrjuk, azaz a következõje lesz, d2 pedig az, ami az eddigi következõ volt, az új elem következõje lesz.
			Data<T>* d = getDataPtrReference(index - 1);
			Data<T>* d2 = d->next;
			d->next = new Data<T>(data, d2);
		}
		return *this;
	}

	LinkedList<T>& remove(const int& index) {
		//Ha az elsõt távolítjuk el, akkor
		if (index == 0) {
			//Az elsõ pointerérõl készül egy másolat, ez segít majd az eltávolításban. 
			Data<T>* d = first;
			//Az elsõt a következõre léptetjünk, így az eddigi elsõ csak a másolatban marad meg.
			first = first->next;
			//A másolat alapján törlünk.
			delete d;
		}
		else {
			//Ha nem az elsõt távolítjuk el, akkor meg kell keresni az eltávolítandó elemet, és az elõtte lévõt és az utána lévõt össze kell kapcsolni, ez után lehet törölni
			Data<T>* d = getDataPtrReference(index - 1);
			Data<T>* d2 = d->next;
			d->next = d2->next;
			delete d2;
		}
		return *this;
	}

	LinkedList<T>& clear() {

		
		
		Data<T>* iterator = first;
		//Amíg a lista végéhez nem ér...
		while (iterator != NULL)
		{
			//Az elem pointerérõl készül egy másolat. Majd ezt fogjuk törölni, de addig nem lehet, amíg ez alapján tovább nem lépett.
			Data<T>* d = iterator;
			//Lépés a következõ elemre.
			iterator = iterator->next;
			//Elõzõ törlése.
			delete d;
		}
		//Az öres listában az elsõ elem értéke NULL.
		first = NULL;
		
		return *this;
	}

	int size() const {
		int count = 0;
		Data<T>* iterator = first;
		while (iterator != NULL)
		{
			count++;
			iterator = iterator->next;
		}
		return count;
	}

	//A get függvény azért referencia, hogy rajta keresztül lehessen módosítani az értéket egy értékadásban.
	T& get(const int& index) {
		return getDataPtrReference(index)->data;
	}

	//Indexelõ operátor. A múlt óráról úgyis kimaradt. Így szebb lesz a lista használata. Úgy mûködik majd, mint egy tömb.
	T& operator[](const int& index)
	{
		return getDataPtrReference(index)->data;
	}
	
	T& getByValue(const T& value) {
		Data<T>* iterator = first;
		while (iterator != NULL && iterator->data != value)
		{
			iterator = iterator->next;
		}
		if (iterator != NULL) {
			return iterator->data;
		}
		else {
			throw "A keresett érték nem található.";
		}
	}
	

	T& getByValue(const T& value, const int& start = 0) {
		Data<T>* iterator = first;
		int count = 0;
		while (iterator != NULL && start > count)
		{
			iterator = iterator->next;
			count++;
		}
		while (iterator != NULL && iterator->data != value)
		{
			iterator = iterator->next;
		}
		if (iterator != NULL) {
			return iterator->data;
		}
		else {
			throw "A keresett érték nem található.";
		}
	}
	

	//A listáról készít egy kimenetet egy streamre. Ezzel könnyen tesztelhetõ, hogy mi van a listában.
	friend ostream& operator<<(ostream& str, const LinkedList& list) {
		str << "LinkedList [";
		str << list.size();
		str << "] {";
		Data<T>* iterator = list.first;
		while (iterator != NULL)
		{
			str << iterator->data;
			if (iterator->next != NULL) {
				str << ", ";
			}
			iterator = iterator->next;
		}
		str << "}";
		return str;
	}

};

