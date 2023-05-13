#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    this->currentIndex = 0;
    while (this->currentIndex < this->bag.m && (this->bag.elems[this->currentIndex].first == NULL_TCOMP))
        this->currentIndex++;
    this->firstIndex = this->currentIndex;
}
//Theta(1)

TElem SortedBagIterator::getCurrent() {
    if (this->currentIndex >= this->bag.m)
        throw exception();
    return this->bag.elems[this->currentIndex];
}
//Theta(1)

bool SortedBagIterator::valid() {
    if (this->bag.elems[this->currentIndex].first == NULL_TCOMP || this->currentIndex >= this->bag.m)
        return false;
    else
        return true;
}
//Theta(1)

void SortedBagIterator::next() {
    if (this->currentIndex >= this->bag.m)
        throw exception();
    this->currentIndex++;
    while (this->currentIndex < this->bag.m && (this->bag.elems[this->currentIndex].first == NULL_TCOMP))
        this->currentIndex++;
}
//Theta(1)

void SortedBagIterator::previous() {
    if (!this->valid())
        throw exception();
    if (this->currentIndex == this->firstIndex)
        this->currentIndex = this->bag.m;
    else {
        this->currentIndex--;
        while ((this->bag.elems[this->currentIndex].first == NULL_TCOMP) && this->currentIndex != this->firstIndex)
            this->currentIndex--;
    }
}

void SortedBagIterator::first() {
    this->currentIndex = 0;
    while (this->currentIndex < this->bag.m && (this->bag.elems[this->currentIndex].first == NULL_TCOMP))
        this->currentIndex++;
    this->firstIndex = this->currentIndex;
}
//Theta(1)
