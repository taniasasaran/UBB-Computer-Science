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
    printf("Type 1 to add a medicine.\n");
    printf("Type 2 to delete a medicine.\n");
    printf("Type 3 to update a medicine.\n");
    printf("Type 4 to display all medicine whose name contains a given string, and show them "
           "sorted ascending by name.\n");
    printf("Type 5 to display all medicine in short supply (quantity less than X). \n");
    printf("Type 6 to undo LPO. \n");
    printf("Type 7 to redo LPO. \n");
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

int read_medicine(char* name, int* concentration, int* quantity, int* price)
{
    printf("name: ");
    scanf(" %s", name);
    printf("concentration: ");
    scanf(" %d", concentration);
    if(concentration<0)
        return 0;
    printf("quantity: ");
    scanf("%d", quantity);
    if(quantity<0)
        return 0;
    printf("price: ");
    scanf("%d", price);
    if(price<0)
        return 0;
    return 1;

}

int read_name_concentration(char* name, int* concentration)
{
    printf("name: ");
    scanf(" %s", name);
    printf("concentration: ");
    scanf(" %d", concentration);
    if(concentration<0)
        return 0;
    return 1;
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
        Medication * m = getEntityOnPos(repository, i);
        char medString[200];
        toString(m, medString);
        printf("%s", medString);
    }
    printf("\n");
}

int undoUI(UI* ui)
{
    int res= undo(ui->serv);
    print_repo(ui->serv->repository);
    printf("\n");
    return res;
}

int redoUI(UI* ui)
{
    return redo(ui->serv);
}

void startUI(UI *ui)
{
    printf("Welcome to Home SmartApps\n");
    int user_command, valid, concentration, quantity, price;
    char string[50], name[50];
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
            valid = read_medicine(name, &concentration, &quantity, &price);
            if(valid!=0)
                addMedicineServ(ui->serv, name, concentration, quantity, price);
        }
        else if(user_command==2)
        {
            valid = read_name_concentration(name, &concentration);
            if(valid!=0)
                deleteMedicineServ(ui->serv, name, concentration);
        }
        else if(user_command==3)
        {
            valid = read_medicine(name, &concentration, &quantity, &price);
            if(valid!=0)
                updateMedicineServ(ui->serv, name, concentration, quantity, price);
        }
        else if(user_command==4)
        {
            read_string(string);
            Repository* secondary_repository = createRepo();
            choose_medicine_given_string_sorted(ui->serv, secondary_repository, string);
            print_repo(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==5)
        {
            int X = readIntegerNumber("X= ");
            Repository* secondary_repository = createRepo();
            choose_medicine_less_than_X_items(ui->serv, secondary_repository, X);
            print_repo(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==6)
        {
            int res = undoUI(ui);
            if (res == 0)
                printf("Undo successful\n");
            else
                printf("Undo unsuccessful\n");
        }
        else if(user_command==7)
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
