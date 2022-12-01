#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    this->R = r;
    this->max_capacity = CAPACITY;
    this->elems = new Node*[CAPACITY];
    this->data = new int[CAPACITY];
    this->sizeBST = 0;
}

void SortedIndexedList::resize(){
    max_capacity *= 2;
    Node** temp;
    temp = new Node*[max_capacity];
    for(int i=0; i<sizeBST; i++){
        temp[i] = elems[i];
    }
    delete[] this->elems;
    this->elems = temp;
}

int SortedIndexedList::size() const {
    return this->sizeBST;
}

bool SortedIndexedList::isEmpty() const {
    if (this->sizeBST ==0) return true;
    return false;
}

TComp SortedIndexedList::getElement(int i) const{
    if (i < 0 || i >= this->sizeBST)
    {
        throw exception();
    }
    Node* current=this->elems[0];
    int position=0;
    while (current != NULL)
    {
        if (i == position + current->nrLeft)
            return current->info;
        if (i < position + current->nrLeft)
        {
            position = position * 2 + 1;
            current = this->elems[position];
        }
        else
        {
            position = position * 2 + 2;
            current = this->elems[position];
        }
    }
    return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= this->sizeBST)
    {
        throw exception();
    }
    Node* prev = NULL;
    Node* current = this->elems[0];
    int position = 0;
    while (current)
    {
        if (i == position + current->nrLeft) break;
        if (i < position + current->nrLeft)
        {
            prev = current;
            current = current->left;
        }
        else
        {
            prev = current;
            position = position + current->nrLeft + 1;
            current = current->right;

        }
    }
    int deleted = current->info;
    if (current->left == NULL && current->right == NULL)
    {
        decrease(i);
        if (prev == NULL)
        {
            this->root = NULL;
        }
        else
        {
            if (this->R(current->info, prev->info)) prev->left = NULL;
            else prev->right = NULL;
            delete[] current;
        }
        this->sizeBST--;
    }
    else
    {
        if (current->left == NULL || current->right == NULL)
        {
            decrease(i);
            Node* descendant;
            if (current->left == NULL)
                descendant = current->right;
            else
                descendant = current->left;
            if (prev == NULL)
            {
                //root
                this->root = descendant;
            }
            else
            {
                //not root
                if (this->R(current->info, prev->info))
                {
                    //on left
                    prev->left = descendant;
                }
                else
                {
                    //on right
                    prev->right = descendant;
                }
                delete[] current;
            }
            this->sizeBST--;
        }
        else
        {
            TComp ssuccessor = this->successor(current->info);
            int index = this->search(ssuccessor);
            this->remove(index);
            current->info = ssuccessor;
        }
    }
    return deleted;
}

TComp SortedIndexedList::parent(TComp e)
{
    if (this->elems[0]->info == e)
        return -1;
    Node* current = this->elems[0];
    int position = 0;
    while (current && this->elems[position*2+1]->info != e && this->elems[position*2+2]->info != e)
    {
        if (!this->R(current->info, e))
            position = position*2 + 1;
        else
            position = position*2 + 2;
    }
    return current->info;
}

void SortedIndexedList::decrease(int i) const
{
    if (i >= this->sizeBST || i < 0)
        throw(exception());

    Node* current = this->elems[0];
    int position = 0;
    while (current)
    {
        if (i == position + current->nrLeft)
            return;
        if (i < position + current->nrLeft)
        {
            //left
            current->nrLeft--;
            position = position*2 + 1;
            current = this->elems[position];
        }
        else
        {
            //right
            position = position*2 + 2;
            current = this->elems[position];
        }
    }
}

int SortedIndexedList::getRange() const
{
    if (this->sizeBST == 0) return -1;
    TComp min, max;
    Node* current = this->elems[0];
    int pos = 0;
    while (this->elems[pos*2+1]) {
        pos = pos*2 + 1;
        current = this->elems[pos];
    }
    min = current->info;
    current = this->elems[0];
    while (this->elems[pos*2+2]) {
        pos = pos*2 + 2;
        current = this->elems[pos];
    }
    max = current->info;
    return max - min;
}

TComp SortedIndexedList::successor(TComp e)
{
    Node* current = this->elems[0];
    int pos=0;
    while (current->info!=e)
    {

        if (this->R(e, current->info)){
            pos = pos*2 + 1;
            current = this->elems[pos];
        }
        else
        {
            pos = pos*2 + 2;
            current = this->elems[pos];
        }
    }
    if (this->elems[pos*2+2])
    {
        pos = pos*2 + 2;
        current = this->elems[pos];
        while (this->elems[pos*2+1]){
            pos = pos*2 + 1;
            current = this->elems[pos];
        }
        return current->info;
    }
    else
    {
        int p = this->parent(current->info);
        Node* parent = this->elems[0];

        while (parent->info != p)
        {
            if (this->R(p, current->info)){
                pos = pos*2 + 1;
                current = this->elems[pos];
            }
            else {
                pos = pos*2 + 2;
                current = this->elems[pos];
            }
        }

        while (parent && parent->left != current)
        {
            current = parent;
            int p = this->parent(current->info);
            Node* parent = this->root;

            while (parent->info != p)
            {

                if (this->R(p, current->info)) current = current->left;
                else current = current->right;

            }
        }
        return p;
    }
}


int SortedIndexedList::search(TComp e) const {
    Node* current = this->root;
    int position = 0;
    while (current != NULL)
    {
        //return position
        if (current->info == e)return position+current->nrLeft;
        if (this->R(e,current->info)) current = current->left;
        else
        {
            position = position+current->nrLeft+1;
            current = current->right;
        }
    }
    return -1;
}

void SortedIndexedList::add(TComp e) {
    Node* newNode = new Node;
    newNode->info = e;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->nrLeft = 0;
    if (root == NULL)
        root = newNode;
    else
    {
        Node* current = this->root;
        while (current)
        {
            if (this->R(e,current->info))
            {
                current->nrLeft++;
                if (current->left == NULL)
                {

                    current->left = newNode;
                    current = NULL;
                }
                else current = current->left;
            }
            else
            {
                //current->nrRight++;
                if (current->right == NULL)
                {
                    current->right = newNode;
                    current = NULL;
                }
                else current = current->right;
            }
        }
    }
    this->sizeBST++;
}

ListIterator SortedIndexedList::iterator(){
    return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    while (!this->isEmpty())this->remove(0);
}

int SortedIndexedList::removeFromKtoK(int k) {
    if(k<=0)
        throw exception();
//    for(int i=0; i<)
//        return 0;
}
