#include "tests.h"

void test_add()
{
    Repository *repo = createRepo();
    Service * srv = createService(repo);
    Product *p1 = createProduct("dulce", "sweets", 10, 2, 3, 2022);
    addProductServ(srv, "dulce", "sweets", 10, 2, 3, 2022);
    int ok=1;
    if(getRepoLength(repo)!=1)
        ok=0;
    Product *check = getProductOnPos(srv->repository, 0);
    if(strcmp(check->name, p1->name)!=0 || strcmp(check->category,p1->category)!=0 || check->quantity!=p1->quantity || check->expiration_date_day!=p1->expiration_date_day || check->expiration_date_month!=p1->expiration_date_month || check->expiration_date_year!=p1->expiration_date_year)
        ok=0;
    if(ok==1)
        printf("test add ok\n");
    destroyProduct(check);
    free(srv);
}

void test_remove()
{
    Repository* repo = createRepo();
    Service *srv = createService(repo);
    Product* p1 = createProduct("dulce", "sweets", 10, 2, 3, 2022);
    addProductServ(srv, "dulce", "sweets", 10, 2, 3, 2022);
    Product* p2 =  findByNameCategory(repo, p1->name, p1->category);
    deleteProductServ(srv, p2->name, p2->category);
    if(getRepoLength(repo)==0)
        printf("test remove ok\n");
    free(srv);
}

void test_update()
{
    Repository* repo = createRepo();
    Service* srv = createService(repo);
    Product* p1 = createProduct("dulce", "sweets", 10, 2, 3, 2022);
    addProductServ(srv, "dulce", "sweets", 10, 2, 3, 2022);
    updateProductServ(srv, p1->name, p1->category, 200, 3, 4, 3000);
    Product* found = findByNameCategory(repo, "dulce", "sweets");
    if(found->expiration_date_year == 3000)
        if(found->expiration_date_month == 4)
            if(found->expiration_date_day == 3)
                if(found->quantity == 200)
                    printf("test update ok\n");
    free(srv);
    free(found);
}

void test_undo_redo()
{
    int ok = 0;
    Repository* repo;
    repo = createRepo();
    Service* s = createService(repo);
    addProductServ(s, "dulce", "sweets", 10, 2, 3, 2022);
    if(getRepoLength(repo)==1)
        ok=1;
    undo(s);
    if(getRepoLength(repo)!=0)
        ok=0;
    redo(s);
    if(getRepoLength(repo)!=1)
        ok=0;
    if(ok==1)
        printf("test undoredo ok\n");
    free(s);
}

void test_find()
{
    Repository* repo = createRepo();
    Service* srv = createService(repo);
    Product* p1 = createProduct("dulce", "sweets", 10, 2, 3, 2022);
    addProductServ(srv, "dulce", "sweets", 10, 2, 3, 2022);
    Product *check = findByNameCategory(srv->repository, "dulce", "sweets");
    int ok=1;
    if(strcmp(check->name, p1->name)!=0 || strcmp(check->category,p1->category)!=0 || check->quantity!=p1->quantity || check->expiration_date_day!=p1->expiration_date_day || check->expiration_date_month!=p1->expiration_date_month || check->expiration_date_year!=p1->expiration_date_year)
        ok=0;
    if(ok==1)
        printf("test find ok\n");
    destroyProduct(p1);
    destroyProduct(check);
    free(repo);
}

void test_sort_filter()
{
    Repository* repo = createRepo();
    Service* s = createService(repo);
    populateRepo(s);
    Repository *secondary = createRepo();
    choose_products_given_food_exp_x_days(s, secondary, "dairy", 10000);
    Product *check = getProductOnPos(secondary, 0);
    if(getDays(check)<10000 && getDays(check)>0)
        printf("filter x days ok\n");
    choose_products_given_food_sorted(s, secondary, "dairy");
    if(getProductOnPos(secondary, 0)->expiration_date_month < getProductOnPos(secondary, 1)->expiration_date_month)
        printf("month sort ok\n");
    choose_products_given_string_sorted(s, secondary, "l");
    if(getProductOnPos(secondary, 0)->quantity < getProductOnPos(secondary, 1)->quantity)
        printf("quantity sort ok\n");
    free(check);
    free(s);
    free(secondary);
}

void test_all()
{
    printf("------tests------\n");
    test_add();
    test_remove();
    test_update();
    test_find();
    test_sort_filter();
    test_undo_redo();
    printf("-----------------\n");
}


