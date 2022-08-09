#include "Medication.h"

Medication * createMedication(char* name, int concentration, int quantity, int price)
{
    Medication* m = (Medication*)malloc(sizeof(Medication));
    if (m == NULL)
        return NULL;
    strcpy(m->name, name);
    m->quantity = quantity;
    m->concentration = concentration;
    m->price = price;
    return m;
}

Medication* createCopyMedication(Medication* medication)
{
    if (medication == NULL)
        return NULL;
    Medication* new_med = createMedication(getName(medication), getConcentration(medication), getQuantity(medication),
                                           getPrice(medication));
    return new_med;
}

void destroyMedication(Medication * m) // the memory is freed
{
    if(m == NULL)
        return;
    free(m);
}

void copyMedication(Medication* destination_med, Medication* source_med)
{
    strcpy(destination_med->name, getName(source_med));
    destination_med->concentration = getConcentration(source_med);
    destination_med->quantity = getQuantity(source_med);
    destination_med->price = getPrice(source_med);
}

char* getName(Medication * m)
{
    if (m == NULL)
        return NULL;
    return m->name;
}

int getConcentration(Medication * m)
{
    if (m == NULL)
        return -1;
    return m->concentration;
}

int getQuantity(Medication * m)
{
    if (m == NULL)
        return -1;
    return m->quantity;
}

int getPrice(Medication * m)
{
    if (m == NULL)
        return -1;
    return m->price;
}

void toString(Medication * m, char str[])
{
    if (m == NULL)
        return;
    sprintf(str, "%s with concentration %d%%, qty %d and price %d \n", m->name, m->concentration, m->quantity, m->price);
}
