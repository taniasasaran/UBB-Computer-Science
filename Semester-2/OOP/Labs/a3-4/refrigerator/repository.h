#pragma once

#include "DynamicArrayProduct.h"
#include "stdlib.h"

typedef struct
{
    DynamicArrayProduct* data;
    int length;
} Repository;

Repository * createRepo();


/// <summary>
/// Destroys a given planet repository. The memory is freed.
/// </summary>
void destroyRepo(Repository * v);

int addProduct(Repository * repository, Product * product);

int getRepoLength(Repository * repo);

int deleteProduct(Repository * repo, Product product);
int updateProduct(Repository * repo, Product product);

void choose_products_exp_X_days(Repository *secondary_repository, int X);

Product * findByNameCategory(Repository * repo, char* name, char* category);

Product * getProductOnPos(Repository * v, int pos);