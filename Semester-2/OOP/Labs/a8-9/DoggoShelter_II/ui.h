#pragma once
#include "service.h"
#include "iostream"
#include "file.h"

class UI{
private:
    Service service;
public:
    UI(Service service);
    ~UI();
    void addUI(std::string breed, std::string name, int age, std::string photo);
    void removeUI(std::string breed, std::string name);
    void updateUI(std::string breed, std::string name, Dog dog);
    void displayDogs(std::vector<Dog> v);
    void startUI();
    int readInteger();
    void printAdminMenu();
    void printUserMenu();
    void openLink(Dog dog);
    void userRoutineCsv(FileCSV adoptionList);
    void userRoutineHtml(FileHTML adoptionList);
    void adminRoutine();
};
