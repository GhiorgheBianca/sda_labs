#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <unordered_map>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) { // complexitate-timp Theta(n)
	/* de adaugat */
	element = new TElem[cp];
	urmator = new int[cp];
	anterior = new int[cp];
	//relatia dintre elemente
	rel = r;
	//dimensiunea initiala e 0
	dimensiune = 0;
	//lista e vida
	primul = -1;
	//se initializeaza lista spatiului liber - toate pozitiile din vector sunt marcate ca fiind libere
	for (int i = 0; i < cp - 1; i++)
		urmator[i] = i + 1;
	urmator[cp - 1] = -1;
	for (int i = 1; i < cp; i++)
		anterior[i] = i - 1;
	anterior[0] = -1;
	//referinta spre prima pozitie libera din lista
	primLiber = 0;
}

int MDO::aloca() { // complexitate-timp Theta(1)
	//se sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urmator[primLiber];
	return i;
}

void MDO::dealoca(int i) { // complexitate-timp Theta(1)
	//se trece pozitia i in lista spatiului liber
	urmator[i] = primLiber;
	anterior[i] = -1;
	primLiber = i;
}

void MDO::redimensioneaza() { // complexitate-timp amortizata Theta(n)
	//dublam capacitatea
	cp *= 2;
	int* new_allocation_urmator = new int[cp];
	int* new_allocation_anterior = new int[cp];
	TElem* new_allocation_element = new TElem[cp];
	int i;
	//initializam prima parte a listelor (deja completata)
	for (i = 0; i < dimensiune; i++)
	{
		new_allocation_urmator[i] = urmator[i];
		new_allocation_anterior[i] = anterior[i];
		new_allocation_element[i] = element[i];
	}
	//initializam a doua parte a listelor
	for (i = dimensiune; i < cp - 1; i++)
	{
		new_allocation_urmator[i] = i + 1;
		new_allocation_anterior[i] = i - 1;
	}
	new_allocation_urmator[cp - 1] = -1;
	new_allocation_anterior[cp - 1] = cp - 2;

	//stergem datele din listele initiale
	delete[] urmator;
	delete[] anterior;
	delete[] element;
	//initializam listele cu listele redimensionate
	urmator = new_allocation_urmator;
	anterior = new_allocation_anterior;
	element = new_allocation_element;
}

//creeaza un nod in lista inlantuita unde se memoreaza informatia utila e
int MDO::creeazaNod(TElem e) { // complexitate-timp Theta(1)
	//daca s-ar folosi vector dinamic, s-ar redimensiona in cazul in care colectia ar fi plina (primLiber=0)
	int i = aloca();
	if (i != -1) { //exista spatiu liber in lista
		element[i] = e;
		urmator[i] = -1;
		anterior[i] = -1;
	}
	return i;
}

// adaugare element in MDO
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
void MDO::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	if (dimensiune == cp - 1) {
		redimensioneaza();
	}
	TElem elementul(c, v);
	auto nou = creeazaNod(elementul);
	//in cazul folosirii unui vector static, e posibil ca i sa fie -1 in cazul in care lista e plina
	if (nou != -1) {
		//dictionarul e vid => adaugarea primului element
		if (primul == -1) {
			urmator[nou] = primul;
			primul = nou;
		}
		//adaugare inainte de primul element, dupa relatie
		else if (!rel(element[primul].first, c)) {
			anterior[primul] = nou;
			urmator[nou] = primul;
			primul = nou;
		}
		//adaugare inauntrul dictionarului sau la finalul dictionarului
		else {
			//parcurgem lista pana gasim primul element al cheii cautate sau pana ajungem la final
			auto nodCurent = primul;
			while (urmator[nodCurent] != -1 && rel(element[urmator[nodCurent]].first, c) && c != element[nodCurent].first) {
				nodCurent = urmator[nodCurent];
			}

			//daca mai exista chei cu valoarea c, le parcurgem pana la ultima cheie cu aceasta valoare
			if (c == element[nodCurent].first) {
				while (urmator[nodCurent] != -1 && element[urmator[nodCurent]].first == c) {
					nodCurent = urmator[nodCurent];
				}
			}

			//facem conexiunile pentru a adauga noul nod
			urmator[nou] = urmator[nodCurent];
			anterior[nou] = nodCurent;
			//daca NU e ultimul nod din lista
			if (urmator[nodCurent] != -1)
				anterior[urmator[nodCurent]] = nou;
			urmator[nodCurent] = nou;
		}
		//incrementam dimensiunea
		dimensiune++;
	}
}

// cauta nodul care contine cheia si returneaza adresa primei pozitii pe care apare (sau nullptr)
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
int MDO::iteratorCheie(TCheie c) const {
	int point = primul;

	bool gasit = false;
	while (point != -1 && rel(element[point].first, c) && gasit == false) {
		if (element[point].first == c) {
			gasit = true;
		}
		else {
			point = urmator[point];
		}
	}

	if (gasit == true)
		return point;
	else
		return -1;
}

