#pragma once
#include "service.h"
#include "iostream"
using namespace std;

class UI{
private:
    Service service;
public:
    UI();
    ~UI();
    bool addUI(std::string breed, std::string name, int age, std::string photo) ;
    bool removeUI(std::string breed, std::string name);
    bool updateUI(std::string breed, std::string name, Dog dog);
    void displayDogs(DynamicVector<Dog> v);
    void startUI();
    int readInteger();
    void printAdminMenu();
    void printUserMenu();
    void openLink(Dog dog);
};
