#pragma once
#include "SLLA.h"

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
class SLLAIterator {
private:
	//Constructor receives a reference of the container.
	SLLAIterator(const SLLA& c);

	//contains a reference of the container it iterates over
	const SLLA& c;
	/* representation specific for the iterator*/
	int currentKey;
	int elementsIterated;
	friend class SLLA;
public:

	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;

};