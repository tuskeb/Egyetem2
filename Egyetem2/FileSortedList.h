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
			//Minden adatszerkezet átalakítható bájt tömbre az alábbi módszerrel. A bájttömb méretét a sizeof() adja meg, azaz ennyi ír majd a fájlba.
			f.write((char*)&(iterator->data), sizeof(T));
			iterator = iterator->next;
		}
	}


	virtual void writeText(ostream& f) {
		typename LinkedList<T>::template Data<T>* iterator = this->first;
		while (iterator != NULL)
		{
			//Szöveges fájlba való íráskor az adat (T) típusnak ismernie kell a << operátort. Ezzel a steamre írja. Ha összetett adatszerkezet, akkor ezt az operátort úgy kell létrehozni, hogy mindent írjon ki valamilyen határoló karakterekkel.
			f << iterator->data;
			if (iterator->next != NULL) {
				f << "\n";
			}
			iterator = iterator->next;
		}
	}

	virtual void readBinary(istream& f) {
		//Fontos a binary, mert különben a 10h 13h párokat rosszul kezeli.
		T buffer;

		//Akkora bájtsort olvas be egy alkalommal, amekkora a T típus mérete. Ezt a T típus példányának lefoglalt memóriaterületre másolja.
		//Vigyázat! Különbözõ fordítók bizonyos adattípusokat más méretûen kezelnek, ezen kívül az adatok illesztése is lehet eltérõ a memóriában. CPU típusok közti bájtsorrendre is figyelni kell, ha más rendszerben is használni akarjuk.
		//https://books.google.hu/books?id=-nivOizJyqsC&pg=PT312&lpg=PT312&dq=c%2B%2B+struct+to+binary+file+difference&source=bl&ots=0abehGQCPM&sig=ACfU3U0r8d6z0fSTIdHpWUWSGJRjiwMNXg&hl=hu&sa=X&ved=2ahUKEwimz82w6rXpAhUupIsKHawFCvQQ6AEwCHoECAgQAQ#v=onepage&q=c%2B%2B%20struct%20to%20binary%20file%20difference&f=false
		while (f.read((char*)&buffer, sizeof(T)))
		{
			this->add(buffer);
		}
	}

	virtual void readText(istream& f) {
		try {
			T buffer;
			/*Ehhez definiálni kell a T típus >> operátorát a beolvasáshoz!*/
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

