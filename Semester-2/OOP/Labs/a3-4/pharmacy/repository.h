#pragma once

#include "DynamicArray.h"
#include "stdlib.h"
#include "Medication.h"

typedef struct
{
    DynamicArray * data;
} Repository;

/// <summary>
/// Creates an empty repository of elements, stored in a dynamic array.
/// </summary>
/// <returns>A pointer the the created repository.</returns>
Repository * createRepo();

/// <summary>
/// Creates a copy of a repository.
/// </summary>
/// <param name="repository">pointer to the "source" repository.</param>
/// <returns>A pointer to the created(and allocated) copy of the initial repository.</returns>
Repository* createCopyRepo(Repository* repository);

/// <summary>
/// Destroys the repository.
/// </summary>
/// <param name="repository">The repository to be destroyed.</param>
void destroyRepo(Repository * repository);

/// <summary>
/// Adds a medication to the repository or increases the quantity of that medication(if it exists in the repo).
/// </summary>
/// <param name="repository">The repository.</param>
/// <param name="entity">The medication to be added.</param>
/// <returns>0 - if the entity was sucessfully added; -1 - if the entity could not be added.</returns>
int addEntity(Repository * repository, Medication* entity);

/// <summary>
/// Deletes a medication from the repository.
/// </summary>
/// <param name="repository">The repository.</param>
/// <param name="entity">The medication to be be deleted.</param>
/// <returns>0 - if the entity was sucessfully deleted; -1 - if the entity could not be deleted.</returns>
int deleteEntity(Repository * repository, Medication* entity);

/// <summary>
/// Updates a medication from the repository.
/// </summary>
/// <param name="repository">The repository.</param>
/// <param name="entity">The updated version of the initial medication. The old version is accessible via name and concentration.</param>
/// <returns>0 - if the entity was sucessfully updated; -1 - if the entity could not be updated.</returns>
int updateEntity(Repository * repository, Medication* entity);

/// <summary>
/// Returns the length of the repository.
/// </summary>
/// <param name="repository">The repository.</param>
/// <returns>The length of the repository.</returns>
int getRepoLength(Repository* repository);

/// <summary>
/// Returns the element which has the given name and concentration (pair is unique).
/// </summary>
/// <param name="repository">The repository.</param>
/// <param name="name">String, the name of the medication.</param>
/// <param name="concentration">Integer, the concentration of the medication.</param>
/// <returns>The element with the given name and concentration.</returns>
Medication * findByNameConcentration(Repository * repository, char* name, int concentration);

/// <summary>
/// Returns the element on a given position.
/// </summary>
/// <param name="repository">The repository.</param>
/// <param name="pos">The position - must be a valid position.</param>
/// <returns>The element on the given position.</returns>
Medication * getEntityOnPos(Repository * repository, int pos);