#include "service.h"

Service::Service(Repository repository) : repository(repository) {}

void Service::add(Dog dog){
    this->repository.add(dog);
}

int Service::search(std::string breed, std::string name){
    return this->repository.search(breed, name);
}

void Service::remove(std::string breed, std::string name){
    return this->repository.remove(breed, name);
}

void Service::update(std::string breed, std::string name, Dog dog){
    return this->repository.update(breed, name, dog);
}

std::vector<Dog> Service::createListOfGivenBreed(std::string breed, int number){
    std::vector<Dog> youngDogsOfGivenBreed;
    for(auto dog: this->repository.getData()) {
        if(dog.getAge() <= number && (dog.getBreed() == breed || breed == " "))
            youngDogsOfGivenBreed.push_back(dog);
    }
    return youngDogsOfGivenBreed;
}
