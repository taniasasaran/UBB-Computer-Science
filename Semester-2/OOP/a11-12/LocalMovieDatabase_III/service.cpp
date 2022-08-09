//
// Created by TANIA on 3/19/2022.
//

#include "service.h"

Service::Service(Repository repository) : repository(repository) {}

void Service::add(Movie movie){
    this->repository.add(movie);
}

int Service::search(std::string title, std::string genre){
    return this->repository.search(title, genre);
}

void Service::remove(std::string title, std::string genre){
    return this->repository.remove(title, genre);
}

void Service::update(std::string title, std::string genre, Movie movie){
    this->repository.update(title, genre, movie);
}


