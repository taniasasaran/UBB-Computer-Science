//
// Created by TANIA on 3/19/2022.
//

#pragma once
#include "service.h"
#include "iostream"
using namespace std;

class UI{
private:
    Service service;
public:
    UI();
    ~UI();
    bool addUI(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) ;
    bool removeUI(std::string title, std::string genre);
    bool updateUI(std::string title, std::string genre, Movie movie);
    void displayMovies(DynamicVector<Movie> v);
    void startUI();
    int read_integer();
    void print_admin_menu();
    void print_user_menu();
    void open_link(Movie movie);
};
