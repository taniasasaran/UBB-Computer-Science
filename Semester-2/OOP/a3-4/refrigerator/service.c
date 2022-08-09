
#include <stdlib.h>
#include "service.h"

Service* createService(Repository * r)
{
    Service* s = (Service*)malloc(sizeof(Service));
    if (s == NULL)
        return NULL;
    s->repository = r;
    s->undoStack = createDynamicArrayOperation(10, &destroyOperation);
    s->redoStack = createDynamicArrayOperation(10, &destroyOperation);
    return s;
}

void destroyService(Service* s)
{
    // first destroy the repository inside
    destroyRepo(s->repository);

    destroyDAO(s->undoStack);
    destroyDAO(s->redoStack);
    // then free the memory
    free(s);
}

void populateRepo(Service* s)
{
    Product *p1 = createProduct("eu", "sweets", 1, 30, 9, 2022);
    addProduct(s->repository, p1);
    Product *p2 = createProduct("lapte", "dairy", 3, 24, 5, 2022);
    addProduct(s->repository, p2);
    Product *p3 = createProduct("conserve", "meat", 10, 4, 9, 2023);
    addProduct(s->repository, p3);
    Product *p4 = createProduct("chocolate", "sweets", 4, 5, 9, 2023);
    addProduct(s->repository, p4);
    Product *p5 = createProduct("dulce", "sweets", 10, 24, 3, 2022);
    addProduct(s->repository, p5);
    Product *p6 = createProduct("cartofi", "fruit", 3, 30, 3, 2022);
    addProduct(s->repository, p6);
    Product *p7 = createProduct("banane", "fruit", 3, 30, 5, 2023);
    addProduct(s->repository, p7);
    Product *p8 = createProduct("iaurt", "dairy", 3, 24, 7, 2022);
    addProduct(s->repository, p8);
    Product *p9 = createProduct("inghetata", "dairy", 5, 20, 12, 2022);
    addProduct(s->repository, p9);
    Product *p10 = createProduct("pui", "meat", 1, 18, 4, 2022);
    addProduct(s->repository, p10);
}

void boblesort_quantity(Repository *repository)
{
    int sorted = 0;
    Product* aux_product;
    while(sorted == 0)
    {
        sorted = 1;
        for(int i=0; i<getLength(repository->data)-1; i++)
        {
            for(int j=i+1; j<getLength(repository->data); j++)
            {
                if(getProductOnPos(repository, i)->quantity > getProductOnPos(repository, j)->quantity)
                {
                    aux_product = createCopyProduct(getProductOnPos(repository, i));
                    copy_product(getProductOnPos(repository, i), getProductOnPos(repository, j));
                    copy_product(getProductOnPos(repository, j), aux_product);
                    sorted = 0;
                }
            }
        }
    }
}

void boblesort_month(Repository *repository)
{
    int sorted = 0;
    Product* aux_product;
    while(sorted == 0)
    {
        sorted = 1;
        for(int i=0; i<getLength(repository->data)-1; i++)
        {
            for(int j=i+1; j<getLength(repository->data); j++)
            {
                if(getProductOnPos(repository, i)->expiration_date_month > getProductOnPos(repository, j)->expiration_date_month)
                {
                    aux_product = createCopyProduct(getProductOnPos(repository, i));
                    copy_product(getProductOnPos(repository, i), getProductOnPos(repository, j));
                    copy_product(getProductOnPos(repository, j), aux_product);
                    sorted = 0;
                }
            }
        }
    }
}

int addProductServ(Service* s, char* name, char* category, int quantity, int expiration_date_day, int expiration_date_month, int expiration_date_year)
{
    Product * p = createProduct(name, category, quantity, expiration_date_day, expiration_date_month, expiration_date_year);

    int res = addProduct(s->repository, p);
    if (res == 0) // the planet was added
    {
        Operation* op = createOperation(ADD, p);
        if (op == NULL)
            return -1;
        addOp(s->undoStack, op);
    }
    return res;

}

int deleteProductServ(Service* s, char* name, char* category)
{
    Product * p = findByNameCategory(s->repository, name, category);
    Operation* op = createOperation(DELETE, p);
    if (op == NULL)
        return -1;
    addOp(s->undoStack, op);

    return deleteProduct(s->repository, *p);
}

