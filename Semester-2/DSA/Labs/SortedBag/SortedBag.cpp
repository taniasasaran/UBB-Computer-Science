
#include <valarray>
#include <vector>
#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->relation = r;
    this->m = CAPACITY;
    this->length = 0;
    this->no_elems = 0;
    this->elems = new TElem[this->m];
    this->next = new int[this->m];
    int index;
    for(index = 0; index < this->m; index++) {
        this->elems[index].first = NULL_TCOMP;
        this->elems[index].second = 0;
        this->next[index] = -1;
    }
    this->first_free = 0;
}
//Theta(1)

int SortedBag::hash(TComp c) {
    return abs(c) % (this->m);
}
//Theta(1)

void SortedBag::changeFirstEmpty() {
    this->first_free = this->first_free + 1;
    while(this->first_free < this->m && this->elems[this->first_free].first != NULL_TCOMP)
        this->first_free = this->first_free + 1;
}
//AC:theta(1)  WC:theta(length)  AC:O(length)

void SortedBag::resizeAndRehash() {
    int currentLength = this->length;
    int currentM = this->m;
    this->m = this->m * 2;
    int index;
    auto oldElements = new TElem[currentM];
    for(index = 0; index < currentM; index++) {
        oldElements[index] = this->elems[index];
    }
    delete[] this->elems;
    this->elems = new TElem[this->m];

    delete[] this->next;
    this->next = new int[this->m];

    for(index = 0; index < this->m; index++) {
        this->elems[index].first = NULL_TCOMP;
        this->next[index] = -1;
    }
    this->first_free = 0;

    for(index = 0; index < currentM; index++) {
        if (oldElements[index].first != NULL_TCOMP)
            for(int i=0; i<oldElements[index].second; i++)
                add(oldElements[index].first);
    }
    this->length = currentLength;

    delete[] oldElements;
}
// theta(length)

void SortedBag::sortWithinHashValue(int value) {
    TElem *hash_elems = new TElem[length];
    int *hash_positions = new int[length];
    int size = 0;
    int position = value;
    TElem elem = elems[value];
    while (true) {
        if (hash(elem.first) == value) {
            hash_elems[size] = elem;
            hash_positions[size] = position;
            size++;
        }
        if (next[position] == -1)
            break;
        position = next[position];
        elem = elems[position];
    }

    //bubble-sort
    int i, j;
    for (i = 0; i < size - 1; i++)

        // Last i elements are already
        // in place
        for (j = 0; j < size - i - 1; j++)
            if (!relation(hash_elems[j].first, hash_elems[j + 1].first))
                swap(hash_elems[j], hash_elems[j + 1]);


    for (i = 0; i < size; i++){
        elems[hash_positions[i]].first = hash_elems[i].first;
        elems[hash_positions[i]].second = hash_elems[i].second;
    }
}
// BC:theta(1), WC: theta(length^2), AC: O(length^2)

void SortedBag::add(TComp e) {
    TElem element;
    element.first = e;
    element.second = 1;
    int hashValue = this->hash(e);
    if (this->elems[hashValue].first == NULL_TCOMP) {
        if(hashValue == first_free)
            this->changeFirstEmpty();
        this->elems[hashValue] = element;
        this->next[hashValue] = -1;
        this->length++;
        this->no_elems++;
        return;
    } else {
        int currentPosition = hashValue;
        while (this->next[currentPosition] != -1 && this->elems[currentPosition].first != e) {
            currentPosition = this->next[currentPosition];
        }
        if (this->elems[currentPosition].first == e) {
            this->elems[currentPosition].second++;
            this->length++;
            return;
        }
        if(this->first_free == this->m)
            this->resizeAndRehash();
        if (this->next[currentPosition] == -1) {
            this->elems[first_free] = element;
            this->next[first_free] = -1;
            this->next[currentPosition] = first_free;
            this->changeFirstEmpty();
            this->length++;
            this->no_elems++;
            sortWithinHashValue(hashValue);
            return;
        }
    }
}
//BC: Theta(1), WC: Theta(length), Total: O(length)


bool SortedBag::remove(TComp e) {
    int current = this->hash(e);
    int check;
    int prev = -1;
    while (current != -1 && this->elems[current].first != e) {
        prev = current;
        current = this->next[current];
    }
    if(search(e))
    {
        if(this->elems[current].second > 1) {
            this->elems[current].second--;
            this->length--;
            return true;
        }
    }
    if (current == -1) {
        return false;
    } else{
        //modify the elems array
        bool over = false;
        do {
            int position = this->next[current];
            int prevPosition = current;
            while (position != -1 && this->hash(this->elems[position].first) != hash(current)) {
                prevPosition = position;
                position = this->next[position];
            }
            if (position == -1)
                over = true;
            else {
                this->elems[current] = this->elems[position];
                prev = prevPosition;
                current = position;
            }
        } while (!over);
        //modify the next array
        if (prev == -1) {
            int idx = 0;
            while (idx < this->m && prev == -1)
                if (this->next[idx] == current) {
                    prev = idx;
                }else {
                    idx = idx + 1;
                }
        }
        if (prev != -1){
            this->next[prev] = this->next[current];
        }
        //free the memory
        this->elems[current].first = NULL_TCOMP;
        this->next[current] = -1;
        sortWithinHashValue(current);
        if (this->first_free > current)
            this->first_free = current;
        this->length--;
        this->no_elems--;
    }
    return true;
}
//BC: Theta(1), WC: Theta(length), Total: O(length)


bool SortedBag::search(TComp e) {
    int currentPosition = this->hash(e);
    if(this->elems[currentPosition].first != e && this->next[currentPosition] == -1)
        return false;
    while (this->next[currentPosition] != -1 && this->elems[currentPosition].first != e) {
        currentPosition = this->next[currentPosition];
    }
    if (currentPosition == -1)
        return false;
    if (this->elems[currentPosition].first == e) {
        return true;
    }
    return false;
}
//BC: Theta(1), WC: Theta(length), Total: O(length)


int SortedBag::nrOccurrences(TComp e) {
    int currentPosition = this->hash(e);
    TElem check;
    if(this->elems[currentPosition].first != e && this->next[currentPosition] == -1)
        return 0;
    while (this->next[currentPosition] != -1 && this->elems[currentPosition].first != e) {
        currentPosition = this->next[currentPosition];
    }
    if (currentPosition == -1)
        return 0;
    if (this->elems[currentPosition].first == e) {
        return this->elems[currentPosition].second;
    }
    return 0;
}
//BC: Theta(1), WC: Theta(length), Total: O(length)


int SortedBag::size() {
    return this->length;
}
//Theta(1)

bool SortedBag::isEmpty(){
    if (this->length == 0)
        return true;
    return false;
}
//Theta(1)

SortedBagIterator SortedBag::iterator() {
    return SortedBagIterator(*this);
}
//Theta(1)

int SortedBag::removeAllOccurrences(TComp e){
    int occurrences = nrOccurrences(e);
    if(!search(e))
        return 0;
    for(int i=0; i <= occurrences; i++)
        remove(e);
    return occurrences;
}
//Theta(occurrences)+theta(length)

SortedBag::~SortedBag() {
    delete[] this->elems;
    delete[] this->next;
}
//Theta(length)