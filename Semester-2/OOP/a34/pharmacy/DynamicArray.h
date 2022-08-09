#pragma once

#include <stdlib.h>
#include <assert.h>
#include "Medication.h"

#define CAPACITY 10

typedef void* TElement;
typedef void (*DestroyElementFunctionType)(TElement);

typedef struct
{
    TElement * elems;
	int length;			// actual length of the array
	int capacity;		// maximum capacity of the array
	DestroyElementFunctionType destroyElemFct; // function pointer to the function responsible with deallocating the elements stored in the array
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <param name="destroyElemFct">Function pointer, of type DestroyElementFunctionType. The function that deals with deallocating the elements of the array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFct);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destroyed.</param>
void destroy(DynamicArray*);

/// <summary>
/// Adds a generic to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void add(DynamicArray*, TElement);

/// <summary>
/// Deletes an element from a given position in the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position from which the element must be deleted. The position must be valid.</param>
void delete(DynamicArray* arr, int pos);

/// <summary>
/// Deletes all elements from a dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
void empty(DynamicArray* arr);

/// <summary>
/// Erases the last element from the dynamic array, without destroying it.
/// </summary>
/// <param name="arr">The dynamic array.</param>
void pop(DynamicArray* arr);

/// <summary>
/// Returns the length of the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
int getLength(DynamicArray*);

/// <summary>
/// Returns the element on a given position.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="pos">The position - must be a valid position.</param>
/// <returns>The element on the given position.</returns>
void* get(DynamicArray*, int pos);