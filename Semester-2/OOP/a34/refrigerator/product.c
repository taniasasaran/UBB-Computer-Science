#include <time.h>
#include "product.h"


void copy_product(Product *destination_product, Product *source_product)
{
    strcpy(destination_product->name, source_product->name);
    strcpy(destination_product->category, source_product->category);
    destination_product->expiration_date_day = source_product->expiration_date_day;
    destination_product->expiration_date_month = source_product->expiration_date_month;
    destination_product->expiration_date_year = source_product->expiration_date_year;
    destination_product->quantity = source_product->quantity;
}

Product * createProduct(char* name, char* category, int quantity, int expiration_date_day, int expiration_date_month, int expiration_date_year)
{
    Product* p = malloc(sizeof(Product));
    strcpy(p->name, name);
    strcpy(p->category, category);

    p->quantity = quantity;
    p->expiration_date_day = expiration_date_day;
    p->expiration_date_month = expiration_date_month;
    p->expiration_date_year = expiration_date_year;

    return p;
}

Product* createCopyProduct(Product* product)
{
    if (product == NULL)
        return NULL;
    Product* new_product = createProduct(product->name, product->category, getQuantity(product),
                                        getExpDateDay(product), getExpDateMonth(product), getExpDateYear(product));
    return new_product;
}

void destroyProduct(Product * p) // the memory is freed
{
    if(p==NULL)
        return;

    free(p);
}

int getDays(Product* p)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
//    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    int years = p->expiration_date_year - (tm.tm_year + 1900);
    int month = p->expiration_date_month - (tm.tm_mon + 1);
    int day = p->expiration_date_day - tm.tm_mday;
    int total_time = day + month*30 + years*365;
    return total_time;
}

char* getName(Product * p)
{
    if (p == NULL)
        return NULL;
    return p->name;
}

char* getCategory(Product * p)
{
    if (p == NULL)
        return NULL;
    return p->category;
}

int getQuantity(Product * p)
{
    if (p == NULL)
        return -1;
    return p->quantity;
}

int getExpDateDay(Product * p)
{
    if (p == NULL)
        return -1;
    return p->expiration_date_day;
}

int getExpDateMonth(Product * p)
{
    if (p == NULL)
        return -1;
    return p->expiration_date_month;
}

int getExpDateYear(Product * p)
{
    if (p == NULL)
        return -1;
    return p->expiration_date_year;
}

void toString(Product * p, char str[])
{
    if (p == NULL)
        return;
    sprintf(str, "%s of %s type, exp date on %d.%d.%d, qty %d \n", p->name, p->category, p->expiration_date_day, p->expiration_date_month, p->expiration_date_year, p->quantity);
}
