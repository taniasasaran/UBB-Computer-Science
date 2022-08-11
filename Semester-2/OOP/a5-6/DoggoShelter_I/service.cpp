#include "service.h"

Service::Service()
{
    this->populateRepository();
}

void Service::populateRepository(){
    Dog dog = Dog("cocker", "Costel", 5, "https://www.cinemagia.ro/actori/costel-bojog-162316/poze/281994/#gallery");
    this->add(dog);
    dog = Dog("ciobanesc german", "Raya", 2, "https://ro.wikipedia.org/wiki/Ciobănesc_german#/media/Fișier:Deutscher_Schäferhund-_portrait.JPG");
    this->add(dog);
    dog = Dog("bulldog", "Emanuel", 3, "https://en.wikipedia.org/wiki/Bulldog#/media/File:Whitebulldog.jpg");
    this->add(dog);
    dog = Dog("Schindler's List", "history", 1993, "https://www.youtube.com/watch?v=mxphAlJID9U");
    this->add(dog);
    dog = Dog("Spirited Away", "anime", 2001, "https://www.youtube.com/watch?v=ByXuk9QqQkk");
    this->add(dog);
    dog = Dog("Interstellar", "adventure", 2014, "https://www.youtube.com/watch?v=zSWdZVtXT7E");
    this->add(dog);
    dog = Dog("Spider-Man: No Way Home", "action", 2021, "https://www.youtube.com/watch?v=JfVOs4VSpmA");
    this->add(dog);
    dog = Dog("Your Name", "anime", 2016, "https://www.youtube.com/watch?v=xU47nhruN-Q");
    this->add(dog);
    dog = Dog("Inside Out", "animation", 2015, "https://www.youtube.com/watch?v=yRUAzGQ3nSY");
    this->add(dog);
    dog = Dog("It's a Wonderful Life", "romantic", 1946, "https://www.youtube.com/watch?v=iLR3gZrU2Xo");
    this->add(dog);
}

bool Service::add(Dog dog){
    return this->repository.add(dog);
}

int Service::search(std::string breed, std::string name){
    return this->repository.search(breed, name);
}

bool Service::remove(std::string breed, std::string name){
    return this->repository.remove(breed, name);
}

bool Service::update(std::string breed, std::string name, Dog dog){
    return this->repository.update(breed, name, dog);
}

DynamicVector<Dog> Service::createListOfGivenBreed(std::string breed, int number){
    DynamicVector<Dog> youngDogsOfGivenBreed;
    for(int i=0; i<this->repository.size(); i++) {
        Dog dog = this->repository.get(i);
        if(dog.getAge() <= number && (dog.getBreed() == breed || breed == " "))
            youngDogsOfGivenBreed.add(dog);
    }
    return youngDogsOfGivenBreed;
}
