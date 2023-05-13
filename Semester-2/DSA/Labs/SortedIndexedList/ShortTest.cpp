#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll(){
    SortedIndexedList list = SortedIndexedList(relation1);
    assert(list.size() == 0);
    assert(list.isEmpty());
    //test range
    assert(list.getRange() == -1);
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    list.add(3);
    //test range
    assert(list.getRange() == 2);
    assert(list.remove(0) == 1);
    assert(list.remove(0) == 3);
    assert(list.size() == 0);
    assert(list.isEmpty());

    list.add(1);
    list.add(3);
    list.add(5);
    list.add(4);
    assert(list.removeFromKtoK(2)==2);
    list.add(2);
    assert(list.removeFromKtoK(3)==1);
}
