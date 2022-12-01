#include "Matrix.h"
#include <exception>

using namespace std;


Matrix::Matrix(int nrLines, int nrColumns) {
    // this function is the constructor of the matrix  O(1)
    nrCols = nrColumns;
    nrRows = nrLines;
}


int Matrix::nrLines() const {
// this function returns the number of rows  O(1)
	return nrRows;
}


int Matrix::nrColumns() const {
// this function returns the number of columns  O(1)
	return nrCols;
}

ListIteratorFW Matrix::getPositionElement(int i, int j) const{
    // this function returns an iterator which points to the position of the element (i, j, value) in the linked list
    // O(n)
    ListIteratorFW itf = data.iterator_fw();
    while (itf.valid()) {
        if(get<0>(itf.getCurrent())==i && get<1>(itf.getCurrent())==j)
            return itf;
        itf.next();
    }
}

TElem Matrix::element(int i, int j) const {
	//this function returns the value associated to a given column and row of the matrix
    // O(n)
    if(!(0<=i && i<nrRows && 0<=j && j<nrCols))
        throw exception();
    ListIteratorFW itf = data.iterator_fw();
    while (itf.valid()) {
        if(get<0>(itf.getCurrent())==i && get<1>(itf.getCurrent())==j)
            return get<2>(itf.getCurrent());
        itf.next();
    }
    return NULL_TELEM;
}

void Matrix::setElemsOnLine(int line, TElem elem){
    // this function gives a certain int value to all elements situated on a line;
    // throws exception if line is not part of the matrix
    // O(nrCols)
    if(!(0<=line && line<nrRows))
        throw exception();
    TELEM x;
    for(int j=0; j<nrCols; j++){
        modify(line, j, elem);
    }
}

TElem Matrix::modify(int i, int j, TElem e) {
    // this function tries to modify an entry to a specified value
    // it throws an exception if the row and column are not part of the matrix
    // O(1)
    if(!(0<=i && i<nrRows && 0<=j && j<nrCols))
        throw exception();
    TELEM x;
    x = make_tuple(i, j, e);
    try {
        int old = element(i, j);
        data.setElementFW(this->getPositionElement(i, j), x);
        return old;
    }
    catch (exception &e) {
        data.addToBeginning(x);
        return NULL_TELEM;
    }
}



