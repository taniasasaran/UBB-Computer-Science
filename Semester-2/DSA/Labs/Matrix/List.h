#pragma once
#include<tuple>
using namespace std;

//typedef int TElem;
typedef tuple<int, int, int> TELEM;

class ListIteratorFW;
class ListIteratorBW;

class List {
private:
	struct DLLNode;
	typedef DLLNode *PNode;
	PNode head;
    PNode tail;

public:
	friend class ListIteratorFW;
    friend class ListIteratorBW;
	List();

	void addToBeginning(TELEM elem);
    void addToEnd(TELEM elem);

	// changes the element from the current position to the given one.
	//returns the old value from the position
	//throws exception if the position is not valid
    TELEM setElementFW(ListIteratorFW pos, TELEM e);
    TELEM setElementBW(ListIteratorBW pos, TELEM e);
    //this function deletes an element of the list by changing the links in the prev and next fields   O(1)
    void delete_pos(ListIteratorFW pos);
	//other operations
	// ...
	ListIteratorFW iterator_fw() const;
    ListIteratorBW iterator_bw() const;

    ~List();

	List(const List&)=delete;
	List& operator=(const List&)=delete;

};


class ListIteratorFW {
	friend class List;
private:
	ListIteratorFW(const List& l);
	const List& list;
	List::PNode currentElement;
public:
    friend class List;
	void first();
	void next();
	bool valid() const;
    TELEM getCurrent() const;

};


class ListIteratorBW{
    friend class List;
private:
    ListIteratorBW(const List& l);
    const List& list;
    List::PNode currentElement;
public:
    friend class List;
    void first();
    void next();
    bool valid() const;
    TELEM getCurrent() const;
};

