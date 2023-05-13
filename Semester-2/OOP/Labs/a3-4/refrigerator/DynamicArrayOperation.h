#pragma once

#include "Operation.h"
#include <stdlib.h>
#include <assert.h>
#define CAPACITY 10

typedef Operation* TElementO;
typedef void (*DestroyOperationFunctionType)(Operation *);

typedef struct
{
    TElementO* elems;
    int length;			// actual length of the array
    int capacity;		// maximum capacity of the array
    DestroyOperationFunctionType destroyOpFct; // function pointer to the function responsible with deallocating the elements stored in the array
} DynamicArrayOperation;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <param name="destroyElemFct">Function pointer, of type DestroyElementFunctionType. The function that deals with deallocating the elements of the array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArrayOperation* createDynamicArrayOperation(int capacity, DestroyOperationFunctionType);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroyDAO(DynamicArrayOperation*);

/// <summary>
/// Adds a generic to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void addOp(DynamicArrayOperation*, TElementO);

/// <summary>
/// Deletes an element from a given position in the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position from which the element must be deleted. The position must be valid.</param>
void deleteOp(DynamicArrayOperation*, int pos);

/// <summary>
/// Returns the length of the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
int getLengthDAO(DynamicArrayOperation*);

/// <summary>
/// Returns the element on a given position.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position - must be a valid position.</param>
/// <returns>The element on the given position.</returns>
TElementO getOp(DynamicArrayOperation*, int pos);