#include "Matrix.h"
#include <exception>

using namespace std;


Matrix::Matrix(int nrLines, int nrColumns) {
    // this function is the constructor of the matrix  theta(1)
    nrCols = nrColumns;
    nrRows = nrLines;
    max_capacity = CAPACITY;
    size = 0;
    data = new TELEM[CAPACITY];
}


int Matrix::nrLines() const {
// this function returns the number of rows  theta(1)
	return nrRows;
}


int Matrix::nrColumns() const {
// this function returns the number of columns  theta(1)
	return nrCols;
}

TElem Matrix::element(int i, int j) const {
	//this function returns the value associated to a given column and row of the matrix
    // theta(n)
    if(!(0<=i && i<nrRows && 0<=j && j<nrCols))
        throw exception();
    for(int k=0; k<size; k++)
        if(std::get<0>(data[k])==i && std::get<1>(data[k])==j)
            return std::get<2>(data[k]);
    return NULL_TELEM;
}

void Matrix::resize(int newCapacity){
    // theta(n)
    max_capacity = newCapacity;
    auto newData = new TELEM[newCapacity]();
    for(int i=0; i<size;i++)
        newData[i] = data[i];
    delete[] data;
    data = newData;
}

void Matrix::append(TELEM e){
    // BC omega(1), WC O(n)
    if(size == max_capacity)
        resize(max_capacity*2);
    data[size] = e;
    size++;
}

void Matrix::remove(int i, int j){
    // theta(n)
    TELEM* newData = new TELEM[max_capacity]();
    int newSize = 0;
    for(int k=0; k<size; k++)
        if(!(std::get<0>(data[k])==i && std::get<1>(data[k])==j)){
            newData[newSize] = data[k];
            newSize++;
        }
    delete[] data;
    data = newData;
}


TElem Matrix::modify(int i, int j, TElem e) {
    // this function tries to modify an entry to a specified value
    // it throws an exception if the row and column are not part of the matrix
    // BC omega(1), WC O(n)
    if(!(0<=i && i<nrRows && 0<=j && j<nrCols))
        throw exception();
    TELEM x;
    x = make_tuple(i, j, e);
    int old = element(i, j);
    if(old == NULL_TELEM) {
        append(x);
        return old;
    }
    for(int k=0; k<size; k++)
        if(std::get<0>(data[k])==i && std::get<1>(data[k])==j){
            if(e==NULL_TELEM)
                remove(i, j);
            else
                std::get<2>(data[k]) = e;
        }
    return old;
}



