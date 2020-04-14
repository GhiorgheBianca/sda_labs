#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lo(lo) { // complexitate-timp Theta(1)
	/* de adaugat */
	this->curent = lo.primul;
}

void Iterator::prim() { // complexitate-timp Theta(1)
	/* de adaugat */
	this->curent = lo.primul;
}

void Iterator::urmator() { // complexitate-timp Theta(1)
	/* de adaugat */
	if (valid())
		this->curent = this->curent->getUrmator();
	else
		throw std::exception();
}

bool Iterator::valid() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return (curent != nullptr);
}

TElement Iterator::element() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return curent->getElement();
}