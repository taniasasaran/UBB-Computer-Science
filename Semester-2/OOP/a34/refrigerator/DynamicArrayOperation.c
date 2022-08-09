#include "DynamicArrayOperation.h"


DynamicArrayOperation * createDynamicArrayOperation(int capacity, DestroyOperationFunctionType destroyOpFct)
{
    DynamicArrayOperation* da = (DynamicArrayOperation*)malloc(sizeof(DynamicArrayOperation));
    // make sure that the space was allocated
    if (da == NULL)
        return NULL;

    da->capacity = capacity;
    da->length = 0;

    // allocate space for the elements
    da->elems = (TElementO*)malloc(capacity * sizeof(TElementO));
    if (da->elems == NULL)
        return NULL;

    // initialize the function pointer
    da->destroyOpFct = destroyOpFct;

    return da;
}

void destroyDAO(DynamicArrayOperation* arr)
{
    if (arr == NULL)
        return;

    // deallocate each of the elements - if we decide that the dynamic array is responsible with this
    for (int i = 0; i < arr->length; i++)
        arr->destroyOpFct(arr->elems[i]);

    // free the space allocated for the elements
    free(arr->elems);
    arr->elems = NULL;

    // free the space allocated for the dynamic array
    free(arr);
    arr = NULL;
}

// Resizes the array, allocating more space.
// If more space cannot be allocated, returns -1, else it returns 0.
int resizeDAO(DynamicArrayOperation* arr)
{
    if (arr == NULL)
        return -1;

    arr->capacity *= 2;

    // allocate new memory, copy everything and deallocate the old memory
    TElementO* aux = (TElementO*)malloc(arr->capacity * sizeof(TElementO));
    if (aux == NULL)
        return -1;
    for (int i = 0; i < arr->length; i++)
        aux[i] = arr->elems[i];
    free(arr->elems);
    arr->elems = aux;

    return 0;
}

void addOp(DynamicArrayOperation* arr, TElementO t)
{
    if (arr == NULL)
        return;
    if (arr->elems == NULL)
        return;

    // resize the array, if necessary
    if (arr->length == arr->capacity)
        resizeDAO(arr);
    arr->elems[arr->length++] = t;
}

void deleteOp(DynamicArrayOperation* arr, int pos)
{
    if (arr == NULL || pos < 0 || pos >= arr->length)
        return;

    arr->destroyOpFct(arr->elems[pos]);

    // !!! Do this only if we delete any element but the last
    if (pos != arr->length - 1)
        arr->elems[pos] = arr->elems[arr->length - 1];
    arr->length--;

}

int getLengthDAO(DynamicArrayOperation* arr)
{
    if (arr == NULL)
        return -1;

    return arr->length;
}

TElementO getOp(DynamicArrayOperation* arr, int pos)
{
    if (arr == NULL || pos < 0)
        return NULL;
    return arr->elems[pos];
}
