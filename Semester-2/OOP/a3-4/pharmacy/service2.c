#include <stdlib.h>
#include "service2.h"

Service* createService(Repository * r)
{
    Service* s = (Service*)malloc(sizeof(Service));
    if (s == NULL)
        return NULL;
    s->repository = r;
    s->UndoStack = createDynamicArray(10, (DestroyElementFunctionType) &destroyRepo);
    s->RedoStack = createDynamicArray(10, (DestroyElementFunctionType) &destroyRepo);
    return s;
}

void destroyService(Service* s)
{
    // first destroy the repository inside
    destroyRepo(s->repository);
    destroy(s->RedoStack);
    destroy(s->UndoStack);

    // then free the memory
    free(s);
}

void populateRepo(Service* s)
{
    Medication *m1 = createMedication("paracetamol", 20, 1000, 5);
    addEntity(s->repository, m1);
    Medication *m2 = createMedication("algocalmin", 10, 800, 10);
    addEntity(s->repository, m2);
    Medication *m3 = createMedication("ibuprofen", 40, 5000, 9);
    addEntity(s->repository, m3);
    Medication* m4 = createMedication("aspenter", 15, 300, 40);
    addEntity(s->repository, m4);
    Medication* m5 = createMedication("strepsils", 8, 10000, 5);
    addEntity(s->repository, m5);
    Medication* m6 = createMedication("triferment", 20, 600, 10);
    addEntity(s->repository, m6);
    Medication* m7 = createMedication("antinevralgic", 10, 5000, 8);
    addEntity(s->repository, m7);
    Medication* m8 = createMedication("paduden", 60, 100, 18);
    addEntity(s->repository, m8);
    Medication* m9 = createMedication("paduden", 30, 100, 10);
    addEntity(s->repository, m9);
    Medication* m10 = createMedication("memoplus", 80, 20, 50);
    addEntity(s->repository, m10);
}

int isCharGreater(char* a, char* b)
{
    return strcmp(a, b)>0;
}

int isCharSmaller(char* a, char* b)
{
    return strcmp(a, b) < 0;
}

int isNumberGreater(int a, int b)
{
    return a > b;
}

int isNumberSmaller(int a, int b)
{
    return a < b;
}

void boblesortQuantity(Repository *repository, ComparisonIntFunction cmpInt)
{
    int sorted = 0;
    while(sorted == 0)
    {
        sorted = 1;
        for(int i=0; i<getLength(repository->data)-1; i++)
        {
            for(int j=i+1; j<getLength(repository->data); j++)
            {
                if(cmpInt(getQuantity(((Medication *)getEntityOnPos(repository, i))), getQuantity(((Medication *) getEntityOnPos(repository, j))))>0)
                {
                    Medication* aux_med = createCopyMedication((Medication *)(getEntityOnPos(repository, i)));
                    copyMedication(getEntityOnPos(repository, i), getEntityOnPos(repository, j));
                    copyMedication(getEntityOnPos(repository, j), aux_med);
                    sorted = 0;
                    destroyMedication(aux_med);
                }
            }
        }
    }
}

void boblesortName(Repository *repository, ComparisonCharFunction cmpChar)
{
    int sorted = 0;
    while(sorted == 0)
    {
        sorted = 1;
        for(int i=0; i<getLength(repository->data)-1; i++)
        {
            for(int j=i+1; j<getLength(repository->data); j++)
            {
                if(cmpChar(getName((Medication *)getEntityOnPos(repository, i)), getName((Medication *)getEntityOnPos(repository, j)))>0)
                {
                    Medication* aux_med = createCopyMedication((Medication *)getEntityOnPos(repository, i));
                    copyMedication((Medication *)getEntityOnPos(repository, i), (Medication *)getEntityOnPos(repository, j));
                    copyMedication((Medication *)getEntityOnPos(repository, j), aux_med);
                    sorted = 0;
                    destroyMedication(aux_med);
                }
            }
        }
    }
}

int addEntityServ(Service* s, char* name, int concentration, int quantity, int price)
{
    Medication * m = createMedication(name, concentration, quantity, price);
    Repository *repo = createCopyRepo(s->repository);
    int result = addEntity(s->repository, m);
    if (result == 0) {
        add(s->UndoStack, repo);
        if (s->RedoStack->length != 0)
            empty(s->RedoStack);
    }
    if (result == -1) {
        destroyRepo(repo);
        destroyMedication(m);
    }
    return result;
}