int updateProductServ(Service* s, char* name, char* category, int quantity, int expiration_date_day, int expiration_date_month, int expiration_date_year)
{
    Product * p = findByNameCategory(s->repository, name, category);
    Product* new_p = createProduct(name, category, quantity, expiration_date_day, expiration_date_month, expiration_date_year);
    Operation* op = createOperation(UPDATE, p);
    if (op == NULL)
        return -1;
    addOp(s->undoStack, op);
    return updateProduct(s->repository, *new_p);
}

// this function filters the data in repo and keeps only the products which contain the given "string" in the name
void choose_products_given_string(Service *service, Repository *secondary_repository, char string[50])
{
    Product* product;
    secondary_repository->data->length = 0;
    secondary_repository->length = 0;
    for(int i=0; i<getLength(service->repository->data); i++)
    {
        if(strstr(getProductOnPos(service->repository, i)->name, string) || strcmp(string, "0")==0 )
        {
            product = createCopyProduct(get(service->repository->data, i));
            addProduct(secondary_repository, product);
            secondary_repository->length += 1;
        }
    }
}

// this function filters the data in repo and keeps only the products which are of "string" category
void choose_products_given_food(Service *service, Repository *secondary_repository, char string[50])
{

    Product* product;
    secondary_repository->data->length = 0;
    secondary_repository->length = 0;
    for(int i=0; i<getLength(service->repository->data); i++) {
        if (strcmp(getProductOnPos(service->repository, i)->category, string) == 0 || strcmp(string, "0")==0) {
            product = createCopyProduct(get(service->repository->data, i));
            addProduct(secondary_repository, product);
            secondary_repository->length += 1;
        }
    }
}

void choose_products_given_string_sorted(Service *service, Repository *secondary_repository, char string[50])
{
    choose_products_given_string(service, secondary_repository, string);
    boblesort_quantity(secondary_repository);
}

void choose_products_given_food_sorted(Service *service, Repository *secondary_repository, char string[50])
{
    choose_products_given_food(service, secondary_repository, string);
    boblesort_month(secondary_repository);
}

void choose_products_given_food_exp_x_days(Service *service, Repository *secondary_repository, char string[50], int X)
{
    choose_products_given_food(service, secondary_repository, string);
    choose_products_exp_X_days(secondary_repository, X);
}

int undo(Service* s)
{
    if (s == NULL)
        return -1; // error

    int undoStackSize = getLengthDAO(s->undoStack);
    if (undoStackSize == 0)
        return 1; // no more undos
    Operation* op = getOp(s->undoStack, undoStackSize - 1);

    if (op == NULL)
        return -1;
    Product * p = getOpObject(op);
    if (p == NULL)
        return -1;
    Operation* op_after_copy = createOperation(getOpType(op), getOpObject(op));
    if (getOpType(op) == ADD)
        deleteProduct(s->repository, *p);
    else if (getOpType(op) == DELETE)
        addProduct(s->repository, createCopyProduct(p));
    else if (getOpType(op) == UPDATE)
    {
        Product* p_2 = findByNameCategory(s->repository, p->name, p->category);
        op_after_copy = createOperation(getOpType(op), p_2);
        updateProduct(s->repository, *p);
    }
    addOp(s->redoStack, op_after_copy);
    deleteOp(s->undoStack, undoStackSize - 1);
    return 0;
}

int redo(Service* s)
{
    if (s == NULL)
        return -1; // error

    int redoStackSize = getLengthDAO(s->redoStack);
    if (redoStackSize == 0)
        return 1;
    Operation* op = getOp(s->redoStack, redoStackSize - 1);
    if (op == NULL)
        return -1;
    Product * p = getOpObject(op);
    if (p == NULL)
        return -1;
    Operation* op_after_copy = createOperation(getOpType(op), getOpObject(op));
    if (getOpType(op) == ADD)
        addProduct(s->repository, createCopyProduct(p));
    else if (getOpType(op) == DELETE)
        deleteProduct(s->repository, *p);
    else if (getOpType(op) == UPDATE)
    {
        Product* p_2 = findByNameCategory(s->repository, p->name, p->category);
        op_after_copy = createOperation(getOpType(op), p_2);
        updateProduct(s->repository, *p);
    }
    addOp(s->undoStack, op_after_copy);
    deleteOp(s->redoStack, redoStackSize - 1);
    return 0;
}

Repository * getRepo(Service* s)
{
    return s->repository;
}