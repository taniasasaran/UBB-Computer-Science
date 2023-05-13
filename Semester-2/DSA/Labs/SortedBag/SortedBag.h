#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

#include <utility>

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef std::pair<TComp, int> TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111
//#define NULL_TELEM std::pair<-11111, 0>
#define CAPACITY 100000

class SortedBagIterator;

class SortedBag {
    friend class SortedBagIterator;

private:
    Relation relation;
    int m;
    TElem* elems;
    int* next;
    int first_free;
    int length;
    int no_elems;
public:
    int hash(TComp e);
    //constructor
    SortedBag(Relation r);

    //adds an element to the sorted bag
    void add(TComp e);
    void changeFirstEmpty();
    void resizeAndRehash();
    //removes one occurrence of an element from a sorted bag
    //returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
    bool remove(TComp e);

    //checks if an element appears is the sorted bag
    bool search(TComp e);

    //returns the number of occurrences for an element in the sorted bag
    int nrOccurrences(TComp e);

    //returns the number of elements from the sorted bag
    int size();

    //returns an iterator for this sorted bag
    SortedBagIterator iterator();

    //checks if the sorted bag is empty
    bool isEmpty();

    void sortWithinHashValue(int v);

    //destructor
    ~SortedBag();

    int removeAllOccurrences(TComp e);
};