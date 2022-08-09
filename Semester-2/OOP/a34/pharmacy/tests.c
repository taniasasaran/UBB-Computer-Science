#include "tests.h"

void test_add()
{
    Repository *repo = createRepo();
    Service * srv = createService(repo);
    Medication *p1 = createMedication("algo", 10, 1000, 10);
    addEntityServ(srv, "algo", 10, 1000, 10);
    int ok=1;
    if(getRepoLength(repo)!=1)
        ok=0;
    Medication *check = getEntityOnPos(srv->repository, 0);
    if(strcmp(getName(check), getName(p1))!=0 || getConcentration(p1)!=getConcentration(check) || getQuantity(check)!= getQuantity(p1) || getPrice(check)!=getPrice(p1))
        ok=0;
    if(ok==1)
        printf("test add ok\n");
    destroyService(srv);
    destroyMedication(p1);
}

void test_remove()
{
    Repository* repo = createRepo();
    Service *srv = createService(repo);
    Medication* p1 = createMedication("algo", 10, 1000, 10);
    addEntityServ(srv, "algo", 10, 1000, 10);
    Medication* p2 =  findByNameConcentration(repo, getName(p1), getConcentration(p1));
    deleteEntityServ(srv, getName(p2), getConcentration(p2));
    if(getRepoLength(repo)==0)
        printf("test remove ok\n");
    destroyService(srv);
    destroyMedication(p1);
}

void test_update()
{
    Repository* repo = createRepo();
    Service* srv = createService(repo);
    Medication* p1 = createMedication("algo", 10, 1000, 10);
    addEntityServ(srv, "algo", 10, 1000, 10);
    updateEntityServ(srv, getName(p1), getConcentration(p1), 300, 15);
    Medication* found = findByNameConcentration(repo, getName(p1), getConcentration(p1));
    if(getQuantity(found) == 300)
        if(getPrice(found) == 15)
            printf("test update ok\n");
    destroyService(srv);
    destroyMedication(p1);
}

void test_undo_redo()
{
    int ok = 0;
    Repository* repo;
    repo = createRepo();
    Service* s = createService(repo);
    addEntityServ(s, "algo", 10, 1000, 10);
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
    destroyService(s);
}

void test_find()
{
    Repository* repo = createRepo();
    Service* srv = createService(repo);
    Medication* p1 = createMedication("algo", 10, 1000, 10);
    addEntityServ(srv, "algo", 10, 1000, 10);
    Medication* check = findByNameConcentration(repo, getName(p1), getConcentration(p1));
    int ok=1;
    if(strcmp(check->name, p1->name)!=0 || check->quantity!=p1->quantity || check->concentration!=p1->concentration || check->price!=p1->price)
        ok=0;
    if(ok==1)
        printf("test find ok\n");
    destroyMedication(p1);
    destroyService(srv);
}

void test_sort_filter()
{
    Repository* repo = createRepo();
    Service* s = createService(repo);
    populateRepo(s);
    Repository *secondary = createRepo();
    chooseMedicineGivenStringSorted(s, secondary, "-", isCharSmaller);
    Medication* check1 = getEntityOnPos(secondary, 0);
    Medication* check2 = getEntityOnPos(secondary, 1);
    if(strstr(getName(check1),"-")>=0 && strstr(getName(check2), "-") >= 0)
        if(strcmp(getName(check1), getName(check2))>0)
            printf("filter&sort string ok\n");
    destroyRepo(secondary);

    Repository* r = createRepo();
    chooseMedicineLessThanXItemsSorted(s, r, 2000, isNumberGreater);
    check1 = getEntityOnPos(r, 0);
    check2 = getEntityOnPos(r, 1);
    if(getQuantity(check1)<=getQuantity(check2) && getQuantity(check1)<=2000 && getQuantity(check2)<=2000)
        printf("quantity filter-sort ok\n");
    destroyRepo(r);

    Repository* repository = createRepo();
    chooseMedicineOddPriceSorted(s, repository, isCharGreater);
    check1 = getEntityOnPos(repository, 0);
    check2 = getEntityOnPos(repository, 1);
    if (strcmp(getName(check1), getName(check2)) < 0)
        if(getPrice(check1)%2==1 && getPrice(check2)%2==1)
            printf("odd filter-sort ok\n");
    destroyRepo(repository);
    destroyService(s);
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