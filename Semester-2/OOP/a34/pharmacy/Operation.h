#pragma once
#include "Medication.h"

#include <stdlib.h>
// version 2 - operation contains functions (function pointers) for 
// the undo and redo functions, as well as the parameters for them
//typedef int (*undoPtrFct)(void*, void*);
//
//typedef struct
//{
//	void* obj;
//	undoPtrFct undoFct, redoFct;
//} Operation;


typedef enum {
	ADD, 
	DELETE,
	UPDATE
} opType;

typedef struct {
	opType type;
	Medication * m;
} Operation;

Operation* createOperation(opType type, Medication * m);
void destroyOperation(Operation* o);

opType getOpType(Operation* o);
Medication * getOpObject(Operation* o);