int deleteEntityServ(Service* s, char* name, int c)
{
    Repository *repo = createCopyRepo(s->repository);
    int result = deleteEntity(s->repository, findByNameConcentration(s->repository, name, c));
    if (result == 0) {
        add(s->UndoStack, repo);
        if (s->RedoStack->length != 0)
            empty(s->RedoStack);
    }
    if (result == -1) {
        destroyRepo(repo);
    }
    return result;
}


int updateEntityServ(Service* s, char* name, int concentration, int quantity, int price)
{
    Medication *new_m = createMedication(name, concentration, quantity, price);
    Repository *repo = createCopyRepo(s->repository);
    int result = updateEntity(s->repository, new_m);
    if (result == 0) {
        add(s->UndoStack, repo);
        if (s->RedoStack->length != 0)
            empty(s->RedoStack);
    }
    if (result == -1) {
        destroyRepo(repo);
        destroyMedication(new_m);
    }
    return result;
}

// this function filters the data in repo and keeps only the products which contain the given "string" in the name
void chooseMedicineGivenString(Service *service, Repository *secondary_repository, char string[50])
{
    empty(secondary_repository->data);
    for(int i=0; i<getLength(service->repository->data); i++)
    {
        if(strstr(getName((Medication *)getEntityOnPos(service->repository, i)), string) || strcmp(string, "-")==0 )
        {
            Medication *medicine = createMedication("", 0, 0, 0);
            copyMedication(medicine, ((Medication *)getEntityOnPos(service->repository, i)));
            addEntity(secondary_repository, medicine);
        }
    }
}

void chooseMedicineOddPrice(Service* service, Repository* secondary_repository)
{
    empty(secondary_repository->data);
    for (int i = 0; i < getLength(service->repository->data); i++)
    {
        if (getPrice((Medication*)getEntityOnPos(service->repository, i))%2==1)
        {
            Medication* medicine = createMedication("", 0, 0, 0);
            copyMedication(medicine, ((Medication*)getEntityOnPos(service->repository, i)));
            addEntity(secondary_repository, medicine);
        }
    }
}

void chooseMedicineLessThanXItems(Service* service, Repository* secondary_repository, int X) {
    empty(secondary_repository->data);
    for (int i = 0; i < getLength(service->repository->data); i++) {
        if (((Medication*)getEntityOnPos(service->repository, i))->quantity < X)
        {
            Medication* medicine = createMedication("", 0, 0, 0);
            copyMedication(medicine, ((Medication*)getEntityOnPos(service->repository, i)));
            addEntity(secondary_repository, medicine);
        }
    }
}


void chooseMedicineGivenStringSorted(Service *service, Repository *secondary_repository, char string[50], ComparisonCharFunction cmpChar)
{
    chooseMedicineGivenString(service, secondary_repository, string);
    boblesortName(secondary_repository, cmpChar);
}

void chooseMedicineOddPriceSorted(Service* service, Repository* secondary_repository, ComparisonCharFunction cmpChar)
{
    chooseMedicineOddPrice(service, secondary_repository);
    boblesortName(secondary_repository, cmpChar);
}

void chooseMedicineLessThanXItemsSorted(Service* service, Repository* secondary_repository, int X, ComparisonIntFunction cmpInt)
{
    chooseMedicineLessThanXItems(service, secondary_repository, X);
    boblesortQuantity(secondary_repository, cmpInt);
}

// UndoStack: init, change1, change2, change3, change4
// RedoStack: (empty)
//UNDO
// UndoStack: init, change1, change2, change3
// RedoStack: change4
//CHANGE
// UndoStack: init, change1, change2, change3, CHANGE
// RedoStack: (empty)

int undo(Service* s)
{
    if (s == NULL)
        return -1; // error

    int undoStackSize = getLength(s->UndoStack);
    if (undoStackSize == 0)
        return 1; // no more undos
    add(s->RedoStack, s->repository);
    Repository * repo = (Repository*)get(s->UndoStack, undoStackSize-1);
    if (repo == NULL)
        return -1;
    s->repository = repo;
    pop(s->UndoStack);
    return 0;
}

int redo(Service* s)
{
    if (s == NULL)
        return -1; // error

    int redoStackSize = getLength(s->RedoStack);
    if (redoStackSize == 0)
        return 1; // no more undos
    add(s->UndoStack, s->repository);
    Repository * repo = (Repository*)get(s->RedoStack, redoStackSize-1);
    if (repo == NULL)
        return -1;
    s->repository = repo;
    pop(s->RedoStack);
    return 0;
}

Repository * getRepo(Service* s)
{
    return s->repository;
}