#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
    friend class SortedBag;

private:
    const SortedBag& bag;
    SortedBagIterator(const SortedBag& b);
    int currentIndex;
    int firstIndex;

public:
    TElem getCurrent();
    bool valid();
    void next();
    void first();
    void previous();
};
