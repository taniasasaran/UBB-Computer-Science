//
// Created by TANIA on 3/19/2022.
//

#pragma once
#include "repository.h"

class Service{
private:
    Repository repository;
public:
    Service();  // this is the constructor of the service; it calls a function which populates the repository(adds 10 entities)
    Service(const Service& s) {this->repository = s.repository;}  // this is the copy constructor; it returns an object of type Service
    ~Service(){}  // this is the destructor of the service; the destructor of the repository is called automatically
    bool add(Movie movie);
    // this function gets a movie as a parameter, calls the add function from the repository and returns its result, true or false

    int search(std::string title, std::string genre);
    // this function calls the search function from the repository and returns its result, an integer, the movie's position or -1

    bool remove(std::string title, std::string genre);
    // this function gets a title and a genre as parameters, calls the remove function from the repository and returns its result, true or false

    bool update(std::string title, std::string genre, Movie movie);
    // this function calls the update function from the repository and returns its result, true or false

    int getRepoSize(){ return this->repository.size();}
    // this function calls the size function from the repo and returns its result: the number of elements in the repository data

    bool isEmptyRepo(){ return this->repository.isEmpty();}
    // this function calls the isEmpty function from the repo and returns its result: true if there are no movies in the repository, otherwise false

    Movie get(int position){ return this->repository.get(position);}
    // this function calls the get function from the repo and returns its result: the movie located on the position "position" in the dynamic vector

    DynamicVector<Movie> getRepoData(){return this->repository.getData();}
    // this function calls the getData function from repo and returns its result: a dynamic vector which contains all the data in the repository
};
