#pragma once
#include<utility>
#include <vector>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
class SLLAIterator;

class SLLA {	
public:
	TElem* elements;
	int size;
	int* next;
	int capacity;
	int head;
	int firstEmpty;
	friend class SLLAIterator;
	friend class MultiMap;
	friend class MultiMapIterator;
private:
	void resize();
public:
	std::vector <TValue> searchValue(TKey);
	TElem getElement(int);
	void add(TElem);
	void remove(TElem);
	int getSize() const { return this->size; };
	bool isEmpty() { return this->size == 0; };
	int getHead() { return this->head; };
	int* getNext() { return this->next; };
	std::pair<int,int> search(TElem);
	SLLA();
	~SLLA();
	SLLAIterator iterator() const;
};