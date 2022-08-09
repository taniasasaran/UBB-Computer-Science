#include "ui.h"


UI* createUI(Service* s)
{
    UI* ui = (UI*)malloc(sizeof(UI));
    if (ui == NULL)
        return NULL;
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

void printMenu()
{
    printf("Type 1 to add a medicine.\n");
    printf("Type 2 to delete a medicine.\n");
    printf("Type 3 to update a medicine.\n");
    printf("Type 4 to display all medicine whose name contains a given string(1) or display all medicine with odd price(2).\n");
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

int readMedicine(char* name, int* concentration, int* quantity, int* price)
{
    printf("name: ");
    scanf(" %s", name);
    printf("concentration: ");
    scanf("%d", concentration);
    if(*concentration<0) {
        printf("Concentration must be a positive integer!\n");
        return 0;
    }
    printf("quantity: ");
    scanf("%d", quantity);
    if(*quantity<0) {
        printf("Quantity must be a positive integer!\n");
        return 0;
    }
    printf("price: ");
    scanf("%d", price);
    if(*price<0) {
        printf("Price must be a positive integer!\n");
        return 0;
    }
    return 1;

}

int readNameConcentration(char* name, int* concentration)
{
    printf("name: ");
    scanf(" %s", name);
    printf("concentration: ");
    scanf(" %d", concentration);
    if (*concentration < 0) {
        printf("Concentration must be a positive integer!\n");
        return 0;
    }
    return 1;
}

void readString(char string[50])
{
    printf("string: ");
    scanf("%s", string);
}

void printRepository(Repository* repository)
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
    return undo(ui->serv);
}

int redoUI(UI* ui)
{
    return redo(ui->serv);
}

void startUI(UI *ui)
{
    printf("Welcome to Home SmartApps\n");
    int user_command, valid, concentration, quantity, price, ok=0;
    char string[50], name[50];
    while(1)
    {
        printMenu();
        user_command = readIntegerNumber("Input command: ");
        while (validCommand(user_command) == 0)
        {
            printf("Please input a valid command!\n");
            user_command = readIntegerNumber("Input command: ");
        }
        if(user_command==1)
        {
            valid = readMedicine(name, &concentration, &quantity, &price);
            if (valid == 1) {
                ok = addEntityServ(ui->serv, name, concentration, quantity, price);
                if (ok == 0)
                    printf("Medicine added.\n");
                else
                    printf("Medicine could not be added.\n");
            }
        }
        else if(user_command==2)
        {
            valid = readNameConcentration(name, &concentration);
            if(valid == 1) {
                ok = deleteEntityServ(ui->serv, name, concentration);
                if (ok == 0)
                    printf("Medicine deleted.\n");
                else
                    printf("Medicine could not be deleted.\n");
            }
        }
        else if(user_command==3)
        {
            valid = readMedicine(name, &concentration, &quantity, &price);
            if(valid == 1) {
                ok = updateEntityServ(ui->serv, name, concentration, quantity, price);;
                if (ok == 0)
                    printf("Medicine updated.\n");
                else
                    printf("Medicine could not be updated.\n");
            }
        }
        else if(user_command==4)
        {
            Repository* secondary_repository = createRepo();
            int filter = readIntegerNumber("type 1 for default(string), type 2 for odd price:");
            int sort = readIntegerNumber("type 1 for ascending, type 2 for descending (by name):");
            if (sort == 1)
                if (filter == 1) {
                    readString(string);
                    chooseMedicineGivenStringSorted(ui->serv, secondary_repository, string, isCharGreater);
                }
                else if (filter == 2)
                    chooseMedicineOddPriceSorted(ui->serv, secondary_repository, isCharGreater);
                else
                    printf("ooops, try again");
            else if (sort == 2)
                if (filter == 1) {
                    readString(string);
                    chooseMedicineGivenStringSorted(ui->serv, secondary_repository, string, isCharSmaller);
                }
                else if (filter == 2)
                    chooseMedicineOddPriceSorted(ui->serv, secondary_repository, isCharSmaller);
                else
                    printf("ooops, try again");
            else
                printf("ooops, try again");
            printRepository(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==5)
        {
            int X = readIntegerNumber("X= ");
            Repository* secondary_repository = createRepo();
            int sort = readIntegerNumber("type 1 for ascending, type 2 for descending (by quantity):");
            if(sort == 1)
                chooseMedicineLessThanXItemsSorted(ui->serv, secondary_repository, X, isNumberGreater);
            else if (sort == 2)
                chooseMedicineLessThanXItemsSorted(ui->serv, secondary_repository, X, isNumberSmaller);
            else
                printf("ooops, try again");
            printRepository(secondary_repository);
            destroyRepo(secondary_repository);
        }
        else if(user_command==6)
        {
            ok = undoUI(ui);
            if (ok == 0)
                printf("Undo successful\n");
            else if (ok == 1)
                printf("No more undos!\n");
            else
                printf("Undo unsuccessful\n");
        }
        else if(user_command==7)
        {
            ok = redoUI(ui);
            if (ok == 0)
                printf("Redo successful\n");
            else if (ok == 1)
                printf("No more redos!\n");
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
