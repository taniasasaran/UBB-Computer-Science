#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	//TODO - Implementation
}

int SortedIteratedList::size() const {
	//TODO - Implementation
	return 0;
}

bool SortedIteratedList::isEmpty() const {
	//TODO - Implementation
	return false;
}

ListIterator SortedIteratedList::first() const {
	//TODO - Implementation
	return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	//TODO - Implementation
	return NULL_TCOMP;
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	//TODO - Implementation
	return NULL_TCOMP;
}

ListIterator SortedIteratedList::search(TComp e) const{
	//TODO - Implementation
	return ListIterator(*this);
}

void SortedIteratedList::add(TComp e) {
	//TODO - Implementation
}

SortedIteratedList::~SortedIteratedList() {
	//TODO - Implementation
}
