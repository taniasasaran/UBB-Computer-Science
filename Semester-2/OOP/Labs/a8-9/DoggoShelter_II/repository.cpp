#include <fstream>
#include "repository.h"
#include "exception.h"

Repository::Repository(std::string filename) {
    this->filename = filename;
    if(filename != "")
        this->readFromFile();
}

void Repository::add(Dog dog){
    int result = search(dog.getBreed(), dog.getName());
    if(result != -1)
        throw Exception("element already exists\n");
    this->data.push_back(dog);
    this->writeToFile();
}

int Repository::search(std::string breed, std::string name) {
    for(int i=this->data.size()-1; i>=0; i--)
        if(this->data[i].getName() == name && this->data[i].getBreed() == breed)
            return i;
    return -1;
}

void Repository::update(std::string breed, std::string name, Dog dog){
    int pos = this->search(breed, name);
    if(pos == -1)
        throw Exception("element does not exist\n");
    this->data[pos] = dog;
    this->writeToFile();
}

void Repository::remove(std::string breed, std::string name) {
    int position = search(breed, name);
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

Dog Repository::get(int position){
    return this->data[position];
}

void Repository::readFromFile()
{
    std::ifstream file;
    file.open(this->filename);

    if (!file.is_open())
        throw Exception("The file could not be opened!");

    Dog d;
    while (file >> d)
        this->data.push_back(d);

    file.close();
}

void Repository::writeToFile()
{
    std::ofstream file;
    file.open(this->filename);
    if (!file.is_open())
        throw Exception("The file could not be opened!");

    for (auto const &d : this->data)
    {
        file << d;
    }

    file.close();
}

