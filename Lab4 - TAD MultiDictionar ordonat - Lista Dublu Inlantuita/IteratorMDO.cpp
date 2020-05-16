#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) { // complexitate-timp Theta(1)
	/* de adaugat */
	this->curent = d.primul;
}

void IteratorMDO::prim() { // complexitate-timp Theta(1)
	/* de adaugat */
	this->curent = dict.primul;
}

void IteratorMDO::urmator() { // complexitate-timp Theta(1)
	/* de adaugat */
	if (this->curent == -1) {
		throw exception();
	}
	this->curent = dict.urmator[curent];
}

bool IteratorMDO::valid() const { // complexitate-timp Theta(1)
	/* de adaugat */
	return this->curent != -1;
}

TElem IteratorMDO::element() const { // complexitate-timp Theta(1)
	/* de adaugat */
	if (this->curent == -1) {
		throw exception();
	}
	return dict.element[curent];
}