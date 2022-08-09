#pragma once

#include "repository.h"
#include "DynamicArray.h"

typedef int (*ComparisonIntFunction)(int, int);
typedef int (*ComparisonCharFunction)(char*, char*);

typedef struct
{
    Repository* repository;
    DynamicArray* UndoStack;
    DynamicArray* RedoStack;
} Service;

/// <summary>
/// Creates the service which will manage the repository and the undo-redo.
/// </summary>
/// <param name="r">The repository service will operate on.</param>
/// <returns>A pointer the the created service.</returns>
Service* createService(Repository * r);

/// <summary>
/// Destroys the service.
/// </summary>
/// <param name="s">The service to be destroyed.</param>
void destroyService(Service* s);

/// <summary>
/// Populates the repository associated to the service.
/// </summary>
/// <param name="s">The service to be worked with.</param>
void populateRepo(Service* s);

/// <summary>
/// Returns the repository of the service.
/// </summary>
/// <param name="s">The service to be worked with.</param>
/// <returns>A pointer to the repository of the given service.</returns>
Repository* getRepo(Service* s);

/// <summary>
/// Adds an entity to the repository.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the entity.</param>
/// <param name = "concentration">Integer, the entity's concentration.</param>
/// <param name = "quantity">Integer, the entity's quantity.</param>
/// <param name = "price">Integer, the entity's price.</param>
/// <returns>0 - if the entity was sucessfully added; -1 - if the entity could not be added.</returns>
int addEntityServ(Service* s, char* name, int concentration, int quantity, int price);

/// <summary>
/// Deletes an entity from the repository.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the entity.</param>
/// <param name = "concentration">Integer, the entity's concentration.</param>
/// <returns>0 - if the entity was sucessfully deleted; -1 - if the entity could not be deleted.</returns>
int deleteEntityServ(Service* s, char* name, int concentration);

/// <summary>
/// Updates a medication from the repository.
/// </summary>
/// <param name="s">Pointer to the Service.</param>
/// <param name = "name">A string, the name of the entity.</param>
/// <param name = "concentration">Integer, the entity's concentration.</param>
/// <param name = "quantity">Integer, the entity's NEW quantity.</param>
/// <param name = "price">Integer, the entity's NEW price.</param>
/// <returns>0 - if the entity was sucessfully updated; -1 - if the entity could not be updated.</returns>
int updateEntityServ(Service* s, char* name, int concentration, int quantity, int price);

/// <summary>
/// Comparison function between two strings. Checks if the first one is greater than the second one.
/// </summary>
/// <param name="a">String, the first one.</param>
/// <param name="b">String, the second one.</param>
/// <returns>1 - if a>b; 0 - otherwise.</returns>
int isCharGreater(char* a, char* b);

/// <summary>
/// Comparison function between two strings. Checks if the first one is smaller than the second one.
/// </summary>
/// <param name="a">String, the first one.</param>
/// <param name="b">String, the second one.</param>
/// <returns>1 - if a<b; 0 - otherwise.</returns>
int isCharSmaller(char* a, char* b);

/// <summary>
/// Comparison function between two integers. Checks if the first one is greater than the second one.
/// </summary>
/// <param name="a">Integer, the first one.</param>
/// <param name="b">Integer, the second one.</param>
/// <returns>1 - if a>b; 0 - otherwise.</returns>
int isNumberGreater(int a, int b);

/// <summary>
/// Comparison function between two integers. Checks if the first one is smaller than the second one.
/// </summary>
/// <param name="a">Integer, the first one.</param>
/// <param name="b">Integer, the second one.</param>
/// <returns>1 - if a<b; 0 - otherwise.</returns>
int isNumberSmaller(int a, int b);

/// <summary>
/// Function that sorts the elements in the repository based on the comparison function applied to the quantities of the elements, using bubblesort.
/// </summary>
/// <param name="repository">The repository sorted.</param>
/// <param name="cmpInt">Comparison function between two integers.</param>
void boblesortQuantity(Repository *repository, ComparisonIntFunction cmpInt);

/// <summary>
/// Function that sorts the elements in the repository based on the comparison function applied to the names of the elements, using bubblesort.
/// </summary>
/// <param name="repository">The repository sorted.</param>
/// <param name="cmpChar">Comparison function between two strings.</param>
void boblesortName(Repository *repository, ComparisonCharFunction cmpChar);

/// <summary>
/// Function that filters the data contained in the repository of the service, adding in the secondary_repository(result), only the elements which contain a given string in their name.
/// </summary>
/// <param name="service">The service worked on.</param>
/// <param name="secondary_repository">The repository resulted from the filtering.</param>
/// <param name="string">String</param>
void chooseMedicineGivenString(Service *service, Repository *secondary_repository, char string[50]);

/// <summary>
/// Function that filters the data contained in the repository of the service, adding in the secondary_repository(result), only the elements which has their price an odd number.
/// </summary>
/// <param name="service">The service worked on.</param>
/// <param name="secondary_repository">The repository resulted from the filtering.</param>
void chooseMedicineOddPrice(Service* service, Repository* secondary_repository);

/// <summary>
/// Function that filters the data contained in the repository of the service, adding in the secondary_repository(result), only the elements which are in short supply.
/// </summary>
/// <param name="service">The service worked on.</param>
/// <param name="secondary_repository">The repository resulted from the filtering.</param>
/// <param name="X">Integer, the limit from which we consider an entity to be in short supply.</param>
void chooseMedicineLessThanXItems(Service* service, Repository* secondary_repository, int X);

/// <summary>
/// Function that filters the data contained in the repository of the service, adding in the secondary_repository(result), only the elements which are in short supply and sorts them by name.
/// </summary>
/// <param name="service">The service worked on.</param>
/// <param name="secondary_repository">The repository resulted from the filtering.</param>
/// <param name="cmpChar">Comparison function between two strings.</param>
void chooseMedicineOddPriceSorted(Service* service, Repository* secondary_repository, ComparisonCharFunction cmpChar);

/// <summary>
/// Function that filters the data contained in the repository of the service, adding in the secondary_repository(result), only the elements which contain a given string in their name, sorted by name.
/// </summary>
/// <param name="service">The service worked on.</param>
/// <param name="secondary_repository">The repository resulted from the filtering.</param>
/// <param name="string">String</param>
/// <param name="cmpChar">Comparison function between two strings.</param>
void chooseMedicineGivenStringSorted(Service *service, Repository *secondary_repository, char string[50], ComparisonCharFunction cmpChar);

/// <summary>
/// Function that filters the data contained in the repository of the service, adding in the secondary_repository(result), only the elements which are in short supply, sorted by quantity/// </summary>
/// <param name="service">The service worked on.</param>
/// <param name="secondary_repository">The repository resulted from the filtering.</param>
/// <param name="X">Integer, the limit from which we consider an entity to be in short supply.</param>
/// <param name="cmpInt">Comparison function between two integers.</param>
void chooseMedicineLessThanXItemsSorted(Service *service, Repository *secondary_repository, int X, ComparisonIntFunction cmpInt);

/// <summary>
/// Undo function.
/// </summary>
/// <param name="s">The service worked on.</param>
/// <returns>0 - success; -1 - error; 1 - no more undos.</returns>
int undo(Service* s);

/// <summary>
/// Redo function.
/// </summary>
/// <param name="s">The service worked on.</param>
/// <returns>0 - success; -1 - error; 1 - no more redos.</returns>
int redo(Service* s);
