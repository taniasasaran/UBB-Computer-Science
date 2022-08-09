//
// Created by TANIA on 5/14/2022.
//

#include "gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <QFormLayout>
#include "qobject.h"
#include "exception.h"
#include "domain.h"
#include "file.h"


void GUI::connect_signals_and_slots(){
    QObject::connect(admin_window->movies_list_widget, &QListWidget::clicked, this, &GUI::init_admin_fields);
    QObject::connect(admin_window->add_button, &QPushButton::clicked, this, &GUI::add_admin_handler);
    QObject::connect(admin_window->delete_button, &QPushButton::clicked, this, &GUI::remove_admin_handler);
    QObject::connect(admin_window->update_button, &QPushButton::clicked, this, &GUI::update_admin_handler);

    QObject::connect(user_window->filter_button, &QPushButton::clicked, this, &GUI::init_filtered_movies);
    QObject::connect(user_window->next_button, &QPushButton::clicked, this, &GUI::next_movie);
    QObject::connect(user_window->like_button, &QPushButton::clicked, this, &GUI::like_movie);
    QObject::connect(user_window->add_to_watchlist_button, &QPushButton::clicked, this, &GUI::add_to_watchlist_user_handler);
    QObject::connect(user_window->remove_from_watchlist_button, &QPushButton::clicked, this, &GUI::remove_from_watchlist_user_handler);
    QObject::connect(user_window->CSV_button, &QPushButton::clicked, this, &GUI::see_watchlist_CSV_user_handler);
    QObject::connect(user_window->HTML_button, &QPushButton::clicked, this, &GUI::see_watchlist_HTML_user_handler);

}

void GUI::connect_user_admin_option_window(){
    QObject::connect(option_window->user_button, &QPushButton::clicked, this, &GUI::open_user);
    QObject::connect(option_window->admin_button, &QPushButton::clicked, this, &GUI::open_admin);
}

int GUI::get_selected_index() {
    auto indexes = admin_window->movies_list_widget->selectionModel()->currentIndex();
    return indexes.row();
}

void GUI::init_admin_window(){
    auto movies = service.getRepoData();
    admin_window->movies_list_widget->clear();
    for(auto & movie : movies)
        admin_window->movies_list_widget->addItem(QString::fromStdString(movie.to_str()));
}

void GUI::init_admin_fields() {
    int index = get_selected_index();
    auto movie = service.getRepoData()[index];
    admin_window->title_line_edit->setText(QString::fromStdString(movie.getTitle()));
    admin_window->genre_line_edit->setText(QString::fromStdString(movie.getGenre()));
    admin_window->year_of_release_line_edit->setText(QString::fromStdString(std::to_string(movie.getYearRelease())));
    admin_window->number_of_likes_line_edit->setText(QString::fromStdString(std::to_string(movie.getNumberLikes())));
    admin_window->trailer_line_edit->setText(QString::fromStdString(movie.getTrailer()));
}

void GUI::add_admin_handler() {
    Validate validate;
    auto title = admin_window->title_line_edit->text().toStdString();
    auto genre = admin_window->genre_line_edit->text().toStdString();
    auto year_of_release = admin_window->year_of_release_line_edit->text().toStdString();
    auto number_of_likes = admin_window->number_of_likes_line_edit->text().toStdString();
    auto trailer = admin_window->trailer_line_edit->text().toStdString();
    try {
        validate.check_link(trailer);
        validate.check_integer(number_of_likes);
        validate.check_year_greater_1000(year_of_release);
        Movie movie(title, genre, std::stoi(year_of_release), std::stoi(number_of_likes), trailer);
        for(auto m: this->service.getRepoData())
            if(m.getGenre() == genre && m.getTitle()==title) {
                oops_an_error_occurred();
                return;
            }
        this->service.add(movie);
        init_admin_window();
    } catch(std::exception){
        oops_an_error_occurred();
        return;
    }
}

void GUI::remove_admin_handler(){
    int index = get_selected_index();
    if(index == -1){
        oops_an_error_occurred();
        return;
    }
    bool ok=false;
    auto movie = service.getRepoData()[index];
    for(auto m: this->service.getRepoData())
        if(m.getGenre() == movie.getGenre() && m.getTitle()==movie.getTitle())
            ok=true;
    if(ok) {
        this->service.remove(movie.getTitle(), movie.getGenre());
        init_admin_window();
    }
    else
        oops_an_error_occurred();
}

void GUI::update_admin_handler() {
    Validate validate;
    int index = get_selected_index();
    if(index == -1){
        oops_an_error_occurred();
        return;
    }
    auto movie = service.getRepoData()[index];
    auto title = admin_window->title_line_edit->text().toStdString();
    auto genre = admin_window->genre_line_edit->text().toStdString();
    auto year_of_release = admin_window->year_of_release_line_edit->text().toStdString();
    auto number_of_likes = admin_window->number_of_likes_line_edit->text().toStdString();
    auto trailer = admin_window->trailer_line_edit->text().toStdString();
    validate.check_link(trailer);
    validate.check_integer(number_of_likes);
    validate.check_year_greater_1000(year_of_release);
    Movie movie_updated(title, genre, std::stoi(year_of_release), std::stoi(number_of_likes), trailer);
    bool ok=false;
    for(auto m: this->service.getRepoData())
        if(m.getGenre() == movie.getGenre() && m.getTitle()==movie.getTitle())
            ok=true;
    if(ok) {
        this->service.remove(movie.getTitle(), movie.getGenre());
        this->service.add(movie_updated);
        init_admin_window();
    }
    else
        oops_an_error_occurred();
}


