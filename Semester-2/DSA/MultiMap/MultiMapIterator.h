#pragma once
#include "MultiMap.h"
#include "SLLAIterator.h"

class MultiMapIterator {
public:
	MultiMapIterator(const MultiMap& c);
private:
	//contains a reference of the container it iterates over
	const MultiMap& c;
	/* representation specific for the iterator*/
	int currentPosition;
	int count;
	int size;
public:

	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
};
