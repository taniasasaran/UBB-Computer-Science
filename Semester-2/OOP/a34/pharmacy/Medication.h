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

Medication * createMedication(char* name, int concentration, int quantity, int price);
void destroyMedication(Medication * m); // the memory is freed

char* getName(Medication * m);
int getConcentration(Medication * m);
int getQuantity(Medication * m);
int getPrice(Medication* m);
Medication* createCopyMedication(Medication* medication);
void copy_medication(Medication*, Medication*);

void toString(Medication * m, char str[]);