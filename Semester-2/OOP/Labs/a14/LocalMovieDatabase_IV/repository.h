//
// Created by TANIA on 3/19/2022.
//

#pragma once

#include <vector>
#include "domain.h"

class Repository{
private:
    std::vector<Movie> data;
    std::string filename;
    void readFromFile();
    void writeToFile();

public:
    Repository(std::string filename="");     // this is the constructor of the repo; it associates a dynamic vector to the data in the repository
    Repository(const Repository& r) {this->data = r.data; this->filename = r.filename;}  // this is the copy constructor; it returns an object of type Repository
    ~Repository(){}// this is the destructor of the repository; the destructor of the dynamic vector is called automatically

    void add(Movie m);
    // this function gets a movie object as a parameter and tries to add it to the repository; if the movie is already in the repo, it raises an error

    int search(std::string title, std::string genre);
    // this function searches for the movie which has the title and the genre given as the parameters
    // returns an integer, the position of that movie in the repo data (dyn vect) if it founds it, otherwise -1

    void remove(std::string title, std::string genre);
    // this function removes a movie based on its title and genre; if the movie is not in the repo it raises an error

    void update(std::string title, std::string genre, Movie movie);
    // this function updates the data of a movie; if the movie is not in the repo, it raises an error

    int size() const;
    // this function returns the number of elements in the repository data

    bool isEmpty() const;
    // this function returns true if there are no movies in the repository, otherwise false

    void populateRepository();
    // this function adds 10 movies in the repository

    std::vector<Movie> getData() {return this->data;}
    // this function returns a dynamic vector which contains all the data in the repository

    Movie get(int position);
    // this function returns the movie located on the position "position" in the dynamic vector; it's basically overload to the operator[] function
};