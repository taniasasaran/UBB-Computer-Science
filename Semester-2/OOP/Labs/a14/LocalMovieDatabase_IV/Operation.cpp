//
// Created by TANIA on 5/27/2022.
//

#include "Operation.h"



Operation* createOperation(opType type, Movie m) {
    Operation* op = new Operation();
    op->type = type;

    op->m = m;

    return op;
}

void destroyOperation(Operation* o) {
    if (o == NULL)
        return;

    free(o);
}

opType getOpType(Operation* o) {
    if (o == NULL)
        throw Exception("woah sth happened");
    return o->type;
}

Movie getOpObject(Operation* o) {
    if (o == NULL)
        throw Exception("woah sth happened");
    return o->m;
}
