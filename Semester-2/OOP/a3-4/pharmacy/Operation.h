#pragma once
#include "Medication.h"
#include <stdlib.h>

typedef enum {
	ADD, 
	DELETE,
	UPDATE,
//	NOTHING=NULL
} opType;

typedef struct {
	opType type;
	Medication * m;
} Operation;

/// <summary>
/// Creates an operation.
/// </summary>
/// <param name="type">opType, the type of the operation.</param>
/// <param name="m">pointer to the medication operated on.</param>
/// <returns>A pointer to the created operation.</returns>
Operation* createOperation(opType type, Medication * m);

/// <summary>
/// Destroys the operation.
/// </summary>
/// <param name="o">The operation to be destroyed.</param>
void destroyOperation(Operation* o);

/// <summary>
/// Returns the type of the operation.
/// </summary>
/// <param name="o">The operation.</param>
/// <returns>opType, the type of the operation.</returns>
opType getOpType(Operation* o);

/// <summary>
/// Returns the medication of the operation.
/// </summary>
/// <param name="o">The operation.</param>
/// <returns>pointer to Medication, the medication operated on.</returns>
Medication * getOpObject(Operation* o);
