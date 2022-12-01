
#include <iostream>
#include "List.h"

using namespace std;

void createList(List& l) {
	l.addToBeginning(make_tuple(2, 3, 2));
	l.addToBeginning(make_tuple(4, 5, 4));
	l.addToEnd(make_tuple(0, 9,2));
	l.addToBeginning(make_tuple(5, 7, 1));
	l.addToEnd(make_tuple(4, 3, 8));
}

void printListFW(List& l) {
    cout << "Original list:\n";
    ListIteratorFW itf = l.iterator_fw();
    while (itf.valid()) {
        cout << get<0>(itf.getCurrent()) << ","<< get<1>(itf.getCurrent()) << ","<< get<2>(itf.getCurrent()) << ' ';
        itf.next();
    }

}
void printListBW(List& l) {
    cout << "\nBackward list: \n";
    ListIteratorBW itb = l.iterator_bw();
    while (itb.valid()) {
        cout << get<0>(itb.getCurrent()) << ","<< get<1>(itb.getCurrent()) << ","<< get<2>(itb.getCurrent()) << ' ';
        itb.next();
    }
}
void modifyListFW(List& l) {
    ListIteratorFW itf = l.iterator_fw();
    TElem x;
    itf.first();
    while (itf.valid()) {
        x = make_tuple(get<0>(itf.getCurrent()) * 2, get<1>(itf.getCurrent()) * 2, get<2>(itf.getCurrent()) * 2);
        l.setElementFW(itf, x);
        itf.next();
    }

    cout << "\nModified list:\n";
    itf.first();
    while (itf.valid()) {
        cout<< get<0>(itf.getCurrent()) << ","<< get<1>(itf.getCurrent()) << ","<< get<2>(itf.getCurrent()) << ' ';
        itf.next();
    }
}
void modifyListBW(List& l) {
    ListIteratorBW itb = l.iterator_bw();
    TElem x;
    itb.first();
    while (itb.valid()) {
        x= make_tuple(get<0>(itb.getCurrent())*2, get<1>(itb.getCurrent())*2, get<2>(itb.getCurrent())*2);
        l.setElementBW(itb, x );
        itb.next();
    }

    cout << "\nReversed modified list:\n";
    itb.first();
    while (itb.valid()) {
        cout << get<0>(itb.getCurrent()) << ","<< get<1>(itb.getCurrent()) << ","<< get<2>(itb.getCurrent()) << ' ';
        itb.next();
    }
}

int main() {
	List myList;
	createList(myList);
    printListFW(myList);
    printListBW(myList);
    modifyListFW(myList);
    modifyListBW(myList);
	return 0;

}
