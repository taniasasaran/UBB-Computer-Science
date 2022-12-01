#pragma once

//DO NOT CHANGE THIS PART
#include "tuple"
typedef int TElem;
typedef std::tuple<int, int, int> TELEM;
#define NULL_TELEM 0
#define CAPACITY 10


class Matrix {

private:
    TELEM* data;
    int nrCols, nrRows, max_capacity, size;
public:
	//constructor
	Matrix(int nrLines, int nrColumns);
    ~Matrix() {  delete[] data;}   // theta(1)

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

    void resize(int newCapacity);

    void remove(int i, int j);

    void append(TELEM e);

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
