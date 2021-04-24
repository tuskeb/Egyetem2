#pragma once
#include <ostream>
#include <fstream>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "Storage.h"

using namespace std;

/*Bináris fát megvalósító adatszerkezet. Még nem tökéletes:( TODO: tökéletesíteni, tesztelni*/
template<class T>
class BinTree : public Storage<T> {

protected:
	template <class T>
	class Data {
	public:
		T data;
		Data<T>* left;
		Data<T>* right;

		Data(T data) {
#ifdef debug
			cout << "A Data belso osztaly peldanya letrejott. " << data << endl;
#endif
			this->data = data;
			left = NULL;
			right = NULL;
			//cout << "new Data\n";
		}
		Data(T data, Data<T>* parent) : Data(data) {
			this->parent = parent;
		}
		~Data() {
#ifdef debug
			cout << "A Data belso osztaly peldanya megszunt. " << data << endl;
#endif
		}
	};

	Data<T>* root = NULL;

	//Visszaadja a data elemmel egyezõ értékû elem referenciáját. 
	//Ha nincs ilyen, akkor annak az üres elemnek a referenciáját adja vissza, 
	//ahová tenni kellene.
	Data<T>*& getDataPtrReference(const T& data) {
		if (root == NULL) {
			cout << "ROOT\n";
			return root;
		}
		static Data<T>* it;
		it = root;
		while (true) {
			//cout << it << endl;
			if (it->data > data) {
				//cout << "balra";
				if (it->left == NULL) {
					return it->left;
				}
				else {
					it = it->left;
				}
			}
			else {
				if (it->data == data) {
					return it;
				}
				else {

					//cout << "jobbra";
					if (it->right == NULL) {
						return it->right;
					}
					else {
						it = it->right;
					}
				}
			}
		}
		return it;
	}


public:

	enum outputformat {
		inorder = 0,
		preorder = 1,
		postorder = 2,
		graph = 3
	};

protected:
	outputformat order = outputformat::inorder;

public:
	void setOutputFormat(outputformat of) {
		order = of;
	}

	T& getByValue(const T& value) {
		return getDataPtrReference(value)->data;
	}

	BinTree<T>& add(const T& data) {
		Data<T>*& ptr = getDataPtrReference(data);
		if (ptr == NULL) {
			ptr = new Data<T>(data);
		}
		else {
			throw "Ilyen elem már létezik.";
		}
		return *this;
	};


	BinTree<T>& remove(const int&) {
		return *this;
	};


	T& get(const int&) {
		return root->data;
	};


	int size() const {
		int count = 0;
		Data<T>* iterator = root;
		while (iterator != NULL)
		{
			count++;
			iterator = iterator->right;
		}
		return count;
	};


	void toBinaryFile(string filename) {
	};


	void toTextFile(string filename) {
	};


	void preOrder(const Data<T>* subTree, ostream& os, string& separator) const {
		if (subTree == NULL) {
			return;
		}
		else {
			os << subTree->data << separator;
			inOrder(subTree->left, os, separator);
			inOrder(subTree->right, os, separator);
		}
	}

	void toPreOrder(ostream& os, string separator) const {
		preOrder(root, os, separator);
	}

	void inOrder(const Data<T>* subTree, ostream& os, string& separator) const {
		if (subTree == NULL) {
			return;
		}
		else {
			inOrder(subTree->left, os, separator);
			os << subTree->data << separator;
			inOrder(subTree->right, os, separator);
		}
	}

	void toInOrder(ostream& os, string separator) const {
		inOrder(root, os, separator);
	}

	void postOrder(const Data<T>* subTree, ostream& os, string& separator) const {
		if (subTree == NULL) {
			return;
		}
		else {
			inOrder(subTree->left, os, separator);
			inOrder(subTree->right, os, separator);
			os << subTree->data << separator;
		}
	}

	void toPostOrder(ostream& os, string separator) const {
		postOrder(root, os, separator);
	}

	void toGraph(ostream& os) {
		//LinkedList<Data<T>*> oldl;
		//oldl.add(root);
		//LinkedList<Data<T>*> newl;
	}

	friend ostream& operator<<(ostream& str, BinTree& tree) {
		str << "BinTree [";
		str << tree.size();
		str << "] {";
		switch (tree.order) {
		case outputformat::preorder:
			tree.toPreOrder(str, " ");
			break;
		case outputformat::inorder:
			tree.toInOrder(str, " ");
			break;
		case outputformat::postorder:
			tree.toPostOrder(str, " ");
			break;
		case outputformat::graph:
			tree.toGraph(str);
			break;
		}
		str << "}";
		return str;
	}

	BinTree<T>& clear() {
		return *this;
	}

};

