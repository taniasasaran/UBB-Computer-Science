//
// Created by TANIA on 3/19/2022.
//

#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>


class Movie {
private:
    std::string title;
    std::string genre;
    int year_of_release;
    int number_of_likes;
    std::string trailer;
public:
    Movie(std::string title="", std::string genre="", int year_of_release=1, int number_of_likes=0, std::string trailer="");
    // this function is the constructor of the movie object; it has some predefined values

    Movie(const Movie &m);
    // copy constructor of the class

    ~Movie() {};
    //destructor of the movie object

    bool operator==(Movie &m);
    // overloading of the == operator

    std::string getTitle();
    // a getter for the title represented on a std::string

    std::string getGenre();
    // a getter for the genre represented on a std::string

    int getYearRelease() const;
    // a getter for the year_of_release represented as an integer

    int getNumberLikes() const;
    // a getter for the year_of_release represented as an integer

    void setNumberLikes(int number);
    // a setter for the number_of_likes

    void setYearRelease(int number);

    void setTrailer(std::string link);


    std::string getTrailer();
    // a getter for the trailer represented on a std::string

    friend std::istream& operator>>(std::istream& is, Movie& m);
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};
