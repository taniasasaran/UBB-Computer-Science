#include "repository.h"

Repository* createRepo()
{
    Repository * repository = (Repository *)malloc(sizeof(Repository));
    if (repository == NULL)
        return NULL;
    repository->data = createDynamicArray(CAPACITY, &destroyProduct);
    return repository;
}

void destroyRepo(Repository * repository)
{
    if (repository == NULL)
        return;

    // then destroy the dynamic array
    destroy(repository->data);
    free(repository);
}

int updateProduct(Repository *repository, Product product)
{
    int found = 0;
    for(int i=0; i<getLength(repository->data); i++)
    {
        if (strcmp(get(repository->data, i)->name, product.name) == 0 &&
            strcmp(get(repository->data, i)->category, product.category) == 0)
        {
            found = 1;
            get(repository->data, i)->quantity = product.quantity;
            get(repository->data, i)->expiration_date_day = product.expiration_date_day;
            get(repository->data, i)->expiration_date_month = product.expiration_date_month;
            get(repository->data, i)->expiration_date_year = product.expiration_date_year;
        }
    }
    if(found==0)
    {
        return -1;
    }
    return 0;
}

int addProduct(Repository * repository, Product * product)
{

    if (repository == NULL || product == NULL)
        return -1;

    add(repository->data, product);

    return 0;
}

int deleteProduct(Repository *repository, Product product)
{
    if(repository == NULL)
        return -1;
    for(int i=0; i<getLength(repository->data); i++)
        if(strcmp(getProductOnPos(repository, i)->name, product.name)==0 && strcmp(getProductOnPos(repository, i)->category, product.category)==0)
        {
            delete(repository->data, i);
            return 0;
        }
    return -1;
}

int getRepoLength(Repository * v)
{
    if (v == NULL)
        return -1;

    return getLength(v->data);
}

Product * getProductOnPos(Repository * v, int pos)
{
    if (v == NULL)
        return NULL;
    return get(v->data, pos);
}


Product * findByNameCategory(Repository * repo, char* name, char* category) {
    if (repo == NULL || name == NULL) {
        return NULL;
    }
    for (int i = 0; i < getLength(repo->data); i++) {
        Product * p = get(repo->data, i);
        if (strcmp(getName(p), name) == 0 && strcmp(getCategory(p), category) == 0) {
            return p;
        }
        free(p);
    }
    return NULL;
}

// this function filters the data in repo and keeps only the products which expire in X days
void choose_products_exp_X_days(Repository *secondary_repository, int X)
{
    for(int i=0; i<getRepoLength(secondary_repository); i++)
        if(getDays(getProductOnPos(secondary_repository, i)) > X || getDays(getProductOnPos(secondary_repository, i))<0) {
            deleteProduct(secondary_repository, *getProductOnPos(secondary_repository, i));
            i--;
        }
}