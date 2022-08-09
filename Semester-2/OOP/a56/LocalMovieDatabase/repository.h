//
// Created by TANIA on 3/19/2022.
//

#pragma once

#include "domain.h"
#include "Dynamic_Vector.h"

class Repository{
private:
    DynamicVector<Movie> data;

public:
    Repository();     // this is the constructor of the repo; it associates a dynamic vector to the data in the repository
    Repository(const Repository& r) {this->data = r.data;}  // this is the copy constructor; it returns an object of type Repository
    ~Repository(){}   // this is the destructor of the repository; the destructor of the dynamic vector is called automatically

    bool add(Movie m);
    // this function gets a movie object as a parameter and tries to add it to the repository
    // returns true if it succeeds, otherwise false if the movie is already in the repo

    int search(std::string title, std::string genre);
    // this function searches for the movie which has the title and the genre given as the parameters
    // returns an integer, the position of that movie in the repo data (dyn vect) if it founds it, otherwise -1

    bool remove(std::string title, std::string genre);
    // this function removes a movie based on its title and genre and returns true if it succeeds; if the movie is not in the repo, returns false

    bool update(std::string title, std::string genre, Movie movie);
    // this function updates the data of a movie and returns true if it succeeds; if the movie is not in the repo, returns false

    int size() const;
    // this function returns the number of elements in the repository data

    bool isEmpty() const;
    // this function returns true if there are no movies in the repository, otherwise false

    void populateRepository();
    // this function adds 10 movies in the repository; we know they are different so the output of the add function will always be true

    DynamicVector<Movie> getData() {return this->data;}
    // this function returns a dynamic vector which contains all the data in the repository

    Movie get(int position);
    // this function returns the movie located on the position "position" in the dynamic vector; it's basically the operator[] function
};