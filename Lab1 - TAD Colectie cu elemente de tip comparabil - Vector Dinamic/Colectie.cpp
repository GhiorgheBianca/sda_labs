#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) { // complexitate-timp Theta(1)
	/* de adaugat */
	return e1 <= e2;
}

Colectie::Colectie() {
	/* de adaugat */
	this->size = 0;
	this->capacity = 100;
	this->vector_elemente = new TElem[this->capacity];
	this->vector_contor = new int[this->capacity];
}

void Colectie::adauga(TElem elem) { // complexitate-timp amortizata Theta(n)
	/* de adaugat */
	// aloca spatiu nou daca este nevoie
	if (this->size == this->capacity - 1)
	{
		this->capacity *= 2;
		int* new_allocation_contor = new int[this->capacity];
		TElem* new_allocation_elemente = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++)
		{
			new_allocation_contor[i] = this->vector_contor[i];
			new_allocation_elemente[i] = this->vector_elemente[i];
		}
		delete[] this->vector_contor;
		delete[] this->vector_elemente;
		this->vector_contor = new_allocation_contor;
		this->vector_elemente = new_allocation_elemente;
	}

	int poz_gasita = this->binarySearch(elem);
	if (this->vector_elemente[poz_gasita] == elem)
	{
		// incrementarea contorului daca elementul exista deja in vector
		this->vector_contor[poz_gasita]++;
	}
	else
	{
		// insereaza undeva in vector
		for (int i = this->size; i > poz_gasita; i--)
		{
			this->vector_elemente[i] = this->vector_elemente[i - 1];
			this->vector_contor[i] = this->vector_contor[i - 1];
		}
		// insereaza la final | continuarea pentru inserare undeva in vector
		this->vector_elemente[poz_gasita] = elem;
		this->vector_contor[poz_gasita] = 1;
		this->size++;
	}
}


bool Colectie::sterge(TElem elem) { // complexitate-timp Theta(n)
	/* de adaugat */
	int poz_gasita = this->binarySearch(elem);
	if (this->vector_elemente[poz_gasita] == elem && !this->vida())
	{
		if (this->vector_contor[poz_gasita] != 1)
			this->vector_contor[poz_gasita]--;
		else
		{
			for (int j = poz_gasita; j < this->size - 1; j++)
			{
				this->vector_elemente[j] = this->vector_elemente[j + 1];
				this->vector_contor[j] = this->vector_contor[j + 1];
			}
			this->size--;
		}
		return true;
	}
	return false;
}


int Colectie::binarySearch(TElem elem) const { // complexitate-timp O(log2(n))
	if (this->size == 0 || rel(elem,this->vector_elemente[0]))
		return 0;
	if (!rel(elem,this->vector_elemente[this->size - 1]))
		return this->size;
	int left, right, middle;
	left = 0;
	right = this->size;
	while (left < right - 1)
	{
		middle = (left + right) / 2;
		if (rel(elem,this->vector_elemente[middle]))
			right = middle;
		else
			left = middle;
	}
	return right;
}


bool Colectie::cauta(TElem elem) const { // complexitate-timp O(log2(n))
	/* de adaugat */
	int result = this->binarySearch(elem);
	if (this->vector_elemente[result] == elem)
		return true;
	return false;
}


int Colectie::nrAparitii(TElem elem) const { // complexitate-timp O(log2(n))
	/* de adaugat */
	int poz_gasita = this->binarySearch(elem);
	if (this->vector_elemente[poz_gasita] == elem)
	{
		return this->vector_contor[poz_gasita];
	}
	return 0;
}



int Colectie::dim() const { // complexitate-timp Theta(n)
	/* de adaugat */
	int size = 0;
	for (int i = 0; i < this->size; i++)
	{
		size += this->vector_contor[i];
	}
	return size;
}


bool Colectie::vida() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return this->size == 0;
}


IteratorColectie Colectie::iterator() const { // complexitate-timp Theta(1)
	return IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	delete[] this->vector_elemente;
	delete[] this->vector_contor;
}