#pragma once

#include "domain.h"
#include "Dynamic_Vector.h"

class Repository{
private:
    DynamicVector<Dog> data;

public:
    Repository();     // this is the constructor of the repo; it associates a dynamic vector to the data in the repository
    Repository(const Repository& r) {this->data = r.data;}  // this is the copy constructor; it returns an object of type Repository
    ~Repository(){}   // this is the destructor of the repository; the destructor of the dynamic vector is called automatically

    bool add(Dog dog);
    // this function gets an object as a parameter and tries to add it to the repository
    // returns true if it succeeds, otherwise false if the entity is already in the repo

    int search(std::string breed, std::string name);
    // this function searches for the entity which has the breed and the name given as the parameters
    // returns an integer, the position of that entity in the repo data (dyn vect) if it founds it, otherwise -1

    bool remove(std::string breed, std::string name);
    // this function removes an entity based on its breed and name and returns true if it succeeds; if the entity is not in the repo, returns false

    bool update(std::string breed, std::string name, Dog dog);
    // this function updates the data of an entity and returns true if it succeeds; if the entity is not in the repo, returns false

    int size() const;
    // this function returns the number of elements in the repository data

    bool isEmpty() const;
    // this function returns true if there are no entities in the repository, otherwise false

    DynamicVector<Dog> getData() {return this->data;}
    // this function returns a dynamic vector which contains all the data in the repository

    Dog get(int position);
    // this function returns the object located on the position "position" in the dynamic vector; it's basically the operator[] function
};