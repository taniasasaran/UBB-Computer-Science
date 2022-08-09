//
// Created by TANIA on 3/13/2022.
//

#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crtdbg.h"

UI* createUI(Service* s)
{
    UI* ui = (UI*)malloc(sizeof(UI));
    ui->serv = s;

    return ui;
}

void destroyUI(UI * ui)
{
    destroyService(ui->serv);
    free(ui);
}

/*
	Prints the available menu for the problem
	Input: -
	Output: the menu is printed at the console
*/

void print_menu()
{
    printf("Type 1 to add a product.\n");
    printf("Type 2 to delete a product.\n");
    printf("Type 3 to update a product.\n");
    printf("Type 4 to display all products whose name contains a given string, and show them "
           "sorted ascending by the existing quantity.\n");
    printf("Type 5 to see all products, sorted ascending by expiration month, for a given category. \n");
    printf("Type 6 to display all products of a given category which expire in the following X days. \n");
    printf("Type 7 to undo LPO. \n");
    printf("Type 8 to redo LPO. \n");
    printf("Type 0 to exit the app. \n");
}

int validCommand(int command)
{
    if (command >= 0 && command <= 8)
        return 1;
    return 0;
}
/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number. */
int readIntegerNumber(const char* message)
{
    char s[16];
    int res = 0;
    int flag = 0;
    int r = 0;

    while (flag == 0)
    {
        printf(message);
        scanf("%s", s);

        r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
        flag = (r == 1);
        if (flag == 0)
            printf("Error reading number!\n");
    }
    return res;
}

int read_product(char* name, char* category, int* day, int* month, int* year, int* quantity)
{
    //char name[50], category[6], expiration_date[10];
    //int quantity;
    char category_words[4][10];
    strcpy(category_words[0], "dairy");
    strcpy(category_words[1], "sweets");
    strcpy(category_words[2], "meat");
    strcpy(category_words[3], "fruit");

    printf("name: ");
    scanf(" %s", name);
    printf("category: ");
    scanf(" %s", category);
    int valid = 0;
    for(int i=0; i<4; i++)
    {
        if(strcmp(category_words[i], category)==0)
        {
            valid = 1;
            break;
        }
    }

    if(valid == 0)
    {
        printf("Category not valid!\n");
        return 0;
    }

    printf("expiration_date \n");
    printf("day: ");
    scanf("%d", day);

    printf("month: ");
    scanf("%d", month);

    printf("year: ");
    scanf("%d", year);

    printf("quantity: ");
    scanf("%d", quantity);

    return 1;

}

int read_name_category(char* name, char* category)
{
    char category_words[4][10];
    strcpy(category_words[0], "dairy");
    strcpy(category_words[1], "fruit");
    strcpy(category_words[2], "meat");
    strcpy(category_words[3], "sweets");

    printf("name: ");
    scanf("%s", name);
    printf("category: ");
    scanf("%s", category);
    for(int i=0; i<4; i++)
    {
        if(strcmp(category_words[i], category)==0)
        {
            return 1;
        }
    }
    printf("Category not valid!\n");
    return 0;
}

void read_string(char string[50])
{
    printf("string: ");
    scanf("%s", string);
}

void print_repo(Repository* repository)
{
    int length = getRepoLength(repository);
    for(int i=0; i<length; i++)
    {
        Product * product = getProductOnPos(repository, i);
        char productString[200];
        toString(product, productString);
        printf("%s", productString);
    }
    printf("\n");
}

int undoUI(UI* ui)
{
    return undo(ui->serv);
}

int redoUI(UI* ui)
{
    return redo(ui->serv);
}

void startUI(UI *ui)
{
    printf("Welcome to Home SmartApps\n");
    int user_command, valid;
    char string[50];
    char name[50], category[10];
    int quantity, expiration_date_day, expiration_date_month, expiration_date_year;
    while(1)
    {
        print_menu();
        user_command = readIntegerNumber("Input command: ");
        while (validCommand(user_command) == 0)
        {
            printf("Please input a valid command!\n");
            user_command = readIntegerNumber("Input command: ");
        }
        if(user_command==1)
        {
            valid = read_product(name, category, &expiration_date_day, &expiration_date_month, &expiration_date_year, &quantity);
            if(valid!=0)
                addProductServ(ui->serv, name, category, quantity,  expiration_date_day, expiration_date_month, expiration_date_year);
        }
        else if(user_command==2)
        {
            valid = read_name_category(name, category);
            if(valid!=0)
                deleteProductServ(ui->serv, name, category);
        }
        else if(user_command==3)
        {
            valid = read_product(name, category, &expiration_date_day, &expiration_date_month, &expiration_date_year, &quantity);
            if(valid!=0)
                updateProductServ(ui->serv, name, category, quantity,  expiration_date_day, expiration_date_month, expiration_date_year);
        }
        else if(user_command==4)
        {
            read_string(string);
            Repository* secondary_repository = createRepo();
            choose_products_given_string_sorted(ui->serv, secondary_repository, string);
            print_repo(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==5)
        {
            read_string(string);
            Repository* secondary_repository = createRepo();
            choose_products_given_food_sorted(ui->serv, secondary_repository, string);
            print_repo(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==6)
        {
            read_string(string);
            int X = readIntegerNumber("X= ");
            Repository* secondary_repository = createRepo();
            choose_products_given_food_exp_x_days(ui->serv, secondary_repository, string, X);
            print_repo(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==7)
        {
            int res = undoUI(ui);
            if (res == 0)
                printf("Undo successful\n");
            else
                printf("Undo unsuccessful\n");
        }
        else if(user_command==8)
        {
            int result = redoUI(ui);
            if (result == 0)
                printf("Redo successful\n");
            else
                printf("Redo unsuccessful\n");
        }
        else if(user_command==0)
        {
            return;
        }
        else
        {
            printf("Menu command not available!\n");
        }
    }

}
