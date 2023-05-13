//
// Created by TANIA on 3/19/2022.
//

#include "domain.h"
#include "exception.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

Movie::Movie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer){
    this->year_of_release = year_of_release;
    this->number_of_likes = number_of_likes;
    this->title = title;
    this->genre = genre;
    this->trailer = trailer;
}

Movie::Movie(const Movie &m)
{
    this->year_of_release = m.year_of_release;
    this->number_of_likes = m.number_of_likes;
    this->title = m.title;
    this->genre = m.genre;
    this->trailer = m.trailer;
}

std::string Movie::getTitle(){
    return this->title;
}

std::string Movie::getGenre(){
    return this->genre;
}
int Movie::getYearRelease() const{
    return this->year_of_release;
}
int Movie::getNumberLikes() const{
    return this->number_of_likes;
}

void Movie::setNumberLikes(int number){
    this->number_of_likes = number;
}

void Movie::setYearRelease(int number){
    this->year_of_release = number;
}

void Movie::setTrailer(std::string link){
    this->trailer = link;
}

std::string Movie::getTrailer(){
    return this->trailer;
}

bool Movie::operator==(Movie &m) {
    bool result = true;
    if(this->title != m.title)
        result = false;
    if(this->genre != m.genre)
        result = false;
    return result;
}

//std::istream & operator>>(std::istream & is, Movie& m)
//{
//    // use reading with getline and then tokenisation if you want to validate the number of tokens
//    Validate validate;
//    if (is.eof())
//        is.setstate(std::ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
//    else
//    {
//        getline(is, m.title, ',');
//        getline(is, m.genre, ',');
//        std::string year, likes, trailer;
//        getline(is, year, ',');
//        getline(is, likes, ',');
//        validate.check_year_greater_1000(year);
//        validate.check_integer(likes);
//        getline(is, trailer, '\n');
//        validate.check_link(trailer);
//        m.setNumberLikes(atoi(likes.c_str()));
//        m.setYearRelease(atoi(year.c_str()));
//        m.setTrailer(trailer);
//    }
//    return is;
//}

std::ostream & operator<<(std::ostream & os, const Movie& m)
{
    os << m.title << "," << m.genre << "," << m.year_of_release << "," << m.number_of_likes << "," << m.trailer << "\n";
    return os;
}


std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream & operator>>(std::istream & is, Movie &m)
{
    std::string line;
    getline(is, line);
    Validate validate;
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 5) // make sure all the starship data was valid
        return is;
    m.title = tokens[0];
    m.genre = tokens[1];
    validate.check_year_greater_1000(tokens[2]);
    m.year_of_release = atoi(tokens[2].c_str());
    validate.check_integer(tokens[3]);
    m.number_of_likes = atoi(tokens[3].c_str());
    validate.check_link(tokens[4]);
    m.trailer = tokens[4];
    return is;
}


