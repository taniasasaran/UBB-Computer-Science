//#include <winuser.h>
//#include <shellapi.h>
#include "ui.h"
#include "file.h"
using namespace std;


UI::UI(Service service) : service(service) {}

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


void UI::addUI(std::string breed, std::string name, int age, std::string photo) {
    Dog dog(breed, name, age, photo);
    this->service.add(dog);
}

void UI::removeUI(std::string breed, std::string name){
    this->service.remove(breed, name);
}

void UI::updateUI(std::string breed, std::string name, Dog dog){
    this->service.update(breed, name, dog);
}

void UI::displayDogs(std::vector<Dog> v){
    for(auto dog : v) {
        cout<<dog.toString();
        cout << '\n';
    }
}

void UI::openLink(Dog dog){
//    ShellExecute(NULL,"open",dog.getPhotograph().c_str(),NULL,NULL,SW_SHOWNORMAL);
//    ShellExecuteA(0, reinterpret_cast<LPCSTR>(L"open"), dog.getPhotograph().c_str(), NULL, NULL, SW_SHOW);
//    std::string Url = dog.getPhotograph();
//    ShellExecuteW(0, L"open", reinterpret_cast<LPCWSTR>(Url.c_str()), NULL, NULL, SW_SHOWDEFAULT);

//    ShellExecuteA(0, nullptr, "chrome.exe", dog.getPhotograph().c_str(), nullptr, SW_SHOWMAXIMIZED);

}

void UI::adminRoutine(){
    int admin_command;
    Validate validate;
    Dog dog;
    std::vector<Dog> adoptedDogs;
    std::string breed, name, photo;
    int age, position;
    while (true) {
        cout << "What do you fancy doing?\n";
        printAdminMenu();
        try {
            admin_command = readInteger();
            if (admin_command == 1) {
                cout<< "Woohoo! you want to add a dog!\nPlease introduce the breed, name, age, and the link to the photograph: \n";
                std::getline(cin, breed);
                std::getline(cin, name);
                try {
                    age = readInteger();
                    std::getline(cin, photo);
                    validate.checkLink(photo);
                    addUI(breed, name, age, photo);
                    cout << "Dog added!\n";
                }
                catch (std::string &s) {
                    cout << s;
                    cout << "Dog could not be added!\n";
                }
            } else if (admin_command == 2) {
                cout<< "Okay, you chose to delete a dog :( \nPlease introduce the title and the genre so we can find it: \n";
                cout<<"Okay, you chose to delete a dog :( \nPlease introduce the breed and the name so we can find it: \n";
                std::getline(cin, breed);
                std::getline(cin, name);
                position = this->service.search(breed, name);
                if(position >=0 ) {
                    dog = this->service.get(position);
                    adoptedDogs.push_back(dog);
                }
                try {
                    removeUI(breed, name);
                    cout << "Dog removed!\n";
                }
                catch (std::string &s) {
                    cout << s;
                    cout << "Dog could not be removed!\n";
                }
            } else if (admin_command == 3) {
                cout<< "Phew, you chose to update a dog. \nPlease introduce the breed and the name so we can find it: \n";
                std::getline(cin, breed);
                std::getline(cin, name);
                position = this->service.search(breed, name);
                if (position == -1) {
                    cout << "unfortunately, we were not able to find the dog\n";
                } else {
                    cout << "Now introduce the updated data(age and photograph): \n";
                    try {
                        age = readInteger();
                        std::getline(cin, photo);
                        validate.checkLink(photo);
                        dog = Dog(breed, name, age, photo);
                        updateUI(breed, name, dog);
                        cout << "Dog updated!\n";
                    }
                    catch (Exception &e) {
                        cout << e.what();
                        cout << "Dog could not be updated!\n";
                    }
                }
            } else if (admin_command == 4) {
                cout<<"Make yourself comfortable, you will now be displayed all the dogs in the database: \n";
                displayDogs(this->service.getRepoData());
            }
            else if(admin_command==5)
                displayDogs(adoptedDogs);
            else if(admin_command==6)
                break;
        }
        catch(Exception &e) {
            cout << e.what();
        }
    }
}

