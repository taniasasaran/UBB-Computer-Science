#include "domain.h"

Dog::Dog(std::string breed, std::string name, int age, std::string photograph){
    this->age = age;
    this->breed = breed;
    this->name = name;
    this->photograph = photograph;
}

Dog::Dog(const Dog &m)
{
    this->age = m.age;
    this->breed = m.breed;
    this->name = m.name;
    this->photograph = m.photograph;
}

std::string Dog::getBreed(){
    return this->breed;
}

std::string Dog::getName(){
    return this->name;
}

int Dog::getAge() const{
    return this->age;
}

std::string Dog::getPhotograph(){
    return this->photograph;
}

bool Dog::operator==(Dog &m) {
    bool result = true;
    if(this->breed != m.breed)
        result = false;
    if(this->name != m.name)
        result = false;
    return result;
}

std::string Dog::toString() {
    std::string str;
    str.append(this->breed);
    str.append(", ");
    str.append(this->name);
    str.append(", ");
    str.append(std::to_string(this->age));
    str.append(", ");
    str.append(this->photograph);
    return str;
}

std::ostream & operator<<(std::ostream & os, const Dog& m)
{
    os << m.breed << "," << m.name << "," << m.age << "," << m.photograph << "\n";
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

std::istream & operator>>(std::istream & is, Dog &d)
{
    std::string line;
    getline(is, line);
    Validate validate;
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 4)
        return is;
    d.breed = tokens[0];
    d.name = tokens[1];
    validate.checkAgePositive(tokens[2]);
    d.age = atoi(tokens[2].c_str());
    validate.checkLink(tokens[3]);
    d.photograph = tokens[3];
    return is;
}

