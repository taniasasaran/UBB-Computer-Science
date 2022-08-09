#pragma once
#include "domain.h"
#include "exception.h"

#include <stdlib.h>

typedef enum {
	ADD, 
	DELETE,
	UPDATE
} opType;

typedef struct {
	opType type;
	Movie m;
} Operation;

Operation* createOperation(opType type, Movie m);
void destroyOperation(Operation* o);

opType getOpType(Operation* o);
Movie getOpObject(Operation* o);
