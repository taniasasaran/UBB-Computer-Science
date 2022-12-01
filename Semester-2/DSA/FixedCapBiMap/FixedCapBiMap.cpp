#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	//TODO - Implementation
}

FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
}

bool FixedCapBiMap::add(TKey c, TValue v){
	//TODO - Implementation
	return false;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	return std::pair<TValue, TValue>(NULL_TVALUE, NULL_TVALUE);
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	return false;
}


int FixedCapBiMap::size() const {
	//TODO - Implementation
	return 0;
}

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	return false;
}

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	return false;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



