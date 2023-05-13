#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111
#define CAPACITY 1000
struct Node {
    TComp info;
    int nrLeft;
};

class SortedIndexedList {
private:
    friend class ListIterator;
private:
    Node** elems;
    int* data;
    Relation R;
    int sizeBST;
    int max_capacity;
public:
    // constructor
    //Complexity: BC=AC=WC=Theta(1)
    SortedIndexedList(Relation r);

    // returns the size of the list
    //Complexity: BC=AC=WC=Theta(1)
    int size() const;

    //checks if the list is empty
    //Complexity: BC=AC=WC=Theta(1)
    bool isEmpty() const;

    // returns an element from a position
    //throws exception if the position is not valid
    // Complexity: WC=O(n) when we have a degenerate tree and the Node we need is a leaf (we have to parse through all of its nodes)
    //             BC=O(1) when the Node we need is the root
    //			   AC=O(log n)
    TComp getElement(int pos) const;

    // adds an element in the sortedList (to the corresponding position)
    // Complexity: WC=O(n) when we have a degenerate tree and we add the Node at the end (it will be a leaf) - we need to parse through all of its other nodes
    //             BC=O(1) when the Node we need is the root
    //			   AC=O(log n)
    void add(TComp e);

    // removes an element from a given position
    //returns the removed element
    //throws an exception if the position is not valid
    // Complexity: WC=O(n) when we have a degenerate tree and the Node to be deleted is a leaf - we need to parse through all of its other nodes
    //             BC=O(1) when the Node to be deleted is the root and the tree has a size of 1 (the root is the only element)
    //			   AC=O(log n)
    TComp remove(int pos);

    // searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    // Complexity: WC=O(n) when we have a degenerate tree and the Node we need is a leaf (we have to parse through all of its nodes)
    //             BC=O(1) when the Node we need is the root
    //			   AC=O(log n)
    int search(TComp e) const;

    //returns the successor of a given element
    // Complexity: WC=O(n^2) when we have a degenerate tree and we need to get to the leaf - we need to parse through all of its other nodes as well - and the parent function has a worst time complexity
    //             BC=O(n) when the parent function has a best case complexity
    //			   AC=O(log^2 n)
    TComp successor(TComp e);

    //returns the parent of a given element
    // Complexity: WC=O(n) when we have a degenerate tree and the Node whose parent we need is a leaf - we need to parse through all of its other nodes as well
    //             BC=O(1) when the tree has a size of 1 (only contains the root)
    //			   AC=O(log n)
    TComp parent(TComp e);

    //modifies the position of the elements after the deletion of a Node
    // Complexity: WC=O(n) when we have a degenerate tree and we need to get to the leaf - we need to parse through all of its other nodes as well
    //             BC=O(1) when the tree has a size of 1 (only contains the root)
    //			   AC=O(log n)
    void decrease(int i) const;

    //returns the difference between the maximum and the minimum element (assume integer values)
    //if the SortedList is empty the range is -1
    // Complexity: WC=O(n) when we have a degenerate tree and the minimum/maximum is a leaf - we need to parse through all of its nodes once
    //             BC=O(1) when the tree has a size of 1 (only contains the root)
    //			   AC=O(log n)
    int getRange() const;

    int removeFromKtoK(int k);

    // returns an iterator set to the first element of the list or invalid if the list is empty
    //Complexity: BC=AC=WC=Theta(1)
    ListIterator iterator();

    //destructor
    //Complexity: BC=AC=WC=Theta(1)
    ~SortedIndexedList();

    void resize();
};