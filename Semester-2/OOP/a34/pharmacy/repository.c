#include "repository.h"

Repository* createRepo()
{
    Repository * repository = (Repository *)malloc(sizeof(Repository));
    if (repository == NULL)
        return NULL;
    repository->data = createDynamicArray(CAPACITY, (DestroyElementFunctionType) &destroyMedication);
    return repository;
}

Repository* createCopyRepo(Repository* repo)
{
    Repository * repository = (Repository *)malloc(sizeof(Repository));
    if (repository == NULL || repo == NULL)
        return NULL;
    repository->data = createDynamicArray(CAPACITY, (DestroyElementFunctionType) &destroyMedication);
    for(int i=0; i<getRepoLength(repo); i++) {
        Medication *med = getEntityOnPos(repo, i);
        Medication *m = createCopyMedication(med);
        addEntity(repository, m);
    }
    return repository;
}

void destroyRepo(Repository * repository)
{
    if (repository == NULL)
        return;
    destroy(repository->data);
    free(repository);
}

int updateEntity(Repository *repository, Medication* entity)
{
    if (repository == NULL || entity == NULL)
        return -1;
    int found = 0;
    Medication * med_updated = (Medication*) entity;
    Medication * med_before;
    for(int i=0; i<getLength(repository->data); i++)
    {
        med_before = (Medication*)(get(repository->data, i));
        if (strcmp(getName(med_before), getName(med_updated))==0 &&
                getConcentration(med_before)==getConcentration(med_updated))
        {
            found = 1;
            med_before->quantity = med_updated->quantity;
            med_before->price = med_updated->price;
        }
    }
    destroyMedication(med_updated);
    if(found==0)
    {
        return -1;
    }
    return 0;
}

int addEntity(Repository * repository, Medication* entity)
{

    if (repository == NULL || entity == NULL)
        return -1;
    Medication* med = findByNameConcentration(repository, getName(entity), getConcentration(entity));
    if(med == NULL)
        add(repository->data, entity);
    else
    {
        med->quantity += getQuantity(entity);
        med->price = getPrice(entity);
    }
    return 0;
}

int deleteEntity(Repository *repository, Medication* entity)
{
    if(repository == NULL || entity == NULL)
        return -1;
    for(int i=0; i<getLength(repository->data); i++)
        if(strcmp(getName(getEntityOnPos(repository, i)), getName(entity))==0 && getConcentration(getEntityOnPos(repository, i))==getConcentration(entity))
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

Medication * getEntityOnPos(Repository * v, int pos)
{
    if (v == NULL)
        return NULL;
    return (Medication*)get(v->data, pos);
}


Medication * findByNameConcentration(Repository * repo, char* name, int concentration) {
    if (repo == NULL || name == NULL) {
        return NULL;
    }
    for (int i = 0; i < getLength(repo->data); i++) {
        Medication * m = (Medication*) get(repo->data, i);
        if (strcmp(getName(m), name) == 0 && getConcentration(m)==concentration) {
            return m;
        }
    }
    return NULL;
}
