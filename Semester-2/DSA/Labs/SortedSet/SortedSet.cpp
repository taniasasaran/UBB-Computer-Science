#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    this->size_of_Values = 0;
    this->max_capacity=CAPACITY;
    this->relation = r;
    this->Values = new TComp[CAPACITY];
}

// O(n) , n=size_of_values
bool SortedSet::resize()
{
    if (this->Values == nullptr)
        return -1;
    this->max_capacity *= 2;

    // allocate new memory, copy everything and deallocate the old memory
    auto * aux = (TComp *)malloc(this->max_capacity * sizeof(TComp));
    if (aux == nullptr)
        return false;
    for (int i = 0; i < this->size_of_Values; i++)
        aux[i] = this->Values[i];
    free(this->Values);
    this->Values = aux;

    return true;
}

// O(n^2) - bubble-sort
void SortedSet::sort(){
    int i, j, min_idx;
    TComp aux;

    for (i = 0; i < this->size_of_Values-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < this->size_of_Values; j++)
            if (this->relation(this->Values[j], this->Values[min_idx]))
                min_idx = j;

        // Swap the found minimum element with the first element
        aux = this->Values[min_idx];
        this->Values[min_idx] = this->Values[i];
        this->Values[i] = aux;
    }
}

// O(n)
int SortedSet::searchElem(TComp elem){
    for(int i=0; i<this->size_of_Values; i++)
        if(this->Values[i] == elem)
            return i;
    return -1;
}

// O(n^2) - cause its doing bubble-sort after inserting each elem on the last position
bool SortedSet::add(TComp elem) {
    if (this->Values == nullptr)
        return false;
    for(int i=0;i<this->size_of_Values; i++)
    {
        if(this->Values[i] == elem) {
            return false;
        }
    }
    if(this->size_of_Values == this->max_capacity)
    {
        this->resize();
    }
    //this->size_of_Values++;
    //int position = searchElem(elem);
    //for(int j=position; j<this->size_of_Values; j++)
    //    this->Values[j+1] = this->Values[j];
    //this->Values[position] = elem;
    //return true;
    this->Values[this->size_of_Values++] = elem;
    this->sort();
    return true;
}

// O(n^2) - cause its doing bubble-sort after moving the "deleted" elem on the last position and decreasing size_of_values
bool SortedSet::remove(TComp elem) {
    int i;
    for(i=0; i<=this->size_of_Values; i++)
        if(this->Values[i] == elem)
            break;
    if(i < this->size_of_Values)
    {
        this->Values[i]=this->Values[this->size_of_Values-1];
        this->size_of_Values--;
        this->sort();
        return true;
    }
    return false;
}

// O(n)
bool SortedSet::search(TComp elem) const {
    for(int i=0; i<=this->size_of_Values; i++)
        if(this->Values[i] == elem)
            return true;
    return false;
}

// O(1)
void SortedSet::empty(){
    delete this->Values;
    this->size_of_Values = 0;
    this->max_capacity=CAPACITY;
    this->Values = new TComp[CAPACITY];
}

// O(1)
int SortedSet::size() const {
    return this->size_of_Values;
}

// O(1)
bool SortedSet::isEmpty() const {
    return this->size_of_Values == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

SortedSet::~SortedSet() {
    delete this->Values;
}


