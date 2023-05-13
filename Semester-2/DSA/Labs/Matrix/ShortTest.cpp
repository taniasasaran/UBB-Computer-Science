#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 8);
	assert(m.element(1, 1) == 8);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 8);

    m.setElemsOnLine(3, 5);
    assert(m.element(3, 0) == 5);
    assert(m.element(3, 1) == 5);
    assert(m.element(3, 2) == 5);
    assert(m.element(3, 3) == 5);
    assert(m.element(1, 3) != 5);
}