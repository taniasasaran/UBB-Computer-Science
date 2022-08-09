#include <stdlib.h>
#include "Operation.h"
#include "service.h"

Service* createService(Repository * r)
{
    Service* s = (Service*)malloc(sizeof(Service));
    if (s == NULL)
        return NULL;
    s->repository = r;
    s->undoStack = createDynamicArray(10, (DestroyElementFunctionType) &destroyOperation);
    s->redoStack = createDynamicArray(10, (DestroyElementFunctionType) &destroyOperation);
    return s;
}

void destroyService(Service* s)
{
    // first destroy the repository inside
    destroyRepo(s->repository);

    destroy(s->undoStack);
    destroy(s->redoStack);
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
    int res = addEntity(s->repository, m);
    if (res == 0) // the planet was added
    {
        Operation* op = createOperation(ADD, m);
        if (op == NULL)
            return -1;
        add(s->undoStack, op);
    }
    return res;
}

int deleteMedicineServ(Service* s, char* name, int c)
{
    Medication * m = createMedication(" ", 0, 0, 0);
    copy_medication(m, findByNameConcentration(s->repository, name, c));
    Operation* op = createOperation(DELETE, m);
    if (op == NULL)
        return -1;
    add(s->undoStack, op);
    return deleteEntity(s->repository, findByNameConcentration(s->repository, name, c));
}

int updateMedicineServ(Service* s, char* name, int concentration, int quantity, int price)
{

    Medication * m = createMedication(" ", 0, 0, 0);
    copy_medication(m, findByNameConcentration(s->repository, name, concentration));
    Medication * new_m = createMedication(name, concentration, quantity, price);
    Operation* op = createOperation(UPDATE, m);
    if (op == NULL)
        return -1;
    add(s->undoStack, op);
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

// this function filters the data in repo and keeps only the products which are of "string" category
//void choose_products_given_food(Service *service, Repository *secondary_repository, char string[50])
//{
//
//    Product* product;
//    secondary_repository->data->length = 0;
//    secondary_repository->length = 0;
//    for(int i=0; i<getLength(service->repository->data); i++) {
//        if (strcmp(getProductOnPos(service->repository, i)->category, string) == 0 || strcmp(string, "0")==0) {
//            product = createCopyProduct(get(service->repository->data, i));
//            addProduct(secondary_repository, product);
//            secondary_repository->length += 1;
//        }
//    }
//}
//
//void choose_products_given_food_sorted(Service *service, Repository *secondary_repository, char string[50])
//{
//    choose_products_given_food(service, secondary_repository, string);
//    boblesort_month(secondary_repository);
//}
//

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

int undo(Service* s)
{
    if (s == NULL)
        return -1; // error

    int undoStackSize = getLength(s->undoStack);
    if (undoStackSize == 0)
        return 1; // no more undos
    Operation* op = get(s->undoStack, undoStackSize - 1);

    if (op == NULL)
        return -1;
    Medication * m = getOpObject(op);
    if (m == NULL)
        return -1;
    Medication * m_after_copy = createMedication(getName(m), getConcentration(m), getQuantity(m), getPrice(m));
    Operation* op_after_copy = createOperation(getOpType(op), m_after_copy);
    if (getOpType(op) == ADD)
        deleteEntity(s->repository, m_after_copy);
    else if (getOpType(op) == DELETE)
        addEntity(s->repository, m_after_copy);
    else if (getOpType(op) == UPDATE)
    {
        Medication * p_2 = createCopyMedication(findByNameConcentration(s->repository, m->name, m->concentration));
        op_after_copy = createOperation(getOpType(op), p_2);
        updateEntity(s->repository, m_after_copy);
    }
    add(s->redoStack, op_after_copy);
    delete(s->undoStack, undoStackSize - 1);
    return 0;
}

int redo(Service* s)
{
    if (s == NULL)
        return -1; // error

    int redoStackSize = getLength(s->redoStack);
    if (redoStackSize == 0)
        return 1;
    Operation* op = get(s->redoStack, redoStackSize - 1);
    if (op == NULL)
        return -1;
    Medication * m = getOpObject(op);
    Medication * m_after_copy = createMedication(getName(m), getConcentration(m), getQuantity(m), getPrice(m));
    if (m == NULL)
        return -1;
    Operation* op_after_copy = createOperation(getOpType(op), m_after_copy);
    if (getOpType(op) == ADD)
        addEntity(s->repository, m_after_copy);
    else if (getOpType(op) == DELETE)
        deleteEntity(s->repository, m_after_copy);
    else if (getOpType(op) == UPDATE)
    {
        Medication * p_2 = createCopyMedication(findByNameConcentration(s->repository, m->name, m->concentration));
        op_after_copy = createOperation(getOpType(op), p_2);
        updateEntity(s->repository, m_after_copy);
    }
    add(s->undoStack, op_after_copy);
    delete(s->redoStack, redoStackSize - 1);
    return 0;
}

Repository * getRepo(Service* s)
{
    return s->repository;
}