void GUI::init_filtered_movies(){
    v = repository.getData();
    user_window->counter=0;
    if(user_window->filter_line_edit->text() == ""){
        oops_an_error_occurred();
        return;
    }
    auto genre = user_window->filter_line_edit->text().toStdString();
    user_window->filtered_movies_vector.clear();
    user_window->filtered_movies_list->clear();
    for(auto movie : v) {
        if(movie.getGenre() == genre || genre == " ")
            user_window->filtered_movies_vector.push_back(movie);
    }
    if(user_window->filtered_movies_vector.empty()){
        oops_an_error_occurred();
        return;
    }
    auto m = user_window->filtered_movies_vector[user_window->counter];
    user_window->filtered_movies_list->addItem(QString::fromStdString(m.to_str()));
}

void GUI::next_movie(){
    if(user_window->filtered_movies_vector.empty()){
        oops_an_error_occurred();
        return;
    }
    user_window->counter++;
    if(user_window->counter == user_window->filtered_movies_vector.size())
        user_window->counter=0;
    user_window->filtered_movies_list->clear();
    auto m = user_window->filtered_movies_vector[user_window->counter];
    user_window->filtered_movies_list->addItem(QString::fromStdString(m.to_str()));
}

void GUI::like_movie(){
    auto indexes = user_window->watchlist->selectionModel()->currentIndex();
    auto index = indexes.row();
    if(index == -1){
        oops_an_error_occurred();
        return;
    }
    Movie movie = user_window->watchlist_vector[index];
    for(Movie m: user_window->liked_movies)
        if(m == movie){
            oops_an_error_occurred();
            return;
        }
    Movie new_movie = movie;
    new_movie.setNumberLikes(movie.getNumberLikes() + 1);
    this->service.update(movie.getTitle(), movie.getGenre(), new_movie);
    user_window->watchlist_vector[index].setNumberLikes(movie.getNumberLikes() + 1);
    user_window->liked_movies.push_back(movie);
    see_watchlist();
}

void GUI::see_watchlist_CSV_user_handler(){
    FileCSV csv_watchlist;
    auto movies = user_window->watchlist_vector;
    user_window->watchlist->clear();
    for(auto & movie : movies)
        csv_watchlist.add(movie);
    csv_watchlist.writeMovies();
    std::string topicName = "movies.csv";
    topicName = "notepad \"" + topicName + "\"";
    system(topicName.c_str());
    see_watchlist();
}

void GUI::see_watchlist_HTML_user_handler(){
    FileHTML html_watchlist;
    auto movies = user_window->watchlist_vector;
    user_window->watchlist->clear();
    for(auto & movie : movies)
        html_watchlist.add(movie);
    html_watchlist.writeMovies();
//    ShellExecuteA(0, nullptr, "chrome.exe", "file:///C:/Users/TANIA/CLionProjects/GitHub/a11-12-taniasasaran/cmake-build-debug/movies.html", nullptr, SW_SHOWMAXIMIZED);
    std::string topicName = "movies.html";
    topicName = "notepad \"" + topicName + "\"";
    system(topicName.c_str());
    see_watchlist();
}

void GUI::see_watchlist(){
    user_window->watchlist->clear();
    for(Movie m: user_window->watchlist_vector)
        user_window->watchlist->addItem(QString::fromStdString(m.to_str()));
}

void GUI::oops_an_error_occurred(){
    QWidget* widget = new QWidget;
    QLabel* text = new QLabel( "bing bong, you're wrong" );
    QHBoxLayout* layout = new QHBoxLayout{};
    layout->addWidget(text);
    widget->setLayout(layout);
    widget->setStyleSheet("background-color: QLinearGradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(13, 50, 130, 255), stop:1 rgba(255, 255, 255, 255));");
    widget->show();
}

void GUI::add_to_watchlist_user_handler(){
    if(user_window->filtered_movies_vector.empty()){
        oops_an_error_occurred();
        return;
    }
    Movie movie = user_window->filtered_movies_vector[user_window->counter];
    int i=0;
    for(i=0; i<this->user_window->watchlist_vector.size(); i++)
        if(this->user_window->watchlist_vector[i].getTitle() == movie.getTitle() && this->user_window->watchlist_vector[i].getGenre() == movie.getGenre())
            break;
    if(i==this->user_window->watchlist_vector.size())
        user_window->watchlist_vector.push_back(movie);
    else
        oops_an_error_occurred();
    see_watchlist();
}

void GUI::remove_from_watchlist_user_handler(){
    auto indexes = user_window->watchlist->selectionModel()->currentIndex();
    auto index = indexes.row();
    if(index == -1){
        oops_an_error_occurred();
        return;
    }
    Movie movie = user_window->watchlist_vector[index];
    std::vector<Movie> f;
    for(Movie& m: user_window->watchlist_vector)
        if(!(m==movie))
            f.push_back(m);
    if(user_window->watchlist_vector.size() == f.size())
        oops_an_error_occurred();
    else
        user_window->watchlist_vector = f;
    see_watchlist();
}

void GUI::start() {
    option_window->show();
    connect_user_admin_option_window();
    connect_signals_and_slots();
}
