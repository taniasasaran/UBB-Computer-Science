#include "domain.h"
#include <cstring>
#include <exception>
#include <string>

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

