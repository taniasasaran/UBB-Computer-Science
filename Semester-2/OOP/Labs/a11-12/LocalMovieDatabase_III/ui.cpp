//
// Created by TANIA on 3/19/2022.
//

#include "ui.h"
#include "file.h"
//#include <Windows.h>
//#include <shellapi.h>
using namespace std;


UI::UI(Service service) : service(service) {}

UI::~UI() {
}

int UI::read_integer(){
    Validate validate;
    std::string integer;
    getline(cin, integer);
    if (validate.check_integer(integer))
        return atoi(integer.c_str());
    return 0;
}

int UI::read_year(){
    Validate validate;
    std::string year;
    getline(cin, year);
    if (validate.check_year_greater_1000(year))
        return atoi(year.c_str());
    return 0;
}

void UI::print_admin_menu(){
    cout<<"1. add a new movie\n";
    cout<<"2. delete a movie\n";
    cout<<"3. update the information of a movie\n";
    cout<<"4. see all the movies in the database\n";
    cout<<"5. exit\n";
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

void UI::addUI(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) {
    Movie movie(title, genre, year_of_release, number_of_likes, trailer);
    this->service.add(movie);
}

void UI::removeUI(std::string title, std::string genre){
    this->service.remove(title, genre);
}

void UI::updateUI(std::string title, std::string genre, Movie movie){
    this->service.update(title, genre, movie);
}

void UI::displayMovies(std::vector<Movie> v){
    for(auto movie : v) {
        cout<<movie.getTitle()<<" | "<<movie.getGenre()<<" | "<<movie.getYearRelease()<<" | "<<movie.getNumberLikes()<<" | "<<movie.getTrailer();
        cout << '\n';
    }
}

std::vector<Movie> create_list_of_given_genre(std::vector<Movie> v, std::string genre){
    std::vector<Movie> list_of_movies_of_given_genre;
    for(auto movie : v) {
        if(movie.getGenre() == genre || genre == " ")
            list_of_movies_of_given_genre.push_back(movie);
    }
    return list_of_movies_of_given_genre;
}


void UI::open_link(Movie movie){
//    ShellExecute(NULL,"open",movie.getTrailer().c_str(),NULL,NULL,SW_SHOWNORMAL);
//    ShellExecuteA(0, reinterpret_cast<LPCSTR>(L"open"), movie.getTrailer().c_str(), NULL, NULL, SW_SHOW);
//    std::string Url = movie.getTrailer();
//    ShellExecuteW(0, L"open", reinterpret_cast<LPCWSTR>(Url.c_str()), NULL, NULL, SW_SHOWDEFAULT);

//    ShellExecuteA(0, nullptr, "chrome.exe", movie.getTrailer().c_str(), nullptr, SW_SHOWMAXIMIZED);

}

void UI::admin_routine(){
    int admin_command;
    Validate validate;
    Movie movie;
    std::vector<Movie> list_genre;
    std::string title, genre, trailer;
    int year_of_release, number_of_likes, position;
    while (true) {
        cout << "What do you fancy doing?\n";
        print_admin_menu();
        try {
            admin_command = read_integer();
            if (admin_command == 1) {
                cout<< "Woohoo! you want to add a movie!\nPlease introduce the title, genre, year of release, number of likes and the link to the trailer: ";
                std::getline(cin, title);
                std::getline(cin, genre);
                try {
                    year_of_release = read_year();
                    number_of_likes = read_integer();
                    std::getline(cin, trailer);
                    validate.check_link(trailer);
                    addUI(title, genre, year_of_release, number_of_likes, trailer);
                    cout << "Movie added!\n";
                }
                catch (std::string &s) {
                    cout << s;
                }
            } else if (admin_command == 2) {
                cout<< "Okay, you chose to delete a movie :( \nPlease introduce the title and the genre so we can find it: \n";
                std::getline(cin, title);
                std::getline(cin, genre);
                removeUI(title, genre);
                cout << "Movie removed!\n";
            } else if (admin_command == 3) {
                cout<< "Phew, you chose to update a movie. \nPlease introduce the title and the genre so we can find it: \n";
                std::getline(cin, title);
                std::getline(cin, genre);
                position = this->service.search(title, genre);
                if (position == -1) {
                    cout << "unfortunately, we were not able to find the movie\n";
                } else {
                    cout << "Now introduce the updated data(year_of_release, number_of_likes and trailer): \n";
                    try {
                        year_of_release = read_year();
                        number_of_likes = read_integer();
                        std::getline(cin, trailer);
                        validate.check_link(trailer);
                        movie = Movie(title, genre, year_of_release, number_of_likes, trailer);
                        updateUI(title, genre, movie);
                        cout << "Movie updated!\n";
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }
            } else if (admin_command == 4) {
                cout<< "Make yourself comfortable, you will now be displayed all the movies in the database: \n";
                displayMovies(this->service.getRepoData());
            } else if (admin_command == 5)
                break;
        }
        catch(Exception &e) {
            cout << e.what();
        }
    }
}

void UI::user_routine_csv(FileCSV watch_list){
    int user_command, user_smaller_command;
    bool result;
    Movie movie;
    std::vector<Movie> list_genre;
    std::string title, genre, trailer;
    while (true) {
        cout << "What is it that you truly desire?\n";
        print_user_menu();
        try {
            user_command = read_integer();
            if (user_command == 1) {
                getline(cin, genre);
                if (this->service.isEmptyRepo()) {
                    cout << "Repository is empty\n";
                    break;
                }
                int i = 0;
                list_genre = create_list_of_given_genre(this->service.getRepoData(), genre);
                while (true) {
                    movie = list_genre[i];
                    cout << movie.getTitle() << " | " << movie.getGenre() << " | " << movie.getYearRelease()
                         << " | " << movie.getNumberLikes() << " | " << movie.getTrailer() << '\n';
//                            this->open_link(movie);
                    cout << "1. add the movie to the watch list\n";
                    cout << "2. go to the next movie\n";
                    cout << "3. exit this genre\n";
                    try {
                        user_smaller_command = read_integer();
                        if (user_smaller_command == 1) {
                            result = true;
                            for (int j = 0; j < watch_list.get_size(); j++)
                                if (watch_list[j] == movie)
                                    result = false;
                            if (result) {
                                watch_list.add(movie);
                                cout << "Movie added to the watch list\n";
                            } else
                                cout << "Movie was already in the watch list\n";
                        } else if (user_smaller_command == 2) {
                            i++;
                            if (i == list_genre.size())
                                i = 0;
                        } else if (user_smaller_command == 3)
                            break;
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }

            } else if (user_command == 2) {
                cout << "please introduce the title and the genre of the movie\n";
                std::getline(cin, title);
                std::getline(cin, genre);
                int pos = -1;
                for (int i = 0; i < watch_list.get_size(); i++)
                    if (watch_list[i].getGenre() == genre && watch_list[i].getTitle() == title)
                        pos = this->service.search(title, genre);
                if (pos != -1) {
                    watch_list.remove(pos);
                    cout << "Movie removed from the watch list\n";
                    cout << "Do you want to like the movie? 1.yes 2.no\n";
                    try {
                        user_smaller_command = read_integer();
                        if (user_smaller_command == 1) {
                            pos = this->service.search(title, genre);
                            movie = this->service.get(pos);
                            Movie new_movie = movie;
                            new_movie.setNumberLikes(movie.getNumberLikes() + 1);
                            this->updateUI(title, genre, new_movie);
                        } else if (user_smaller_command == 2) {
                            continue;
                        }
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                } else
                    cout << "command not valid\n";
            } else if (user_command == 3) {
                if (watch_list.get_size() == 0)
                    cout << "you do not have movies in your watchlist\n";
                for (int i = 0; i < watch_list.get_size(); i++) {
                    movie = watch_list[i];
                    cout << movie.getTitle() << " | " << movie.getGenre() << " | " << movie.getYearRelease()
                         << " | " << movie.getNumberLikes() << " | " << movie.getTrailer() << '\n';
                }
            } else if (user_command == 4) {
                watch_list.writeMovies();
                std::string topicName = "movies.csv";
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

void UI::user_routine_html(FileHTML watch_list){
    int user_command, user_smaller_command;
    bool result;
    Movie movie;
    std::vector<Movie> list_genre;
    std::string title, genre, trailer;
    while (true) {
        cout << "What is it that you truly desire?\n";
        print_user_menu();
        try {
            user_command = read_integer();
            if (user_command == 1) {
                getline(cin, genre);
                if (this->service.isEmptyRepo()) {
                    cout << "Repository is empty\n";
                    break;
                }
                int i = 0;
                list_genre = create_list_of_given_genre(this->service.getRepoData(), genre);
                while (true) {
                    movie = list_genre[i];
                    cout << movie.getTitle() << " | " << movie.getGenre() << " | " << movie.getYearRelease()
                         << " | " << movie.getNumberLikes() << " | " << movie.getTrailer() << '\n';
//                            this->open_link(movie);
                    cout << "1. add the movie to the watch list\n";
                    cout << "2. go to the next movie\n";
                    cout << "3. exit this genre\n";
                    try {
                        user_smaller_command = read_integer();
                        if (user_smaller_command == 1) {
                            result = true;
                            for (int j = 0; j < watch_list.get_size(); j++)
                                if (watch_list[j] == movie)
                                    result = false;
                            if (result) {
                                watch_list.add(movie);
                                cout << "Movie added to the watch list\n";
                            } else
                                cout << "Movie was already in the watch list\n";
                        } else if (user_smaller_command == 2) {
                            i++;
                            if (i == list_genre.size())
                                i = 0;
                        } else if (user_smaller_command == 3)
                            break;
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                }

            } else if (user_command == 2) {
                cout << "please introduce the title and the genre of the movie\n";
                std::getline(cin, title);
                std::getline(cin, genre);
                int pos = -1;
                for (int i = 0; i < watch_list.get_size(); i++)
                    if (watch_list[i].getGenre() == genre && watch_list[i].getTitle() == title)
                        pos = this->service.search(title, genre);
                if (pos != -1) {
                    watch_list.remove(pos);
                    cout << "Movie removed from the watch list\n";
                    cout << "Do you want to like the movie? 1.yes 2.no\n";
                    try {
                        user_smaller_command = read_integer();
                        if (user_smaller_command == 1) {
                            pos = this->service.search(title, genre);
                            movie = this->service.get(pos);
                            Movie new_movie = movie;
                            new_movie.setNumberLikes(movie.getNumberLikes() + 1);
                            this->updateUI(title, genre, new_movie);
                        } else if (user_smaller_command == 2) {
                            continue;
                        }
                    }
                    catch (Exception &e) {
                        cout << e.what();
                    }
                } else
                    cout << "command not valid\n";
            } else if (user_command == 3) {
                if (watch_list.get_size() == 0)
                    cout << "you do not have movies in your watchlist\n";
                for (int i = 0; i < watch_list.get_size(); i++) {
                    movie = watch_list[i];
                    cout << movie.getTitle() << " | " << movie.getGenre() << " | " << movie.getYearRelease()
                         << " | " << movie.getNumberLikes() << " | " << movie.getTrailer() << '\n';
                }
            } else if (user_command == 4) {
                watch_list.writeMovies();
//                ShellExecuteA(0, nullptr, "chrome.exe", "file:///C:/Users/TANIA/CLionProjects/GitHub/a8-9-taniasasaran/cmake-build-debug/movies.html", nullptr, SW_SHOWMAXIMIZED);
                std::string topicName = "movies.html";
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
    cout << "\n------------Welcome to IMDB!------------\n\n";
    cout << "What are you?\n1.THE Boss\n2.Just a movie buff\n";
    int command;
    Movie movie;
    std::vector<Movie> list_genre;
    FileCSV watch_list_csv;
    FileHTML watch_list_html;
    std::string title, genre, trailer;
    try {
        command = read_integer();
        if (command == 1) {
            cout << "Hello admin!";
            admin_routine();
        } else if (command == 2) {
            cout << "Hello movie worm!\n";
            cout<<"But first, tell me... 1.HTML or 2.CSV ?\n";
            int file_command = read_integer();
            if(file_command==1 || file_command ==2) {
                if (file_command == 1)
                    user_routine_html(watch_list_html);
                if (file_command == 2) {
                    user_routine_csv(watch_list_csv);
                }
            }
        }
    }
    catch(Exception &e) {
        cout << e.what();
    }
}




