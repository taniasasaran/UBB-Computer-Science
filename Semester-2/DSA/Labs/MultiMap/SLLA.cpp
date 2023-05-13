#include "SLLA.h"
#include "SLLAIterator.h"
#include<exception>
#include <iostream>
#include <vector>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
using namespace std;

SLLA::SLLA() {
	this->capacity = 3;
	this->elements = new TElem[this->capacity];
	this->next =new int[this->capacity];
	this->head = -1;
	for (int i = 0; i < this->capacity; i++)
		this->next[i] = i + 1;
	this->next[this->capacity-1] = -1;
	this->firstEmpty = 0;
	this->size = 0;
	//theta(n);
}

SLLA::~SLLA() {
	delete[] next;
	delete[] elements;
    //O(1)
}

TElem SLLA::getElement(int position) {
	auto current = this->head;
	if (position == 0)
		return this->elements[this->head];
	while (current!=-1 and position != 0) {
		current = this->next[current];
		position--;
	}
	if (current == -1)
		throw exception();
	return this->elements[current];
	//O(n)
}
void SLLA::resize(){
	this->capacity *= 2;
	TElem* elems = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		elems[i] = this->elements[i];
	delete[] this->elements;
	this->elements = elems;
	int* nextNew = new int[this->capacity];
	for (int i = 0; i < this->size; i++)
		nextNew[i] = this->next[i];
	for (int i = this->size; i < this->capacity; i++) {
		nextNew[i] = i + 1;
	}
	nextNew[this->capacity-1] = -1;
	delete[] this->next;
	this->next = nextNew;
	this->firstEmpty = this->size;
	//theta(n)
}

std::pair<int,int> SLLA::search(TElem element) {
	auto current = this->head;
	int count = 0;
	int previous = -1;
	while (count!=this->size and current != -1 and this->elements[current] != element) {
		previous = current;
		current = this->next[current];
	}
	return make_pair(previous,current);
	//O(n)
}

std::vector<TValue> SLLA::searchValue(TKey c)
{
	std::vector<TValue> elems;
	int current = this->head;
	int count = 0;
	while (count!=this->size and current != -1) {
		if (this->elements[current].first == c)
			elems.push_back(this->elements[current].second);
			current = this->next[current];
			count++;
	}
	return elems;
	//O(n)
}

void SLLA::add(TElem element) {
	if (this->firstEmpty==-1) {
		this->resize();
	}
	auto occupiedPosition = this->firstEmpty;
	this->elements[this->firstEmpty] = element;
	this->firstEmpty = this->next[this->firstEmpty];
	this->next[occupiedPosition] = -1;
	if (this->head == -1)
		this->head = occupiedPosition;
	else {
		this->next[occupiedPosition] = this->head;
		this->head = occupiedPosition;
	}
	this->size++;
	//O(1)
}

void SLLA::remove(TElem element) {
	std::pair<int,int> positions = this->search(element);
	int previous = positions.first;
	int current = positions.second;
	if (current == -1)
		throw std::exception();
	if (current != this->head) {
		this->next[previous] = this->next[current];
		this->next[current] = this->firstEmpty;
		this->firstEmpty = current;
	}
	else {
		this->head = this->next[this->head];
		this->next[current] = firstEmpty;
		this->firstEmpty = current;
	}
	this->size--;
	//O(n)
}

SLLAIterator SLLA::iterator() const {
	return SLLAIterator(*this);
	//theta(1)
}