#include "ui.h"
#include <cstring>

UI::UI() {
}

UI::~UI() {
}

int UI::readInteger(){
    std::string integer;
    getline(cin, integer);
    for (int i = 0; i<strlen(integer.c_str()); i++)
        if(!isdigit(integer.c_str()[i]))
            return -1;
    return atoi(integer.c_str());
}

void UI::printAdminMenu(){
    cout<<"1. add a new dog\n";
    cout<<"2. delete a dog\n";
    cout<<"3. update the information of a dog\n";
    cout<<"4. see all the dogs in the database\n";
    cout<<"5. display all adopted dogs\n";
    cout<<"6. exit\n";
}

void UI::printUserMenu(){
    cout<<"1. See the dogs in the database\n";
    //cout<<"1.1. add the dog to the adoption list";
    //cout<<"1.2. go to the next dog\n";
    //cout<<"1.3. exit\n";
    cout<<"2. See all the dogs of a given breed, having an age less than a given number. If no breed is provided, then all the dogs will be considered.\n";
    //cout<<"2.1. add the dog to the adoption list";
    //cout<<"2.2. go to the next dog\n";
    //cout<<"2.3. exit\n";
    cout<<"3. See the adoption list\n";
    cout<<"4. exit\n";
}

bool UI::addUI(std::string breed, std::string name, int age, std::string photo) {
    Dog dog(breed, name, age, photo);
    return this->service.add(dog);
}

bool UI::removeUI(std::string breed, std::string name){
    return this->service.remove(breed, name);
}

bool UI::updateUI(std::string breed, std::string name, Dog movie){
    return this->service.update(breed, name, movie);
}

void UI::displayDogs(DynamicVector<Dog> v){
    for(int i=0; i<v.getSize(); i++) {
        Dog dog = v[i];
        cout << dog.toString();
        cout << '\n';
    }
}

void UI::openLink(Dog dog){
//    ShellExecute(NULL,"open",movie.getTrailer().c_str(),NULL,NULL,SW_SHOWNORMAL);
//    ShellExecuteA(0, reinterpret_cast<LPCSTR>(L"open"), movie.getTrailer().c_str(), NULL, NULL, SW_SHOW);
    std::string Url = dog.getPhotograph();
//    ShellExecuteW(0, L"open", reinterpret_cast<LPCWSTR>(Url.c_str()), NULL, NULL, SW_SHOWDEFAULT);
}


