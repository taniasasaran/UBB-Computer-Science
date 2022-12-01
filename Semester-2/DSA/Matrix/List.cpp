#include "List.h"
#include <exception>
using namespace std;

struct List::DLLNode	{
		TELEM info;
		PNode prev;
        PNode next;
		DLLNode(PNode p, TELEM e, PNode n);
};

List::DLLNode::DLLNode(PNode p, TELEM e, PNode n) {
	info = e;
    prev = p;
	next = n;
}


List::List() { // O(1)
	head = nullptr;
    tail = nullptr;
}

// O(1)
void List::addToBeginning(TELEM e) {
	PNode pn = new DLLNode(nullptr, e, nullptr);
	pn->next = head;
	head = pn;
    if(tail == nullptr)
        tail = pn;
    else{
        head->next->prev = pn;
    }
}

// O(1)
void List::addToEnd(TELEM e) {
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
//throws exception if the position is not valid    O(1)
TELEM List::setElementFW(ListIteratorFW pos, TELEM e){
	PNode pn;
	pn = pos.currentElement;
	if (pn == nullptr){
		throw exception();
	} else {
        TELEM old;
		old = pn->info;
        pn->info = e;
		return old;
	}
}

// O(1)
TELEM List::setElementBW(ListIteratorBW pos, TELEM e){
    PNode pn;
    pn = pos.currentElement;
    if (pn == nullptr){
        throw exception();
    } else {
        TELEM old;
        old = pn->info;
        pn->info = e;
        return old;
    }
}

// O(1)
ListIteratorFW List::iterator_fw() const {
	return ListIteratorFW(*this);
}

// O(1)
ListIteratorBW List::iterator_bw() const {
    return ListIteratorBW(*this);
}

List::~List() {     //O(1)
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


TELEM ListIteratorFW::getCurrent() const {
    if ( currentElement == nullptr) throw exception();
    return currentElement->info;
}

// ----------------------------------------------------


ListIteratorBW::ListIteratorBW(const List& l) : list(l) {
    currentElement = l.tail;
}


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


TELEM ListIteratorBW::getCurrent() const {
    if ( currentElement == nullptr) throw exception();
    return currentElement->info;
}








void List::delete_pos(ListIteratorFW pos){
    PNode pn;
    pn = pos.currentElement;
    if (pn == nullptr){
        throw exception();
    } else {
        pn->next->prev = pn->prev;
        pn->prev->next = pn->next;
    }
}