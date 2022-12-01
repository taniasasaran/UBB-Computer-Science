#pragma once

#include "List.h"

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    List data;
    int nrCols, nrRows;
public:
	//constructor
	Matrix(int nrLines, int nrColumns);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

    // this function returns an iterator which points to the position of the element (i, j, value) in the linked list
    ListIteratorFW getPositionElement(int i, int j) const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

    void setElemsOnLine(int line, TElem elem);

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
