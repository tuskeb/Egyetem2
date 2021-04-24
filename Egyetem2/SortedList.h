#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "LinkedList.h"

using namespace std;

/*A kapcsolt list�hoz hasonl� adatszerkezet, annyiban k�l�nb�zik, hogy a felviteln�l figyel a rendezetts�gre a T t�pus �sszehasonl�t� oper�torai alapj�n.*/
template<class T>
class SortedList : public LinkedList<T> {

public:

	/*�res konstruktor*/
	SortedList<T>() {}

	//Copy konstruktor, m�solat k�sz�t�se egy list�r�l. A mem�ri�ban l�v� teljes l�ncolatot lem�solja. Ez persze t�bb l�p�s.
	SortedList<T>(const LinkedList<T>& other) {
		typename LinkedList<T>::template Data<T>* iterator = other.first;
		while (iterator != NULL)
		{
			add(iterator->data);
			iterator = iterator->next;
		}
	}

	/*A destruktor t�rli a list�t a mem�ri�b�l, hogy ne maradjon szem�t ut�na. Ha ez nem lenne, akkor csak az els� elem pointere t�rl�dne, az pedig probl�ma.*/
	~SortedList() {
		this->clear();
	}

	virtual LinkedList<T>& add(const T& data) {
		//Ha az els� elem �res, akkor az els� elem lesz az �j elem.
		if (this->first == NULL) {
			this->first = new typename LinkedList<T>::template Data<T>(data);
			return *this;
		}

		//Ha az els� elemn�l kisebb, akkor oda kell besz�rni.
		if (this->first->data > data) {
			typename LinkedList<T>::template Data<T>* newdata = new typename LinkedList<T>::template Data<T>(data);
			newdata->next = this->first;
			this->first = newdata;
			return *this;
		}

		//Egy�bk�nt meg kell keresni az elem hely�t a rendez�si elv szerint.
		typename LinkedList<T>::template Data<T>* iterator = this->first;
		while (iterator->next != NULL && iterator->next->data < data)
		{
			iterator = iterator->next;
		}
		if (iterator->next == NULL) {
			iterator->next = new typename LinkedList<T>::template Data<T>(data);
		}
		else {
			typename LinkedList<T>::template Data<T>* newdata = new typename LinkedList<T>::template Data<T>(data);
			newdata->next = iterator->next;
			iterator->next = newdata;
		}
		return *this;
	}

};