void UI::startUI() {
    cout << "\n------------Welcome to PetShelter!------------\n";
    cout << "          Keep calm and adopt a pet!   \n\n";
    cout << "What are you?\n1.THE Boss\n2.Just a dog person\n";
    int command, admin_command, user_command, user_smaller_command;
    bool result;
    Dog dog;
    DynamicVector<Dog> adoptionList;
    DynamicVector<Dog> youngDogsSpecificBreed;
    DynamicVector<Dog> adoptedDogs;
    std::string breed, name, photo;
    int age, number, position;
    command = readInteger();
    if (command == 1){
        cout << "Hello admin!";
        while (true) {
                cout << "What do you fancy doing?\n";
            printAdminMenu();
                admin_command = readInteger();
                if(admin_command==1) {
                    cout<< "Woohoo! you want to add a dog!\nPlease introduce the breed, name, age, and the link to the photograph: \n";
                    std::getline(cin, breed);
                    std::getline(cin, name);
                    age = readInteger();
                    if (age == -1)
                        cout<<"please introduce integers\n";
                    else {
                            std::getline(cin, photo);
                            result = addUI(breed, name, age, photo);
                            if (result)
                                cout << "Dog added!\n";
                            else
                                cout << "Dog could not be added!\n";
                        }
                }
                else if(admin_command==2){
                    cout<<"Okay, you chose to delete a dog :( \nPlease introduce the breed and the name so we can find it: \n";
                    std::getline(cin, breed);
                    std::getline(cin, name);
                    position = this->service.search(breed, name);
                    if(position >=0 ) {
                        dog = this->service.get(position);
                        adoptedDogs.add(dog);
                    }
                    result = removeUI(breed, name);
                    if(result)
                        cout<<"Dog removed!\n";
                    else
                        cout<<"Dog could not be removed!\n";
                }
                else if(admin_command==3) {
                    cout<< "Phew, you chose to update a dog. \nPlease introduce the breed and the name so we can find it: \n";
                    std::getline(cin, breed);
                    std::getline(cin, name);
                    position = this->service.search(breed, name);
                    if (position == -1) {
                        cout << "unfortunately, we were not able to find the dog\n";
                    } else {
                        cout << "Now introduce the updated data(age and photograph): \n";
                        age = readInteger();
                        if (age == -1)
                            cout << "please introduce integers\n";
                        else {
                            std::getline(cin, photo);
                            dog = Dog(breed, name, age, photo);
                            result = updateUI(breed, name, dog);
                            if (result)
                                cout << "Dog updated!\n";
                            else
                                cout << "Dog could not be updated!\n";
                            }
                    }
                }
                else if(admin_command==4){
                    cout<<"Make yourself comfortable, you will now be displayed all the dogs in the database: \n";
                    displayDogs(this->service.getRepoData());
                }
                else if(admin_command==5)
                    displayDogs(adoptedDogs);
                else if(admin_command==6)
                    break;
                else
                    cout<<"please input a valid command\n";
        }
    }
    else
            if(command == 2) {
                cout << "Hello dog fan!";
                while (true) {
                    cout << "What is it that you truly desire?\n";
                    printUserMenu();
                    user_command = readInteger();
                    if(user_command == 1){
                        if(this->service.isEmptyRepo()) {
                            cout<<"Repository is empty\n";
                            break;
                        }
                        int i=0;
                        youngDogsSpecificBreed = this->service.getRepoData();
                        while(true) {
                            dog = youngDogsSpecificBreed[i];
                            cout << dog.toString() << '\n';
//                            this->openLink(dog);
                            cout << "1. add the dog to the adoption list\n";
                            cout << "2. go to the next dog\n";
                            cout << "3. exit\n";
                            user_smaller_command = readInteger();
                            if(user_smaller_command == 1){
                                result = true;
                                for(int m=0; m < adoptionList.getSize(); m++)
                                    if(adoptionList[m] == dog)
                                        result = false;
                                if(result){
                                    adoptionList.add(dog);
                                    cout<<"Dog added to the adoption list\n";
                                }
                                else
                                    cout<<"Dog was already in the adoption list\n";
                            }
                            else if(user_smaller_command == 2){
                                i++;
                                if(i == youngDogsSpecificBreed.getSize())
                                    i=0;
                            }
                            else if(user_smaller_command == 3)
                                break;
                            else
                                cout<<"command not valid\n";
                        }
                    }
                    else if(user_command==2){
                        getline(cin, breed);
                        if(this->service.isEmptyRepo()) {
                            cout<<"Repository is empty\n";
                            break;
                        }
                        int i=0;
                        cout << "dogs younger than how many years? age=";
                        number = readInteger();
                        youngDogsSpecificBreed = this->service.createListOfGivenBreed(breed, number);
                        while(true) {
                            dog = youngDogsSpecificBreed[i];
                            cout << dog.toString() << '\n';
//                            this->openLink(dog);
                            cout << "1. add the dog to the adoption list\n";
                            cout << "2. go to the next dog\n";
                            cout << "3. exit this breed\n";
                            user_smaller_command = readInteger();
                            if (user_smaller_command == 1) {
                                result = true;
                                for (int m = 0; m < adoptionList.getSize(); m++)
                                    if (adoptionList[m] == dog)
                                        result = false;
                                if (result) {
                                    adoptionList.add(dog);
                                    cout << "Dog added to the adoption list\n";
                                } else
                                    cout << "Dog was already in the adoption list\n";
                            } else if (user_smaller_command == 2) {
                                i++;
                                if (i == youngDogsSpecificBreed.getSize())
                                    i = 0;
                            } else if (user_smaller_command == 3)
                                break;
                            else
                                cout << "command not valid\n";
                        }
                    }
                    else if (user_command == 3){
                        if(adoptionList.getSize() == 0)
                            cout<<"you dont have dogs in your adoption list\n";
                        else
                        for(int m=0; m < adoptionList.getSize(); m++){
                            dog = adoptionList[m];
                            cout << dog.toString() << '\n';
                        }
                    }
                    else if (user_command == 4)
                        break;
                    else
                        cout<<"command not valid\n";
                }
            }
            else
                cout<<"Please choose 1 or 2, we do not accept outsiders\n";
    }


