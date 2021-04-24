#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "LinkedList.h"
#include "SortedList.h"
#include "FileLinkedList.h"
#include "File.h"

template<typename T>
class FileSortedList : public SortedList<T>, public File
{

public:
	FileSortedList<T>() {}

	FileSortedList<T>(const FileSortedList<T>& other) : LinkedList(other) {
		typename LinkedList<T>::template Data<T>* iterator = other.first;
		while (iterator != NULL)
		{
			add(iterator->data);
			iterator = iterator->next;
		}
	}

	~FileSortedList() {
		this->clear();
	}


	virtual void writeBinary(ostream& f) {
		typename LinkedList<T>::template Data<T>* iterator = this->first;
		while (iterator != NULL)
		{
			//Minden adatszerkezet �talak�that� b�jt t�mbre az al�bbi m�dszerrel. A b�jtt�mb m�ret�t a sizeof() adja meg, azaz ennyi �r majd a f�jlba.
			f.write((char*)&(iterator->data), sizeof(T));
			iterator = iterator->next;
		}
	}


	virtual void writeText(ostream& f) {
		typename LinkedList<T>::template Data<T>* iterator = this->first;
		while (iterator != NULL)
		{
			//Sz�veges f�jlba val� �r�skor az adat (T) t�pusnak ismernie kell a << oper�tort. Ezzel a steamre �rja. Ha �sszetett adatszerkezet, akkor ezt az oper�tort �gy kell l�trehozni, hogy mindent �rjon ki valamilyen hat�rol� karakterekkel.
			f << iterator->data;
			if (iterator->next != NULL) {
				f << "\n";
			}
			iterator = iterator->next;
		}
	}

	virtual void readBinary(istream& f) {
		//Fontos a binary, mert k�l�nben a 10h 13h p�rokat rosszul kezeli.
		T buffer;

		//Akkora b�jtsort olvas be egy alkalommal, amekkora a T t�pus m�rete. Ezt a T t�pus p�ld�ny�nak lefoglalt mem�riater�letre m�solja.
		//Vigy�zat! K�l�nb�z� ford�t�k bizonyos adatt�pusokat m�s m�ret�en kezelnek, ezen k�v�l az adatok illeszt�se is lehet elt�r� a mem�ri�ban. CPU t�pusok k�zti b�jtsorrendre is figyelni kell, ha m�s rendszerben is haszn�lni akarjuk.
		//https://books.google.hu/books?id=-nivOizJyqsC&pg=PT312&lpg=PT312&dq=c%2B%2B+struct+to+binary+file+difference&source=bl&ots=0abehGQCPM&sig=ACfU3U0r8d6z0fSTIdHpWUWSGJRjiwMNXg&hl=hu&sa=X&ved=2ahUKEwimz82w6rXpAhUupIsKHawFCvQQ6AEwCHoECAgQAQ#v=onepage&q=c%2B%2B%20struct%20to%20binary%20file%20difference&f=false
		while (f.read((char*)&buffer, sizeof(T)))
		{
			this->add(buffer);
		}
	}

	virtual void readText(istream& f) {
		try {
			T buffer;
			/*Ehhez defini�lni kell a T t�pus >> oper�tor�t a beolvas�shoz!*/
			while (f >> buffer)
			{
				this->add(buffer);
			}
		}
		catch (const exception& e) {
			if (!f.eof()) {
				throw e;
			}
		}
	}
};