void UI::userRoutineCsv(FileCSV adoptionList){
    int user_command, user_smaller_command, number;
    bool result;
    Dog dog;
    std::vector<Dog> listYoungBreed;
    std::string breed, name, photo;
    while (true) {
        cout << "What is it that you truly desire?\n";
        printUserMenu();
        try {
            user_command = readInteger();
            if (user_command == 1) {
                if (this->service.isEmptyRepo()) {
                    cout << "Repository is empty\n";
                    break;
                }
                int i = 0;
                listYoungBreed = this->service.getRepoData();
                while (true) {
                    dog = listYoungBreed[i];
                    cout << dog.toString() << '\n';
                            this->openLink(dog);
                    cout << "1. add the dog to the adoption list\n";
                    cout << "2. go to the next dog\n";
                    cout << "3. exit\n";
                    try {
                        user_smaller_command = readInteger();
                        if (user_smaller_command == 1) {
                            result = true;
                            for (int j = 0; j < adoptionList.getSize(); j++)
                                if (adoptionList[j] == dog)
                                    result = false;
                            if (result) {
                                adoptionList.add(dog);
                                cout << "Dog added to the adoption list\n";
                            } else
                                cout << "Dog was already in the adoption list\n";
                        } else if (user_smaller_command == 2) {
                            i++;
                            if (i == listYoungBreed.size())
                                i = 0;
                        } else if (user_smaller_command == 3)
                            break;
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }

            } else if (user_command == 2) {
                if(this->service.isEmptyRepo()) {
                    cout<<"Repository is empty\n";
                    break;
                }
                cout << "please introduce the breed of the dog: \n";
                getline(cin, breed);
                number = readInteger();
                listYoungBreed = this->service.createListOfGivenBreed(breed, number);
                int i = 0;
                while (true) {
                    dog = listYoungBreed[i];
                    cout << dog.toString() << '\n';
                            this->openLink(dog);
                    cout << "1. add the dog to the adoption list\n";
                    cout << "2. go to the next dog\n";
                    cout << "3. exit\n";
                    try {
                        user_smaller_command = readInteger();
                        if (user_smaller_command == 1) {
                            result = true;
                            for (int j = 0; j < adoptionList.getSize(); j++)
                                if (adoptionList[j] == dog)
                                    result = false;
                            if (result) {
                                adoptionList.add(dog);
                                cout << "Dog added to the adoption list\n";
                            } else
                                cout << "Dog was already in the adoption list\n";
                        } else if (user_smaller_command == 2) {
                            i++;
                            if (i == listYoungBreed.size())
                                i = 0;
                        } else if (user_smaller_command == 3)
                            break;
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }
            } else if (user_command == 3) {
                if(adoptionList.getSize() == 0)
                    cout<<"you dont have dogs in your adoption list\n";
                else
                    for(auto dog: adoptionList.getData()){
                        cout << dog.toString() << '\n';
                    }
            } else if (user_command == 4) {
                adoptionList.writeInFile();
                std::string topicName = "dogs.csv";
                topicName = "notepad \"" + topicName + "\"";
                system(topicName.c_str());
                break;
            }
        }
        catch (Exception &e) {
            cout << e.what();
        }
    }
}

void UI::userRoutineHtml(FileHTML adoptionList){
    int user_command, user_smaller_command, number;
    bool result;
    Dog dog;
    std::vector<Dog> listYoungBreed;
    std::string breed, name, photo;
    while (true) {
        cout << "What is it that you truly desire?\n";
        printUserMenu();
        try {
            user_command = readInteger();
            if (user_command == 1) {
                if (this->service.isEmptyRepo()) {
                    cout << "Repository is empty\n";
                    break;
                }
                int i = 0;
                listYoungBreed = this->service.getRepoData();
                while (true) {
                    dog = listYoungBreed[i];
                    cout << dog.toString() << '\n';
//                            this->open_link(dog);
                    cout << "1. add the dog to the adoption list\n";
                    cout << "2. go to the next dog\n";
                    cout << "3. exit\n";
                    try {
                        user_smaller_command = readInteger();
                        if (user_smaller_command == 1) {
                            result = true;
                            for (int j = 0; j < adoptionList.getSize(); j++)
                                if (adoptionList[j] == dog)
                                    result = false;
                            if (result) {
                                adoptionList.add(dog);
                                cout << "Dog added to the adoption list\n";
                            } else
                                cout << "Dog was already in the adoption list\n";
                        } else if (user_smaller_command == 2) {
                            i++;
                            if (i == listYoungBreed.size())
                                i = 0;
                        } else if (user_smaller_command == 3)
                            break;
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }

            } else if (user_command == 2) {
                if(this->service.isEmptyRepo()) {
                    cout<<"Repository is empty\n";
                    break;
                }
                cout << "please introduce the breed of the dog: \n";
                getline(cin, breed);
                number = readInteger();
                listYoungBreed = this->service.createListOfGivenBreed(breed, number);
                int i = 0;
                while (true) {
                    dog = listYoungBreed[i];
                    cout << dog.toString() << '\n';
//                            this->open_link(dog);
                    cout << "1. add the dog to the adoption list\n";
                    cout << "2. go to the next dog\n";
                    cout << "3. exit\n";
                    try {
                        user_smaller_command = readInteger();
                        if (user_smaller_command == 1) {
                            result = true;
                            for (int j = 0; j < adoptionList.getSize(); j++)
                                if (adoptionList[j] == dog)
                                    result = false;
                            if (result) {
                                adoptionList.add(dog);
                                cout << "Dog added to the adoption list\n";
                            } else
                                cout << "Dog was already in the adoption list\n";
                        } else if (user_smaller_command == 2) {
                            i++;
                            if (i == listYoungBreed.size())
                                i = 0;
                        } else if (user_smaller_command == 3)
                            break;
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }
            } else if (user_command == 3) {
                if(adoptionList.getSize() == 0)
                    cout<<"you dont have dogs in your adoption list\n";
                else
                    for(auto dog: adoptionList.getData()){
                        cout << dog.toString() << '\n';
                    }
            } else if (user_command == 4) {
                adoptionList.writeInFile();
//                ShellExecuteA(0, nullptr, "chrome.exe", "file:///C:/Users/TANIA/CLionProjects/GitHub/a8-9-taniasasaran/cmake-build-debug/movies.html", nullptr, SW_SHOWMAXIMIZED);
                std::string topicName = "dogs.html";
                topicName = "notepad \"" + topicName + "\"";
                system(topicName.c_str());
                break;
            }
        }
        catch (Exception &e) {
            cout << e.what();
        }
    }
}

void UI::startUI() {
    cout << "\n------------Welcome to PetShelter!------------\n";
    cout << "          Keep calm and adopt a pet!   \n\n";
    cout << "What are you?\n1.THE Boss\n2.Just a dog person\n";
    int command;
    FileCSV adoptionListCSV;
    FileHTML adoptionListHtml;
    try {
        command = readInteger();
        if (command == 1) {
            cout << "Hello admin!";
            adminRoutine();
        } else if (command == 2) {
            cout << "Hello dog worm!\n";
            cout<<"But first, tell me... 1.HTML or 2.CSV ?\n";
            int file_command = readInteger();
            if(file_command==1 || file_command ==2) {
                if (file_command == 1)
                    userRoutineHtml(adoptionListHtml);
                if (file_command == 2) {
                    userRoutineCsv(adoptionListCSV);
                }
            }
        }
    }
    catch(Exception &e) {
        cout << e.what();
    }
}
