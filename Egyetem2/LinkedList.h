#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "Storage.h"

//#define debug

using namespace std;

/*Minden adatszerkezet �s�b�l lesz�rmaztatott kapcsolt lista adatszerkezetet megval�s�t� generikus oszt�ly. B�rmilyen T adatszerkezettel haszn�lhat�.*/
template<typename T>
class LinkedList : public Storage<T> {

protected:

	/* Bels� oszt�ly l�trehoz�sa a l�ncolt lista szerkezet t�rol�s�ra.
	Az�rt sz�ks�ges, mert az adat mell�, amely T t�pus�, meg kell hat�rozni a k�vetkez� adatra val� hivatkoz�st a l�ncolat miatt.*/
	template <typename T>
	class Data {
	public:
		//A hordozott adat
		T data;

		//A l�ncol�s a k�vetkez� elemre mutat majd. Amennyiben nincs k�vetkez�, NULL �rt�k� lesz.
		Data<T>* next;

		//A be�gyazott oszt�lyb�l �gy hozhat� l�tre p�ld�ny, hogy �tadjuk neki a hordozott adatot. Err�l m�solatot k�sz�t.
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

		//Amikor t�rl�nk egy adatot, a destruktora lefut.
		~Data() {
#ifdef debug
			cout << "A Data belso osztaly peldanya megszunt.\n";
#endif
		}
	};

	/*A l�ncolt lista legels� elem�t t�rolja. Amikor �res a lista, az �rt�ke NULL*/
	Data<T>* first = NULL;

	/*Valah�nyadik elemre mutat� pointernek a refenci�j�t adja meg. Ezen kereszt�l m�dos�that� lesz a pointer �rt�ke is, azaz ezen kereszt�l is lehet majd a l�ncot m�dos�tani.*/
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
		throw "Az index a lista hat�rain k�v�lre mutat.";
	}


public:

	/*�res konstruktor*/
	LinkedList<T>() {}

	//Copy konstruktor, m�solat k�sz�t�se egy list�r�l. A mem�ri�ban l�v� teljes l�ncolatot lem�solja. Ez persze t�bb l�p�s.
	LinkedList<T>(const LinkedList<T>& other) {
		Data<T>* iterator = other.first;
		while (iterator != NULL)
		{
			add(iterator->data);
			iterator = iterator->next;
		}
	}

	/*�j lista k�sz�t�se elemek hozz�ad�s�val. Ez csak megk�nny�ti a haszn�lat�t.*/
	LinkedList<T>(int countOfEllipsis, const T ...) {
		va_list vl;
		va_start(vl, countOfEllipsis);
		for (int i = 0; i < countOfEllipsis; add(va_arg(vl, T)), i++);
	}

	/*A destruktor t�rli a list�t a mem�ri�b�l, hogy ne maradjon szem�t ut�na. Ha ez nem lenne, akkor csak az els� elem pointere t�rl�dne, az pedig probl�ma.*/
	~LinkedList() {
		clear();
	}


	LinkedList<T>& add(const T& data) {
		//Ha az els� elem �res, akkor az els� elem lesz az �j elem.
		if (first == NULL) {
			first = new Data<T>(data);
			return *this;
		}
		//Ha az els� elem nem �res, akkor meg kell keresni azt, aminek a k�vetkez�je �res. Indul�s az els� emelt�l.
		Data<T>* iterator = first;
		while (iterator->next != NULL)
		{
			iterator = iterator->next;
		}
		//Az utols� elem k�vetkez�je lesz az �j elem.
		iterator->next = new Data<T>(data);
		return *this;
	}


	LinkedList<T>& insert(const T& data, const int& index) {
		//Ha az els� elem hely�re akarunk besz�rni, akkor az els� elem pointer�t kell �t�ll�tani az �j elemre.
		//Az �j elem k�vetkez�je pedig az els� lesz.
		if (index == 0) {
			//El�sz�r jegyezz�k meg az els� elem pointer�t
			Data<T>* d = first;
			//Majd az els� elem pinter�t �ll�tsuk az �jra, �s annak a k�vetkez� pointere az els� elemre mutasson.
			first = new Data<T>(data, d);
		}
		else {
			//Ha nem az els� elem hely�re akarunk, akkor keress�k meg a k�v�nt elem pointer�t.
			//d �rt�ke az elem, ami ut�n besz�rjuk, azaz a k�vetkez�je lesz, d2 pedig az, ami az eddigi k�vetkez� volt, az �j elem k�vetkez�je lesz.
			Data<T>* d = getDataPtrReference(index - 1);
			Data<T>* d2 = d->next;
			d->next = new Data<T>(data, d2);
		}
		return *this;
	}

	LinkedList<T>& remove(const int& index) {
		//Ha az els�t t�vol�tjuk el, akkor
		if (index == 0) {
			//Az els� pointer�r�l k�sz�l egy m�solat, ez seg�t majd az elt�vol�t�sban. 
			Data<T>* d = first;
			//Az els�t a k�vetkez�re l�ptetj�nk, �gy az eddigi els� csak a m�solatban marad meg.
			first = first->next;
			//A m�solat alapj�n t�rl�nk.
			delete d;
		}
		else {
			//Ha nem az els�t t�vol�tjuk el, akkor meg kell keresni az elt�vol�tand� elemet, �s az el�tte l�v�t �s az ut�na l�v�t �ssze kell kapcsolni, ez ut�n lehet t�r�lni
			Data<T>* d = getDataPtrReference(index - 1);
			Data<T>* d2 = d->next;
			d->next = d2->next;
			delete d2;
		}
		return *this;
	}

	LinkedList<T>& clear() {

		
		
		Data<T>* iterator = first;
		//Am�g a lista v�g�hez nem �r...
		while (iterator != NULL)
		{
			//Az elem pointer�r�l k�sz�l egy m�solat. Majd ezt fogjuk t�r�lni, de addig nem lehet, am�g ez alapj�n tov�bb nem l�pett.
			Data<T>* d = iterator;
			//L�p�s a k�vetkez� elemre.
			iterator = iterator->next;
			//El�z� t�rl�se.
			delete d;
		}
		//Az �res list�ban az els� elem �rt�ke NULL.
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

	//A get f�ggv�ny az�rt referencia, hogy rajta kereszt�l lehessen m�dos�tani az �rt�ket egy �rt�kad�sban.
	T& get(const int& index) {
		return getDataPtrReference(index)->data;
	}

	//Indexel� oper�tor. A m�lt �r�r�l �gyis kimaradt. �gy szebb lesz a lista haszn�lata. �gy m�k�dik majd, mint egy t�mb.
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
			throw "A keresett �rt�k nem tal�lhat�.";
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
			throw "A keresett �rt�k nem tal�lhat�.";
		}
	}
	

	//A list�r�l k�sz�t egy kimenetet egy streamre. Ezzel k�nnyen tesztelhet�, hogy mi van a list�ban.
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

