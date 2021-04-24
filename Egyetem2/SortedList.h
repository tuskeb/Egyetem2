#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "LinkedList.h"

using namespace std;

/*A kapcsolt listához hasonló adatszerkezet, annyiban különbözik, hogy a felvitelnél figyel a rendezettségre a T típus összehasonlító operátorai alapján.*/
template<class T>
class SortedList : public LinkedList<T> {

public:

	/*Üres konstruktor*/
	SortedList<T>() {}

	//Copy konstruktor, másolat készítése egy listáról. A memóriában lévõ teljes láncolatot lemásolja. Ez persze több lépés.
	SortedList<T>(const LinkedList<T>& other) {
		typename LinkedList<T>::template Data<T>* iterator = other.first;
		while (iterator != NULL)
		{
			add(iterator->data);
			iterator = iterator->next;
		}
	}

	/*A destruktor törli a listát a memóriából, hogy ne maradjon szemét utána. Ha ez nem lenne, akkor csak az elsõ elem pointere törlõdne, az pedig probléma.*/
	~SortedList() {
		this->clear();
	}

	virtual LinkedList<T>& add(const T& data) {
		//Ha az elsõ elem üres, akkor az elsõ elem lesz az új elem.
		if (this->first == NULL) {
			this->first = new typename LinkedList<T>::template Data<T>(data);
			return *this;
		}

		//Ha az elsõ elemnél kisebb, akkor oda kell beszúrni.
		if (this->first->data > data) {
			typename LinkedList<T>::template Data<T>* newdata = new typename LinkedList<T>::template Data<T>(data);
			newdata->next = this->first;
			this->first = newdata;
			return *this;
		}

		//Egyébként meg kell keresni az elem helyét a rendezési elv szerint.
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


