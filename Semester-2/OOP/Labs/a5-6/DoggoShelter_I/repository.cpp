#include "repository.h"

Repository::Repository() {
    this->data = DynamicVector<Dog>();
}

bool Repository::add(Dog dog){
    int result = search(dog.getBreed(), dog.getName());
    if(result != -1)
        return false;
    this->data.add(dog);
    return true;
}

int Repository::search(std::string breed, std::string name) {
    for(int i=this->data.getSize()-1; i>=0; i--)
        if(this->data[i].getName() == name && this->data[i].getBreed() == breed)
            return i;
    return -1;
}

bool Repository::update(std::string breed, std::string name, Dog dog){
    int pos = this->search(breed, name);
    if(pos == -1)
        return false;
    this->data[pos] = dog;
    return true;
}

bool Repository::remove(std::string breed, std::string name) {
    int position = search(breed, name);
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

Dog Repository::get(int position){
    return this->data[position];
}


