#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[50];
    int concentration;
    int quantity;
    int price;
} Medication;

/// <summary>
/// Creates a medication.
/// </summary>
/// <param name="name">Char*, the name of the medication.</param>
/// <param name="concentration">Integer, the concentration of the medication.</param>
/// <param name="quantity">Integer, the quantity of the medication.</param>
/// <param name="price">Integer, the price of the medication.</param>
/// <returns>A pointer to the created medication.</returns>
Medication * createMedication(char* name, int concentration, int quantity, int price);

/// <summary>
/// Destroys the medication.
/// </summary>
/// <param name="m">The medication to be destroyed.</param>
void destroyMedication(Medication * m); // the memory is freed

/// <summary>
/// Returns the name of the medication.
/// </summary>
/// <param name="m">The medication.</param>
/// <returns>Char*, the name of the medication.</returns>
char* getName(Medication * m);

/// <summary>
/// Returns the concentration of the medication.
/// </summary>
/// <param name="m">The medication.</param>
/// <returns>Integer, the concentration of the medication.</returns>
int getConcentration(Medication * m);

/// <summary>
/// Returns the quantity of the medication.
/// </summary>
/// <param name="m">The medication.</param>
/// <returns>Integer, the quantity of the medication.</returns>
int getQuantity(Medication * m);

/// <summary>
/// Returns the price of the medication.
/// </summary>price
/// <param name="m">The medication.</param>
/// <returns>Integer, the price of the medication.</returns>
int getPrice(Medication* m);

/// <summary>
/// Creates a copy of a medication.
/// </summary>
/// <param name="medication">pointer to the "source" medication.</param>
/// <returns>A pointer to the created(and allocated) copy of the initial medication.</returns>
Medication* createCopyMedication(Medication* medication);

/// <summary>
/// Copies the data from a medication to another.
/// </summary>
/// <param name="destination">pointer to the new copy of the source medication.</param>
/// <param name="source">pointer to a medication which will be duplicated.</param>
void copyMedication(Medication* destination, Medication* source);

/// <summary>
/// Creates a string/char representation of a medication.
/// </summary>
/// <param name="m">pointer to the medication.</param>
/// <param name="str">an array of characters which will represent the interpretation of the data stored in a medication.</param>
void toString(Medication * m, char str[]);