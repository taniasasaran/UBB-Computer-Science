#include "Operation.h"


Operation* createOperation(opType type, Medication * m) {
	Operation* op = malloc(sizeof(Operation));
	op->type = type;

	Medication * copyOfM = createCopyMedication(m);
	op->m = copyOfM;

	return op;
}

void destroyOperation(Operation* o) {
	if (o == NULL)
		return;

	destroyMedication(o->m);
	free(o);
}

opType getOpType(Operation* o) {
	if (o == NULL)
		return -1;
	return o->type;
}

Medication * getOpObject(Operation* o) {
	if (o == NULL)
		return NULL;
	return o->m;
}
