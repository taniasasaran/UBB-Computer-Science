#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
    this->current_index = 0;
}


void SortedSetIterator::first() {
    this->current_index = 0;
}


void SortedSetIterator::next() {
    if (this->current_index < this->multime.size_of_Values)
        this->current_index ++;
    else
        throw exception();
}


TElem SortedSetIterator::getCurrent()
{
    if (this->valid()) {
        return this->multime.Values[this->current_index];
    } else{
        return false;
    }
}

bool SortedSetIterator::valid() const {
    return this->current_index >= 0 && this->current_index < this->multime.size_of_Values;
}

