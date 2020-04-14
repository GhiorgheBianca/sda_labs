#include <exception>
#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	this->elementCurent = col.vector_elemente[0];
	this->pozitiaCurenta = 0;
	this->frecventaCurenta = col.vector_contor[0];
}

TElem IteratorColectie::element() const { // complexitate-timp Theta(1)
	/* de adaugat */
	if (this->valid() == true)
		return this->elementCurent;
	else
		throw std::exception::exception();
}

bool IteratorColectie::valid() const { // complexitate-timp Theta(1)
	/* de adaugat */
	if (this->col.vida() == true)
		return false;
	if (this->pozitiaCurenta >= col.size)
		return false;
	if (this->col.vector_contor[pozitiaCurenta] == 0)
		return false;
	return true;
}

void IteratorColectie::urmator() { // complexitate-timp Theta(1)
	/* de adaugat */
    if (this->valid() == true)
    {
        if (this->frecventaCurenta == 0)
        {
            // daca frecventa curenta este 0, inseamna ca frecventa nu este actualizata si trebuie preluata din vectorul de frecvente
            this->frecventaCurenta = this->col.vector_contor[this->pozitiaCurenta];
            this->frecventaCurenta--;
            if (this->frecventaCurenta == 0)
            {
				// se actualizeaza elementul curent si pozitia curenta
                this->pozitiaCurenta++;
                this->elementCurent = this->col.vector_elemente[this->pozitiaCurenta];
            }
        }
        else
        {
            this->frecventaCurenta--;
            if (this->frecventaCurenta == 0 && this->pozitiaCurenta != col.size - 1)
            {
				// se actualizeaza elementul curent si pozitia curenta
                this->pozitiaCurenta++;
                this->elementCurent = this->col.vector_elemente[this->pozitiaCurenta];
            }
        }
    }
	else
		throw std::exception::exception();
}

void IteratorColectie::prim() { // complexitate-timp Theta(1)
	/* de adaugat */
	if (col.size > 0) 
	{
		this->pozitiaCurenta = 0;
		this->elementCurent = col.vector_elemente[this->pozitiaCurenta];
		this->frecventaCurenta = col.vector_contor[this->pozitiaCurenta];
	}
	else 
	{
		this->frecventaCurenta = 0;
	}
}