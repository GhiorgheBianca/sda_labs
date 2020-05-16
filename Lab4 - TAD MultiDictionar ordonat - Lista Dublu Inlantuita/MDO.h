#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
private:
	/* aici e reprezentarea */
	Relatie rel;
	int dimensiune;
	int cp = 100;
	//vectorul dinamic de elemente de tip TElem (cu spatiu variabil de memorare - poate fi extins)
	TElem* element;
	//vectorii dinamici pentru legaturi - lista dublu inlantuita
	int* urmator;
	int* anterior;
	//referinta catre primul element al listei
	int primul;
	//referinta catre primul element din lista spatiului liber
	int primLiber;

	//functii pentru alocarea/dealocarea unui spatiu liber
	//se returneaza pozitia unui spatiu liber in lista
	int aloca();
	//dealoca spatiul de indice i
	void dealoca(int i);
	//functie privata care creeaza un nod in lista inlantuita
	int creeazaNod(TElem e);
	//functie privata care gaseste primul nod care are cheia mentionata
	int iteratorCheie(TCheie c) const;
	//functie privata care redimensioneaza listele
	void redimensioneaza();

public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

	// elimina o cheie impreuna cu toate valorile sale
	// returneaza un vector cu valorile care au fost anterior asociate acestei chei (si au fost eliminate)
	vector<TValoare> stergeValoriPentruCheie(TCheie cheie);

	// returneaza valoarea care apare cel mai frecvent in multidictionar. Daca mai multe valori apar cel mai frecvent, se returneaza una (oricare) dintre ele.
	// Daca multidictionarul este vid, operatia returneaza NULL_TVALOARE
	TValoare ceaMaiFrecventaValoare() const;

};