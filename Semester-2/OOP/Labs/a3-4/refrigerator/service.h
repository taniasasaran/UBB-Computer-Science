#pragma once

#include "repository.h"
#include "DynamicArrayOperation.h"

typedef struct
{
    Repository * repository;
    DynamicArrayOperation* undoStack;
    DynamicArrayOperation* redoStack;
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
int addProductServ(Service* s, char* name, char* category, int quantity, int expiration_date_day, int expiration_date_month, int expiration_date_year);

Repository * getRepo(Service* s);

int deleteProductServ(Service* s, char* name, char* category);

int updateProductServ(Service* s, char* name, char* category, int quantity, int expiration_date_day, int expiration_date_month, int expiration_date_year);

void boblesort_quantity(Repository *repository);

void boblesort_month(Repository *repository);

void choose_products_given_string(Service *service, Repository *secondary_repository, char string[50]);
void choose_products_given_food(Service *service, Repository *secondary_repository, char string[50]);

void choose_products_given_string_sorted(Service *service, Repository *secondary_repository, char string[50]);
void choose_products_given_food_sorted(Service *service, Repository *secondary_repository, char string[50]);
void choose_products_given_food_exp_x_days(Service *service, Repository *secondary_repository, char string[50], int X);

/*
* Return 0 - succes; -1 - error; 1 - no more undos
*/
int undo(Service* s);

int redo(Service* s);
