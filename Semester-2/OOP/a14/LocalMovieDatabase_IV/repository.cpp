//
// Created by TANIA on 3/19/2022.
//

#include <fstream>
#include "repository.h"
#include "exception.h"

Repository::Repository(std::string filename) {
    this->filename = filename;
    if(filename != "")
        this->readFromFile();
}

void Repository::add(Movie movie){
    int result = search(movie.getTitle(), movie.getGenre());
    if(result != -1)
        throw Exception("element already exists\n");
    this->data.push_back(movie);
    this->writeToFile();
}

void Repository::populateRepository(){
    Movie movie = Movie("The Book of Eli", "action", 2010, 59758, "https://www.youtube.com/watch?v=zSMHmtaoXtI");
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
    for(int i=0; i<this->data.size(); i++)
        if(this->data[i].getTitle() == title && this->data[i].getGenre() == genre)
            return i;
    return -1;
}

void Repository::update(std::string title, std::string genre, Movie new_movie){
    int pos = this->search(title, genre);
    if(pos == -1)
        throw Exception("element does not exist\n");
    this->data[pos] = new_movie;
    this->writeToFile();
}

void Repository::remove(std::string title, std::string genre) {
    int position = search(title, genre);
    if(position == -1)
        throw Exception("element does not exist\n");
    this->data.erase(this->data.begin()+position);
    this->writeToFile();
}

int Repository::size() const {
    return this->data.size();
}

bool Repository::isEmpty() const{
    return this->data.empty();
}

Movie Repository::get(int position){
    return this->data[position];
}

void Repository::readFromFile()
{
    std::ifstream file;
    file.open(this->filename);

    if (!file.is_open())
        throw Exception("The file could not be opened!");

    Movie m;
    while (file >> m)
        this->data.push_back(m);

    file.close();
}

void Repository::writeToFile()
{
    std::ofstream file;
    file.open(this->filename);
    if (!file.is_open())
        throw Exception("The file could not be opened!");

    for (auto m : this->data)
    {
        file << m;
    }

    file.close();
}

