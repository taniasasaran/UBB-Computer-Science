#include "List.h"
#include <exception>
using namespace std;

struct List::DLLNode	{
		TElem info;
		PNode prev;
        PNode next;
		DLLNode(PNode p, TElem e, PNode n);
};

List::DLLNode::DLLNode(PNode p, TElem e, PNode n) {
	info = e;
    prev = p;
	next = n;
}


List::List() {
	head = nullptr;
    tail = nullptr;
}

void List::addToBeginning(TElem e) {
	PNode pn = new DLLNode(nullptr, e, nullptr);
	pn->next = head;
	head = pn;
    if(tail == nullptr)
        tail = pn;
    else{
        head->next->prev = pn;
    }
}

void List::addToEnd(TElem e) {
    PNode pn = new DLLNode(nullptr, e, nullptr);
    pn->prev = tail;
    tail = pn;
    if(head == nullptr)
        head = pn;
    else{
        tail->prev->next = pn;
    }
}

// changes the element from the current position to the given one.
//returns the old value from the position
//throws exception if the position is not valid
TElem List::setElementFW(ListIteratorFW pos, TElem e){
	PNode pn;
	pn = pos.currentElement;
	if (pn == nullptr){
		throw exception();
	} else {
		TElem old;
		old = pn->info;
		pn->info = e;
		return old;
	}
}

TElem List::setElementBW(ListIteratorBW pos, TElem e){
    PNode pn;
    pn = pos.currentElement;
    if (pn == nullptr){
        throw exception();
    } else {
        TElem old;
        old = pn->info;
        pn->info = e;
        return old;
    }
}

ListIteratorFW List::iterator_fw() const {
	return ListIteratorFW(*this);
}

ListIteratorBW List::iterator_bw() const {
    return ListIteratorBW(*this);
}

List::~List() {
	while (head != nullptr) {
		PNode p = head;
		head = head->next;
		delete p;
	}
}

// ----------------------------------------------------

ListIteratorFW::ListIteratorFW(const List& l) : list(l) {
	currentElement = l.head;
}

void ListIteratorFW::first() {
    currentElement = list.head;
}


void ListIteratorFW::next() {
	if ( currentElement == nullptr) throw exception();
    currentElement = currentElement->next;
}


bool ListIteratorFW::valid() const {
	return currentElement != nullptr;
}


TElem ListIteratorFW::getCurrent() const {
    if ( currentElement == nullptr) throw exception();
    return currentElement->info;
}

ListIteratorBW::ListIteratorBW(const List& l) : list(l) {
    currentElement = l.tail;
}

// ----------------------------------------------------

void ListIteratorBW::first() {
    currentElement = list.tail;
}


void ListIteratorBW::next() {
    if ( currentElement == nullptr) throw exception();
    currentElement = currentElement->prev;
}


bool ListIteratorBW::valid() const {
    return currentElement != nullptr;
}


TElem ListIteratorBW::getCurrent() const {
    if ( currentElement == nullptr) throw exception();
    return currentElement->info;
}
