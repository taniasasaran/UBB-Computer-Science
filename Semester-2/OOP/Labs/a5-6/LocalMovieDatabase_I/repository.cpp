//
// Created by TANIA on 3/19/2022.
//

#include "repository.h"

Repository::Repository() {
    this->data = DynamicVector<Movie>();
}

bool Repository::add(Movie movie){
    int result = search(movie.getTitle(), movie.getGenre());
    if(result != -1)
        return false;
    this->data.add(movie);
    return true;
}

void Repository::populateRepository(){
    Movie movie = Movie("The Book of Eli", "action", 2010, 599758, "https://www.youtube.com/watch?v=zSMHmtaoXtI");
    this->add(movie);
    movie = Movie("The Matrix Resurrections", "sci-fi", 2021, 356794, "https://www.youtube.com/watch?v=9ix7TUGVYIo");
    this->add(movie);
    movie = Movie("Titanic", "romantic", 2012, 1974152, "https://www.youtube.com/watch?v=kVrqfYjkTdQ");
    this->add(movie);
    movie = Movie("Schindler's List", "history", 1993, 264629, "https://www.youtube.com/watch?v=mxphAlJID9U");
    this->add(movie);
    movie = Movie("Spirited Away", "anime", 2001, 5679482, "https://www.youtube.com/watch?v=ByXuk9QqQkk");
    this->add(movie);
    movie = Movie("Interstellar", "adventure", 2014, 185183, "https://www.youtube.com/watch?v=zSWdZVtXT7E");
    this->add(movie);
    movie = Movie("Spider-Man: No Way Home", "action", 2021, 2554889, "https://www.youtube.com/watch?v=JfVOs4VSpmA");
    this->add(movie);
    movie = Movie("Your Name", "anime", 2016, 2482869, "https://www.youtube.com/watch?v=xU47nhruN-Q");
    this->add(movie);
    movie = Movie("Inside Out", "animation", 2015, 5786942, "https://www.youtube.com/watch?v=yRUAzGQ3nSY");
    this->add(movie);
    movie = Movie("It's a Wonderful Life", "romantic", 1946, 3691843, "https://www.youtube.com/watch?v=iLR3gZrU2Xo");
    this->add(movie);
}

int Repository::search(std::string title, std::string genre) {
    for(int i=this->data.getSize()-1; i>=0; i--)
        if(this->data[i].getTitle() == title && this->data[i].getGenre() == genre)
            return i;
    return -1;
}

bool Repository::update(std::string title, std::string genre, Movie new_movie){
    int pos = this->search(title, genre);
    if(pos == -1)
        return false;
    this->data[pos] = new_movie;
    return true;
}

bool Repository::remove(std::string title, std::string genre) {
    int position = search(title, genre);
    if(position == -1)
        return false;
    this->data.erase(position);
    return true;
}

int Repository::size() const {
    return this->data.getSize();
}

bool Repository::isEmpty() const{
    return this->data.getSize() == 0;
}

Movie Repository::get(int position){
    return this->data[position];
}


