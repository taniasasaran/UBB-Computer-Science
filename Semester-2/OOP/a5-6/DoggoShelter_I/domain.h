#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;
public:
    Dog(std::string breed="", std::string name="", int age=0, std::string photograph="");
    // this function is the constructor of the dog object; it has some predefined values

    Dog(const Dog &m);
    // copy constructor of the class

    ~Dog() {};
    //destructor of the dog object

    bool operator==(Dog &m);
    // overloading of the == operator

    std::string getBreed();
    // a getter for the breed represented on a std::string

    std::string getName();
    // a getter for the name represented on a std::string

    int getAge() const;
    // a getter for the age represented as an integer

    std::string getPhotograph();
    // a getter for the photograph represented on a std::string

    std::string toString();
};
