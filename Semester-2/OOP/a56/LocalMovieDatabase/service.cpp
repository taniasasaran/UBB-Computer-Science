//
// Created by TANIA on 3/19/2022.
//

#include "service.h"

Service::Service()
{
    repository.populateRepository();
}

bool Service::add(Movie movie){
    return this->repository.add(movie);
}

int Service::search(std::string title, std::string genre){
    return this->repository.search(title, genre);
}

bool Service::remove(std::string title, std::string genre){
    return this->repository.remove(title, genre);
}

bool Service::update(std::string title, std::string genre, Movie movie){
    return this->repository.update(title, genre, movie);
}


