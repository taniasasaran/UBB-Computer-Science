#include "MultiMapIterator.h"
#include <exception>
using namespace std;

MultiMapIterator::MultiMapIterator(const MultiMap& map) : c(map) {
	this->currentPosition = map.elements->getHead();
	this->count = 0;
	this->size = map.elements->getSize();
	//theta(1)
}

void MultiMapIterator::first() {
	this->currentPosition = this->c.elements->getHead();
	this->count = 0;
	this->size = this->c.elements->getSize();
	//theta(1)
}

void MultiMapIterator::next() {
	if (this->valid() == false)
		throw std::exception();
	this->currentPosition = this->c.elements->getNext()[this->currentPosition];
	this->count++;
	//theta(1)
}

bool MultiMapIterator::valid() const{
	if (this->size == 0)
		return false;
	if (this->count != this->size)
		return true;
	return false;
}

TElem MultiMapIterator::getCurrent() const {		
	if (this->valid() == false)
        throw std::exception();
//	return this->c.elements->getElement(this->currentPosition);
	return this->c.elements->elements[this->currentPosition];
	//theta(1)
}