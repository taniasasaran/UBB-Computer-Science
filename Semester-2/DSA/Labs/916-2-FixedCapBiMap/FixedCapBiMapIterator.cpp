#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->current_index = 0;
}


void FixedCapBiMapIterator::first() {
    this->current_index = 0;
}


void FixedCapBiMapIterator::next() {
    if (this->current_index < this->map.size_of_Values)
	    this->current_index ++;
    else
        throw exception();
}


TElem FixedCapBiMapIterator::getCurrent(){
    if (this->valid()) {
        return this->map.Values[this->current_index];
    } else{
        throw exception();
    }
}


bool FixedCapBiMapIterator::valid() const {
	return this->current_index < this->map.size_of_Values;
}



