#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    this->currentPosition = 0;
}

void ListIterator::first(){
    this->currentPosition = 0;
}

void ListIterator::next(){

    if (!this->valid())
    {
        throw exception();
    }
    ++this->currentPosition;
}

bool ListIterator::valid() const{
    if (this->currentPosition < list.size())return true;
    return false;
}

TComp ListIterator::getCurrent() const{
    if (!this->valid())
    {
        throw exception();
    }
    return list.getElement(this->currentPosition);
}

