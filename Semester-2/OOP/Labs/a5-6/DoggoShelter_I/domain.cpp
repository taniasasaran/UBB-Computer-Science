#include "domain.h"
#include <cstring>
#include <exception>
#include <string>
#include <ostream>
#include <iostream>

Dog::Dog(std::string breed, std::string name, int age, std::string photograph){
    this->age = age;
    this->breed = breed;
    this->name = name;
    this->photograph = photograph;
}

Dog::Dog(const Dog &m)
{
    this->age = m.age;
    this->breed = m.breed;
    this->name = m.name;
    this->photograph = m.photograph;
}

std::string Dog::getBreed(){
    return this->breed;
}

std::string Dog::getName(){
    return this->name;
}
int Dog::getAge() const{
    return this->age;
}

std::string Dog::getPhotograph(){
    return this->photograph;
}

bool Dog::operator==(Dog &m) {
    bool result = true;
    if(this->breed != m.breed)
        result = false;
    if(this->name != m.name)
        result = false;
    return result;
}

std::string Dog::toString() {
    std::string str;
    str.append(this->breed);
    str.append(", ");
    str.append(this->name);
    str.append(", ");
    str.append(std::to_string(this->age));
    str.append(", ");
    str.append(this->photograph);
    return str;
}

