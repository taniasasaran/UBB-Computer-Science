//
// Created by TANIA on 3/19/2022.
//

#pragma once
#include "service.h"
#include "iostream"
#include "file.h"

class UI{
private:
    Service service;
public:
    UI(Service service);
    ~UI();
    void addUI(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer) ;
    void removeUI(std::string title, std::string genre);
    void updateUI(std::string title, std::string genre, Movie movie);
    void displayMovies(std::vector<Movie> v);
    void startUI();
    int read_integer();
    int read_year();
    void print_admin_menu();
    void print_user_menu();
    void user_routine_csv(FileCSV watch_list);
    void user_routine_html(FileHTML watch_list);
    void admin_routine();
    void open_link(Movie movie);
};
