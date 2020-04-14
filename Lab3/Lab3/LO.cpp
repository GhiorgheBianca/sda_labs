#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

////Nod operations
//constructorul nodului
Nod::Nod(TElement elem, Pointer_toNod urm) { // complexitate-timp Theta(1)
	this->element = elem;
	this->urmator = urm;
}

//functia care returneaza elementul nodului
TElement Nod::getElement() { // complexitate-timp Theta(1)
	return this->element;
}

//functia care returneaza adresa nodului urmator
Pointer_toNod Nod::getUrmator() { // complexitate-timp Theta(1)
	return this->urmator;
}
////

LO::LO(Relatie r) { // complexitate-timp Theta(1)
	/* de adaugat */
	rel = r;
	this->primul = nullptr;
}

//returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
int LO::dim() const { // complexitate-timp Theta(n)
	/* de adaugat */
	int dim = 0;
	auto nodCurent = primul;
	while (nodCurent != nullptr) {
		dim++;
		nodCurent = nodCurent->urmator;
	}
	return dim;
}

//verifica daca LO e vida
bool LO::vida() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return primul == nullptr;
}

//prima pozitie din LO
Iterator LO::prim() const { // complexitate-timp Theta(1)
	/* de adaugat */
	Iterator primul = Iterator(*this);
	primul.prim();
	return primul;
}

//returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const { // complexitate-timp Theta(1)
	/* de adaugat */
	if (poz.valid())
		return poz.curent->element;
	else
		throw exception();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
/*
	Complexitati:
		Caz favorabil: complexitate-timp Theta(1)
			- elementul nu exista in lista
			- elementul este pe prima pozitie

		Caz defavorabil: complexitate-timp Theta(n)
			- elementul exista si este pe ultima pozitie

		Caz mediu: complexitate-timp Theta(n) <= T(n) = (1+2+...+(n-1))/n
			- elementul este undeva in interiorul listei
	Complexitate generala: complexitate-timp Theta(n)
*/
TElement LO::sterge(Iterator& poz) {
	/* de adaugat */
	TElement elem = element(poz);
	if (cauta(elem).valid()) {
		//daca e primul si singurul element
		if (primul->urmator == nullptr) {
			delete primul;
			primul = nullptr;
		}
		//daca e primul element
		else if (primul->element == elem) {
			auto aux = primul->urmator;
			delete primul;
			primul = aux;
			poz.curent = aux;
		}
		else {
			auto nodCurent = primul;
			while (nodCurent->urmator->element != elem) {
				nodCurent = nodCurent->urmator;
			}

			//daca e intre primul si ultimul (nu este ultimul element)
			if (nodCurent->urmator->urmator != nullptr) {
				auto aux = nodCurent->urmator->urmator;
				delete nodCurent->urmator;
				nodCurent->urmator = aux;
				poz.curent = aux;
			}
			//daca e ultimul element
			else {
				delete nodCurent->urmator;
				nodCurent->urmator = nullptr;
				poz.curent = nodCurent;
			}
		}

		return elem;
	}
	else {
		throw exception();
	}
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
/*
	Complexitati:
		Caz favorabil: complexitate-timp Theta(1)
			- elementul s-ar afla in afara listei
			- elementul este pe prima pozitie

		Caz defavorabil: complexitate-timp Theta(n)
			- elementul exista si este pe ultima pozitie

		Caz mediu: complexitate-timp Theta(n) <= T(n) = (1+2+...+(n-1))/n
			- elementul este undeva in interiorul listei
	Complexitate generala: complexitate-timp Theta(n)
*/
Iterator LO::cauta(TElement e) const {
	/* de adaugat */
	Iterator iterator = Iterator(*this);
	iterator.curent = nullptr;

	//daca elementul nu apare in lista
	//(lista e vida SAU elementul e < primul - daca relatia e <=)
	if ((primul == nullptr) || !rel(primul->element, e)) {
		return iterator;
	}

	Pointer_toNod point = primul;
	//cat timp elementul cautat e in relatie cu elementul listei
	while ((point != nullptr) && (point->element != e) && !rel(e, point->element)) {
		point = point->urmator;
	}

	//daca am gasit elementul
	if ((point != nullptr) && (point->element == e)) {
		iterator.curent = point;
	}

	return iterator;
}

// adaugare element in LO
/*
	Complexitati:
		Caz favorabil: complexitate-timp Theta(1)
			- inseram pe prima pozitie
			- inseram inaintea primei pozitii

		Caz defavorabil: complexitate-timp Theta(n)
			- inseram pe ultima pozitie

		Caz mediu: complexitate-timp Theta(n) <= T(n) = (1+2+...+(n-1))/n
			- inseram undeva in interiorul listei
	Complexitate generala: complexitate-timp Theta(n)
*/
void LO::adauga(TElement e) {
	/* de adaugat */
	Pointer_toNod nou = new Nod(e, nullptr);

	//lista e vida => adaugarea primului element
	if (primul == nullptr) {
		primul = nou;
	}

	//adaugare inainte de primul element dupa relatie
	else if (!rel(primul->element, e)) {
		nou->urmator = primul;
		primul = nou;
	}

	//adaugare inauntrul listei sau la finalul listei
	else {
		auto nodCurent = primul;
		while (nodCurent->urmator != nullptr && rel(nodCurent->urmator->element, e)) {
			nodCurent = nodCurent->urmator;
		}
		nou->urmator = nodCurent->urmator;
		nodCurent->urmator = nou;
	}
}


//destructor
LO::~LO() { // complexitate-timp Theta(n)
	/* de adaugat */
	while (primul != nullptr) {
		auto aux = primul;
		primul = primul->urmator;
		delete aux;
	}
}


// returneaza ultimul iterator al unui element dat
// daca elementul nu este in lista, returneaza un iterator nevalid
/*
	Complexitati:
		Caz favorabil: complexitate-timp Theta(1)
			- elementul nu exista in lista (nu satisface relatia cu primul element)

		Caz defavorabil: complexitate-timp Theta(n)
			- elementul nu exista in lista (nu satisface relatia cu ultimul element)
			- elementul exista in lista

	Complexitate generala: complexitate-timp Theta(n)
*/
Iterator LO::ultimulIterator(TElement elem) const {
	Iterator iterator = Iterator(*this);
	iterator.curent = nullptr;

	//daca elementul nu apare in lista
	if ((primul == nullptr) || !rel(primul->element, elem)) {
		return iterator;
	}

	Pointer_toNod point = primul;
	//cat timp nu am ajuns la elementul cautat
	while ((point->urmator != nullptr) && (point->element != elem) && !rel(elem, point->element)) {
		point = point->urmator;
	}

	//cand am gasit elementul, cautam ultimul iterator
	while ((point->urmator != nullptr) && (point->urmator->element == elem)) {
		point = point->urmator;
	}

	//daca am gasit elementul
	if (point->element == elem) {
		iterator.curent = point;
	}

	return iterator;
}