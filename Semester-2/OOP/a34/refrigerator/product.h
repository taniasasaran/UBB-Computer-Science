
#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[50];
    char category[10]; // (one of dairy, sweets, meat or fruit)
    int quantity;
    int expiration_date_day;
    int expiration_date_month;
    int expiration_date_year;
} Product;

Product * createProduct(char* name, char* category, int quantity, int expiration_date_day, int expiration_date_month, int expiration_date_year);
void destroyProduct(Product * p); // the memory is freed

char* getName(Product * p);
char* getCategory(Product * p);
int getQuantity(Product * p);
int getExpDateDay(Product* p);
int getExpDateMonth(Product* p);
int getExpDateYear(Product* p);
int getDays(Product *p);
Product* createCopyProduct(Product* product);
void copy_product(Product*, Product*);

void toString(Product * p, char str[]);


