#include "Operation.h"


Operation* createOperation(opType type, Product * p) {
	Operation* op = malloc(sizeof(Operation));
	op->type = type;

	Product * copyOfP = createCopyProduct(p);
	op->p = copyOfP;

	return op;
}

void destroyOperation(Operation* o) {
	if (o == NULL)
		return;

	destroyProduct(o->p);
	free(o);
}

opType getOpType(Operation* o) {
	if (o == NULL)
		return -1;
	return o->type;
}

Product * getOpObject(Operation* o) {
	if (o == NULL)
		return NULL;
	return o->p; 
}
