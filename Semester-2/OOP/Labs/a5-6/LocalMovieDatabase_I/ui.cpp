//
// Created by TANIA on 3/19/2022.
//

#include "ui.h"
#include <cstring>

UI::UI() {
}

UI::~UI() {
}

int UI::read_integer(){
    std::string integer;
    getline(cin, integer);
    for (int i = 0; i<strlen(integer.c_str()); i++)
        if(!isdigit(integer.c_str()[i]))
            return -1;
    return atoi(integer.c_str());
}

void UI::print_admin_menu(){
    cout<<"1. add a new movie\n";
    cout<<"2. delete a movie\n";
    cout<<"3. update the information of a movie\n";
    cout<<"4. see all the movies in the database\n";
    cout<<"5. display all deleted movies\n";
    cout<<"6. exit\n";
}

void UI::print_user_menu(){
    cout<<"1. see the movies in the database having a given genre (if the genre is empty, see all the movies)\n";
    //cout<<"1.1. add the movie to the watch list";
    //cout<<"1.2. go to the next movie\n";
    //cout<<"1.3. exit this genre\n";
    cout<<"2. delete a movie from the watch list\n";
    //cout<<"2.1. rate the movie\n";
    //cout<<"2.2. don't rate the movie\n";
    cout<<"3. see the watch list\n";
    cout<<"4. exit\n";
}

bool UI::addUI(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) {
    Movie movie(title, genre, year_of_release, number_of_likes, trailer);
    return this->service.add(movie);
}

bool UI::removeUI(std::string title, std::string genre){
    return this->service.remove(title, genre);
}

bool UI::updateUI(std::string title, std::string genre, Movie movie){
    return this->service.update(title, genre, movie);
}

void UI::displayMovies(DynamicVector<Movie> v){
    for(int i=0; i<v.getSize(); i++) {
        Movie movie = v[i];
        cout<<movie.getTitle()<<" | "<<movie.getGenre()<<" | "<<movie.getYearRelease()<<" | "<<movie.getNumberLikes()<<" | "<<movie.getTrailer();
        cout << '\n';
    }
}

DynamicVector<Movie> create_list_of_given_genre(DynamicVector<Movie> v, std::string genre){
    DynamicVector<Movie> list_of_movies_of_given_genre;
    for(int i=0; i<v.getSize(); i++) {
        Movie movie = v[i];
        if(movie.getGenre() == genre || genre == " ")
            list_of_movies_of_given_genre.add(movie);
    }
    return list_of_movies_of_given_genre;
}

void UI::open_link(Movie movie){
//    ShellExecute(NULL,"open",movie.getTrailer().c_str(),NULL,NULL,SW_SHOWNORMAL);
//    ShellExecuteA(0, reinterpret_cast<LPCSTR>(L"open"), movie.getTrailer().c_str(), NULL, NULL, SW_SHOW);
    std::string Url = movie.getTrailer();
//    ShellExecuteW(0, L"open", reinterpret_cast<LPCWSTR>(Url.c_str()), NULL, NULL, SW_SHOWDEFAULT);
}