// cauta nodurile care contin cheia si returneaza un vector cu valorile corespunzatoare cheii mentionate (sau un vector gol)
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
vector<TValoare> MDO::cauta(TCheie c) const {
	/* de adaugat */
	int point = iteratorCheie(c);
	vector<TValoare> vector_valori;

	if (point == -1) {
		return vector_valori;
	}

	if (element[point].first == c) {
		while (point != -1 && element[point].first == c) {
			vector_valori.push_back(element[point].second);
			point = urmator[point];
		}
	}
	return vector_valori;
}

//sterge elementul care are o cheie, respectiv o valoare data si returneaza true daca elementul a fost sters, respectiv false in caz contrar
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
bool MDO::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	int pointer = iteratorCheie(c);
	if (pointer != -1) {
		//daca e primul si singurul element
		if (urmator[primul] == -1) {
			dealoca(primul);
			primul = -1;
		}
		//daca e primul element
		else if (element[primul].first == c && element[primul].second == v) {
			auto aux = urmator[primul];
			dealoca(primul);
			primul = aux;
			anterior[aux] = -1;
		}
		else {
			auto nodCurent = pointer;
			while (urmator[nodCurent] != -1 && (element[nodCurent].first != c || element[nodCurent].second != v)) {
				nodCurent = urmator[nodCurent];
			}

			//daca nu exista un nod cu valoarea data
			if (element[nodCurent].second != v || element[nodCurent].first != c) {
				return false;
			}
			//daca e ultimul element
			else if (urmator[nodCurent] == -1 && (element[nodCurent].first == c && element[nodCurent].second == v)) {
				dealoca(urmator[nodCurent]);
				urmator[nodCurent] = -1;
			}
			//daca e intre primul si ultimul element
			else {
				urmator[anterior[nodCurent]] = urmator[nodCurent];
				anterior[urmator[nodCurent]] = anterior[nodCurent];
				dealoca(nodCurent);
			}
		}
		dimensiune--;
		return true;
	}
	else {
		return false;
	}
}

//returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
int MDO::dim() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return this->dimensiune;
}

//verifica daca MDO e vid
bool MDO::vid() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return this->dimensiune == 0;
}

IteratorMDO MDO::iterator() const { // complexitate-timp Theta(1)
	return IteratorMDO(*this);
}

TValoare MDO::ceaMaiFrecventaValoare() const { // complexitate-timp Theta(n)
	unordered_map<TValoare, int> vals_map;
	int point = primul;
	bool gasit;
	while (point != -1) {
		gasit = false;
		int i = 0;
		if (vals_map.find(element[point].second) != vals_map.end()) {
			vals_map.at(element[point].second)++;
		}
		else {
			vals_map.insert({ element[point].second,0 });
		}
		point = urmator[point];
	}

	int max = -1;
	TValoare maxVal;
	for (const auto& val : vals_map)
		if (val.second > max) {
			max = val.second;
			maxVal = val.first;
		}

	if (max != -1)
		return maxVal;
	else
		return INT_MAX;
}

/*
	Complexitati:
		Caz favorabil: complexitate-timp Theta(1)
			- elementul nu exista in lista si s-ar afla inainte de prima pozitie

		Caz defavorabil = Caz mediu: complexitate-timp Theta(n)
			- se ajunge la parcurgerea listei
	Complexitate generala: complexitate-timp Theta(n)
*/
vector<TValoare> MDO::stergeValoriPentruCheie(TCheie cheie) {
	int pointer = iteratorCheie(cheie);
	vector<TValoare> vector_valori;
	if (pointer != -1) {
		vector_valori = cauta(cheie);
		for (int i = 0; i < vector_valori.size(); i++) {
			//sterge(cheie, vector_valori[i]);
			//daca e primul si singurul element
			if (urmator[primul] == -1) {
				dealoca(primul);
				primul = -1;
			}
			//daca e primul element
			else if (element[primul].first == cheie && element[primul].second == vector_valori[i]) {
				auto aux = urmator[primul];
				dealoca(primul);
				primul = aux;
				anterior[aux] = -1;
			}
			//daca e ultimul element
			else if (urmator[pointer] == -1 && (element[pointer].first == cheie && element[pointer].second == vector_valori[i])) {
				dealoca(urmator[pointer]);
				urmator[pointer] = -1;
			}
			//daca e intre primul si ultimul element
			else {
				auto aux_point = urmator[pointer];
				urmator[anterior[pointer]] = urmator[pointer];
				anterior[urmator[pointer]] = anterior[pointer];
				dealoca(pointer);
				pointer = aux_point;
			}
			dimensiune--;
		}
		return vector_valori;
	}
	else {
		return vector_valori;
	}
}

//destructor
MDO::~MDO() { // complexitate-timp Theta(n)
	/* de adaugat */
	while (primul != -1) {
		auto aux = primul;
		primul = urmator[primul];
		dealoca(aux);
	}
}