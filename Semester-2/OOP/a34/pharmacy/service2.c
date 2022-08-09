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
    Medication *m3 = createMedication("ibup", 400, 5000, 9);
    addEntity(s->repository, m3);
}

void boblesort_quantity(Repository *repository)
{
    int sorted = 0;
    Medication * aux_med;
    while(sorted == 0)
    {
        sorted = 1;
        for(int i=0; i<getLength(repository->data)-1; i++)
        {
            for(int j=i+1; j<getLength(repository->data); j++)
            {
                if(((Medication *)getEntityOnPos(repository, i))->quantity > ((Medication *) getEntityOnPos(repository, j))->quantity)
                {
                    aux_med = createCopyMedication((Medication *)(getEntityOnPos(repository, i)));
                    copy_medication(getEntityOnPos(repository, i), getEntityOnPos(repository, j));
                    copy_medication(getEntityOnPos(repository, j), aux_med);
                    sorted = 0;
                }
            }
        }
    }
}

void boblesort_name(Repository *repository)
{
    int sorted = 0;
    Medication * aux_med;
    while(sorted == 0)
    {
        sorted = 1;
        for(int i=0; i<getLength(repository->data)-1; i++)
        {
            for(int j=i+1; j<getLength(repository->data); j++)
            {
                if(strcmp(((Medication *)getEntityOnPos(repository, i))->name, ((Medication *)getEntityOnPos(repository, j))->name) >0)
                {
                    aux_med = createCopyMedication((Medication *)getEntityOnPos(repository, i));
                    copy_medication((Medication *)getEntityOnPos(repository, i), (Medication *)getEntityOnPos(repository, j));
                    copy_medication((Medication *)getEntityOnPos(repository, j), aux_med);
                    sorted = 0;
                }
            }
        }
    }
}

int addMedicineServ(Service* s, char* name, int concentration, int quantity, int price)
{
    Medication * m = createMedication(name, concentration, quantity, price);
    Repository *repo = createCopyRepo(s->repository);
    add(s->UndoStack, repo);
    empty(s->RedoStack);
    return addEntity(s->repository, m);
}

int deleteMedicineServ(Service* s, char* name, int c)
{
    Repository *repo = createCopyRepo(s->repository);
    add(s->UndoStack, repo);
    empty(s->RedoStack);
    return deleteEntity(s->repository, findByNameConcentration(s->repository, name, c));
}


int updateMedicineServ(Service* s, char* name, int concentration, int quantity, int price)
{
    Medication * new_m = createMedication(name, concentration, quantity, price);
    Repository *repo = createCopyRepo(s->repository);
    add(s->UndoStack, repo);
    empty(s->RedoStack);
    return updateEntity(s->repository, new_m);
}

// this function filters the data in repo and keeps only the products which contain the given "string" in the name
void choose_medicine_given_string(Service *service, Repository *secondary_repository, char string[50])
{
    secondary_repository->data->length = 0;
    secondary_repository->length = 0;
    for(int i=0; i<getLength(service->repository->data); i++)
    {
        if(strstr(((Medication *)getEntityOnPos(service->repository, i))->name, string) || strcmp(string, "0")==0 )
        {
            Medication *medicine = createMedication("", 0, 0, 0);
            copy_medication(medicine, ((Medication *)getEntityOnPos(service->repository, i)));
            addEntity(secondary_repository, medicine);
        }
    }
}

void choose_medicine_given_string_sorted(Service *service, Repository *secondary_repository, char string[50])
{
    choose_medicine_given_string(service, secondary_repository, string);
    boblesort_name(secondary_repository);
}

void choose_medicine_less_than_X_items(Service *service, Repository *secondary_repository, int X)
{
    secondary_repository->data->length = 0;
    secondary_repository->length = 0;
    for(int i=0; i<getLength(service->repository->data); i++) {
        if(((Medication *)getEntityOnPos(service->repository, i))->quantity < X )
        {
            Medication *medicine = createMedication("", 0, 0, 0);
            copy_medication(medicine, ((Medication *)getEntityOnPos(service->repository, i)));
            addEntity(secondary_repository, medicine);
        }
    }
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
//    add(s->RedoStack, repo);
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
//    add(s->UndoStack, repo);
    pop(s->RedoStack);
    return 0;
}


Repository * getRepo(Service* s)
{
    return s->repository;
}