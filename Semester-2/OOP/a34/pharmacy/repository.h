#pragma once

#include "DynamicArray.h"
#include "stdlib.h"
#include "Medication.h"

typedef struct
{
    DynamicArray * data;
    int length;
} Repository;

Repository * createRepo();
Repository* createCopyRepo(Repository* repo);
void destroyRepo(Repository * v);

int addEntity(Repository * repository, Medication* entity);

int getRepoLength(Repository * repo);
int deleteEntity(Repository * repo, Medication* entity);
int updateEntity(Repository * repo, Medication* entity);

//void choose_products_exp_X_days(Repository *secondary_repository, int X);

Medication * findByNameConcentration(Repository * repo, char* name, int concentration);

Medication * getEntityOnPos(Repository * v, int pos);