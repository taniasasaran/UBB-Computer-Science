#pragma once

#include "repository.h"
#include "DynamicArray.h"

typedef struct
{
    Repository* repository;
    DynamicArray* UndoStack;
    DynamicArray* RedoStack;
} Service;

Service* createService(Repository * r);
void destroyService(Service* s);
void populateRepo(Service* s);
/// <summary>
/// Adds a planet to the repository of planets.
/// </summary>
/// <param name="s">Pointer to theService.</param>
/// <param name = "name">A string, the name of the planet.</param>
/// <param name = "type">A string, the planet's type.</param>
/// <param name = "distanceFromEarth">Double, the distance from the planet to Earth, in light years.</param>
/// <returns>1 - if the planet was sucessfully added; 0 - if the planet could not be added, as another planet with the same symbol already exists.</returns>
int addMedicineServ(Service* s, char* name, int concentration, int quantity, int price);
Repository * getRepo(Service* s);

int deleteMedicineServ(Service* s, char* name, int c);

int updateMedicineServ(Service* s, char* name, int concentration, int quantity, int price);
void boblesort_quantity(Repository *repository);

void boblesort_name(Repository *repository);

void choose_medicine_given_string(Service *service, Repository *secondary_repository, char string[50]);

void choose_medicine_given_string_sorted(Service *service, Repository *secondary_repository, char string[50]);
void choose_medicine_less_than_X_items(Service *service, Repository *secondary_repository, int X);

/*
* Return 0 - success; -1 - error; 1 - no more undos
*/
int undo(Service* s);

int redo(Service* s);