void UI::startUI() {
    cout << "\n------------Welcome to IMDB!------------\n\n";
    cout << "What are you?\n1.THE Boss\n2.Just a movie buff\n";
    int command, admin_command, user_command, user_smaller_command;
    bool result;
    Movie movie;
    DynamicVector<Movie> watch_list;
    DynamicVector<Movie> list_genre;
    DynamicVector<Movie> deleted_movies;
    std::string title, genre, trailer;
    int year_of_release, number_of_likes, position;
    command = read_integer();
    if (command == 1){
        cout << "Hello admin!";
        while (true) {
                cout << "What do you fancy doing?\n";
                print_admin_menu();
                admin_command = read_integer();
                if(admin_command==1) {
                    cout<< "Woohoo! you want to add a movie!\nPlease introduce the title, genre, year of release, number of likes and the link to the trailer: \n";
                    std::getline(cin, title);
                    std::getline(cin, genre);
                    year_of_release = read_integer();
                    if (year_of_release == -1)
                        cout<<"please introduce integers\n";
                    else {
                            number_of_likes = read_integer();
                            if(number_of_likes == -1)
                                cout<<"please introduce integers\n";
                            else {
                                std::getline(cin, trailer);
                                result = addUI(title, genre, year_of_release, number_of_likes, trailer);
                                if (result)
                                    cout << "Movie added!\n";
                                else
                                    cout << "Movie could not be added!\n";
                            }
                        }
                }
                else if(admin_command==2){
                    cout<<"Okay, you chose to delete a movie :( \nPlease introduce the title and the genre so we can find it: \n";
                    std::getline(cin,title);
                    std::getline(cin,genre);
                    position = this->service.search(title, genre);
                    if(position >=0 ) {
                        movie = this->service.get(position);
                        deleted_movies.add(movie);
                    }
                    result = removeUI(title, genre);
                    if(result)
                        cout<<"Movie removed!\n";
                    else
                        cout<<"Movie could not be removed!\n";
                }
                else if(admin_command==3) {
                    cout<< "Phew, you chose to update a movie. \nPlease introduce the title and the genre so we can find it: \n";
                    std::getline(cin, title);
                    std::getline(cin, genre);
                    position = this->service.search(title, genre);
                    if (position == -1) {
                        cout << "unfortunately, we were not able to find the movie\n";
                    } else {
                        cout << "Now introduce the updated data(year_of_release, number_of_likes and trailer): \n";
                        year_of_release = read_integer();
                        if (year_of_release == -1)
                            cout << "please introduce integers\n";
                        else {
                            number_of_likes = read_integer();
                            if (number_of_likes == -1)
                                cout << "please introduce integers\n";
                            else {
                                std::getline(cin, trailer);
                                movie = Movie(title, genre, year_of_release, number_of_likes, trailer);
                                result = updateUI(title, genre, movie);
                                if (result)
                                    cout << "Movie updated!\n";
                                else
                                    cout << "Movie could not be updated!\n";
                            }
                        }
                    }
                }
                else if(admin_command==4){
                    cout<<"Make yourself comfortable, you will now be displayed all the movies in the database: \n";
                    displayMovies(this->service.getRepoData());
                }
                else if(admin_command==5)
                    displayMovies(deleted_movies);
                else if(admin_command==6)
                    break;
                else
                    cout<<"please input a valid command\n";
        }
    }
    else
            if(command == 2) {
                cout << "Hello movie worm!";
                while (true) {
                    cout << "What is it that you truly desire?\n";
                    print_user_menu();
                    user_command = read_integer();
                    if(user_command==1){
                        getline(cin,genre);
                        if(this->service.isEmptyRepo()) {
                            cout<<"Repository is empty\n";
                            break;
                        }
                        int i=0;
                        list_genre = create_list_of_given_genre(this->service.getRepoData(), genre);
                        while(true) {
                            movie = list_genre[i];
                            cout<<movie.getTitle()<<" | "<<movie.getGenre()<<" | "<<movie.getYearRelease()<<" | "<<movie.getNumberLikes()<<" | "<<movie.getTrailer()<<'\n';
//                            this->open_link(movie);
                            cout << "1. add the movie to the watch list\n";
                            cout << "2. go to the next movie\n";
                            cout << "3. exit this genre\n";
                            user_smaller_command = read_integer();
                            if(user_smaller_command == 1){
                                result = true;
                                for(int m=0; m<watch_list.getSize(); m++)
                                    if(watch_list[m] == movie)
                                        result = false;
                                if(result){
                                    watch_list.add(movie);
                                    cout<<"Movie added to the watch list\n";
                                }
                                else
                                    cout<<"Movie was already in the watch list\n";
                            }
                            else if(user_smaller_command == 2){
                                i++;
                                if(i == list_genre.getSize())
                                    i=0;
                            }
                            else if(user_smaller_command == 3)
                                break;
                            else
                                cout<<"command not valid\n";
                        }

                    }
                    else if (user_command == 2) {
                        cout << "please introduce the title and the genre of the movie\n";
                        std::getline(cin,title);
                        std::getline(cin,genre);
                        int pos = -1;
                        for(int m=0; m<watch_list.getSize(); m++)
                            if(watch_list[m].getGenre() == genre && watch_list[m].getTitle() == title)
                                pos = m;
                        if(pos != -1){
                            watch_list.erase(pos);
                            cout<<"Movie removed from the watch list\n";
                            cout<<"Do you want to like the movie? 1.yes 2.no\n";
                            user_smaller_command = read_integer();
                            if(user_smaller_command == 1) {
                                pos = this->service.search(title, genre);
                                movie = this->service.get(pos);
                                Movie new_movie = movie;
                                new_movie.setNumberLikes(movie.getNumberLikes()+1);
                                this->updateUI(title, genre, new_movie);
                            }
                            else if(user_smaller_command == 2){
                                continue;
                            }
                            else
                                cout<<"command not valid\n";
                        }
                        else
                            cout<<"command not valid\n";
                    }
                    else if (user_command == 3){
                        if(watch_list.getSize() == 0)
                            cout<<"you dont have movies in your watch list\n";
                        else
                        for(int m=0; m<watch_list.getSize(); m++){
                            movie = watch_list[m];
                            cout<<movie.getTitle()<<" | "<<movie.getGenre()<<" | "<<movie.getYearRelease()<<" | "<<movie.getNumberLikes()<<" | "<<movie.getTrailer()<<'\n';
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


