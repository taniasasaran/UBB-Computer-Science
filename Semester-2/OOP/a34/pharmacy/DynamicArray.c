#include "DynamicArray.h"


DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFct)
{
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    // make sure that the space was allocated
    if (da == NULL)
        return NULL;

    da->capacity = capacity;
    da->length = 0;

    // allocate space for the elements
    da->elems = (TElement*)malloc(capacity * sizeof(TElement));
    if (da->elems == NULL)
        return NULL;

    // initialize the function pointer
    da->destroyElemFct = destroyElemFct;

    return da;
}

void destroy(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    // deallocate each of the elements - if we decide that the dynamic array is responsible with this
    for (int i = 0; i < arr->length; i++)
        arr->destroyElemFct(arr->elems[i]);
    // free the space allocated for the elements
    free(arr->elems);
    arr->elems = NULL;
    // free the space allocated for the dynamic array
    free(arr);
    arr = NULL;
}

// Resizes the array, allocating more space.
// If more space cannot be allocated, returns -1, else it returns 0.
int resize(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;

    arr->capacity *= 2;

    // allocate new memory, copy everything and deallocate the old memory
    TElement* aux = (TElement*)malloc(arr->capacity * sizeof(TElement));
    if (aux == NULL)
        return -1;
    for (int i = 0; i < arr->length; i++)
        aux[i] = arr->elems[i];
    free(arr->elems);
    arr->elems = aux;

    return 0;
}

void add(DynamicArray* arr, TElement t)
{
    if (arr == NULL)
        return;
    if (arr->elems == NULL)
        return;

    // resize the array, if necessary
    if (arr->length == arr->capacity)
        resize(arr);
    arr->elems[arr->length++] = t;
}

void delete(DynamicArray* arr, int pos)
{
    if (arr == NULL || pos < 0 || pos >= arr->length)
        return;

    arr->destroyElemFct(arr->elems[pos]);

    // !!! Do this only if we delete any element but the last
    if (pos != arr->length - 1)
        arr->elems[pos] = arr->elems[arr->length - 1];
    arr->length--;

}

void empty(DynamicArray* arr){
    if (arr == NULL)
        return;
    for(int i=0; i<arr->length; i++)
        arr->destroyElemFct(arr->elems[i]);
}

void pop(DynamicArray* arr)
{
    if(arr==NULL)
        return;
    arr->length--;
    arr->elems[arr->length] = NULL;

}

int getLength(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;

    return arr->length;
}

TElement get(DynamicArray* arr, int pos)
{
    if (arr == NULL || pos < 0)
        return NULL;
    return arr->elems[pos];
}
