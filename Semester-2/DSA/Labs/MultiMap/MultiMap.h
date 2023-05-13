#pragma once

#include "SLLA.h"
#include <vector>
#include<utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

class MultiMapIterator;

class MultiMap{

	friend class MultiMapIterator;
private:
	/* representation of the MultiMap */
	SLLA* elements;

public:
	//constructor);
	MultiMap();
	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

    std::vector<TValue> removeKey(TKey c);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	std::vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;


	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//destructor
	~MultiMap();
};