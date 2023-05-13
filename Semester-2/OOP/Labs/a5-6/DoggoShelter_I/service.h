#pragma once
#include "repository.h"

class Service{
private:
    Repository repository;
public:
    Service();  // this is the constructor of the service; it calls a function which populates the repository(adds 10 entities)
    Service(const Service& s) {this->repository = s.repository;}  // this is the copy constructor; it returns an object of type Service
    ~Service(){}  // this is the destructor of the service; the destructor of the repository is called automatically

    void populateRepository();
    // this function adds 10 entities in the repository; we know they are different so the output of the add function will always be true

    bool add(Dog dog);
    // this function gets an entity as a parameter, calls the add function from the repository and returns its result, true or false

    int search(std::string breed, std::string name);
    // this function calls the search function from the repository and returns its result, an integer, the movie's position or -1

    bool remove(std::string breed, std::string name);
    // this function gets a breed and a name as parameters, calls the remove function from the repository and returns its result, true or false

    bool update(std::string breed, std::string name, Dog dog);
    // this function calls the update function from the repository and returns its result, true or false

    int getRepoSize(){ return this->repository.size();}
    // this function calls the size function from the repo and returns its result: the number of elements in the repository data

    bool isEmptyRepo(){ return this->repository.isEmpty();}
    // this function calls the isEmpty function from the repo and returns its result: true if there are no movies in the repository, otherwise false

    Dog get(int position){ return this->repository.get(position);}
    // this function calls the get function from the repo and returns its result: the movie located on the position "position" in the dynamic vector

    DynamicVector<Dog> createListOfGivenBreed(std::string breed, int number);

    DynamicVector<Dog> getRepoData(){return this->repository.getData();}
    // this function calls the getData function from repo and returns its result: a dynamic vector which contains all the data in the repository
};
