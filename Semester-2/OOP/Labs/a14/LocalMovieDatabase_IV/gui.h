//
// Created by TANIA on 5/14/2022.
//

#pragma once
#include "QWidget"
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
#include <QTableView>
#include "exception.h"
#include "service.h"
#include "ui_TableViewWidget.h"
#include "MyModel.h"

class OptionWindow: public QWidget{
public:
    QHBoxLayout* horizontal_layout;
    QPushButton* admin_button;
    QPushButton* user_button;

    OptionWindow(){
        this->setWindowTitle("choose your fighter");
        horizontal_layout = new QHBoxLayout{};
        admin_button = new QPushButton("Boss");
        user_button = new QPushButton("Movie buff");
        horizontal_layout->addWidget(admin_button);
        horizontal_layout->addWidget(user_button);
        this->setLayout(horizontal_layout);
    };
    ~OptionWindow() {}
};

class AdminWindow: public QWidget{
public:
    QHBoxLayout* main_layout;
    QLineEdit* title_line_edit;
    QLineEdit* genre_line_edit;
    QLineEdit* year_of_release_line_edit;
    QLineEdit* number_of_likes_line_edit;
    QLineEdit* trailer_line_edit;
    QPushButton* add_button;
    QPushButton* delete_button;
    QPushButton* update_button;
    QPushButton* undo_button;
    QPushButton* redo_button;
    QListWidget* movies_list_widget;
    AdminWindow(){
        this->setWindowTitle("Hello admin");
        movies_list_widget = new QListWidget{};
        title_line_edit = new QLineEdit{};
        genre_line_edit = new QLineEdit{};
        year_of_release_line_edit = new QLineEdit{};
        number_of_likes_line_edit = new QLineEdit{};
        trailer_line_edit = new QLineEdit{};
        add_button = new QPushButton("Add");
        delete_button = new QPushButton("Delete");
        update_button = new QPushButton("Update");
        undo_button = new QPushButton("Undo");
        redo_button = new QPushButton("Redo");

        QGridLayout* grid_layout = new QGridLayout{};
        grid_layout->addWidget(add_button, 0, 0);
        grid_layout->addWidget(delete_button, 0, 1);
        grid_layout->addWidget(update_button, 0, 2);
        grid_layout->addWidget(undo_button, 1, 1);
        grid_layout->addWidget(redo_button, 1, 2);

        QFormLayout* form_layout = new QFormLayout{};
        form_layout->addRow("Title", title_line_edit);
        form_layout->addRow("Genre", genre_line_edit);
        form_layout->addRow("Year of release", year_of_release_line_edit);
        form_layout->addRow("Number of likes", number_of_likes_line_edit);
        form_layout->addRow("Trailer", trailer_line_edit);

        QVBoxLayout* vertical_layout = new QVBoxLayout{};
        vertical_layout->addLayout(form_layout);
        vertical_layout->addLayout(grid_layout);

        main_layout = new QHBoxLayout{};
        main_layout->addLayout(vertical_layout);
        main_layout->addWidget(movies_list_widget);
        this->setLayout(main_layout);
    };
    ~AdminWindow() {};
};

class UserWindow: public QWidget{
public:
    int counter;
    QHBoxLayout* main_layout;
    QListWidget* watchlist;
    std::vector<Movie> watchlist_vector;
    std::vector<Movie> filtered_movies_vector;
    std::vector<Movie> liked_movies;
    QListWidget* filtered_movies_list;
    QPushButton* filter_button;  //also used for see movies given genre in user routine
    QLineEdit* filter_line_edit;
    QPushButton* add_to_watchlist_button;
    QPushButton* remove_from_watchlist_button;
    QPushButton* CSV_button;
    QPushButton* HTML_button;
    QPushButton* like_button;
    QPushButton* next_button;
    MyModel* myModel;
    QTableView* tableView;
    UserWindow() {
        this->setWindowTitle("Hello user");
        counter = 0;
        main_layout = new QHBoxLayout{};
        filter_line_edit = new QLineEdit{};
        filter_button = new QPushButton("See movies given genre");
        add_to_watchlist_button = new QPushButton("Add to watchlist");
        remove_from_watchlist_button = new QPushButton("Remove from watchlist");
        CSV_button = new QPushButton("See watchlist CSV");
        HTML_button = new QPushButton("See watchlist HTML");
        like_button = new QPushButton("Like");
        next_button = new QPushButton("Next");

        QGridLayout* grid_layout = new QGridLayout{};
        grid_layout->addWidget(CSV_button, 0, 0);
        grid_layout->addWidget(HTML_button, 0, 1);
        grid_layout->addWidget(filter_line_edit, 1, 0);
        grid_layout->addWidget(filter_button, 1,1);
        grid_layout->addWidget(add_to_watchlist_button, 2, 0);
        grid_layout->addWidget(remove_from_watchlist_button, 2,1);
        grid_layout->addWidget(like_button, 3, 0);
        grid_layout->addWidget(next_button, 3, 1);

        filtered_movies_list = new QListWidget{};
        watchlist = new QListWidget{};
        main_layout->addLayout(grid_layout);
        main_layout->addWidget(filtered_movies_list);
        main_layout->addWidget(watchlist);

        this->setLayout(main_layout);

        tableView = new QTableView{};
        myModel = new MyModel(watchlist_vector);
        tableView->setModel(myModel);
    }
    ~UserWindow() {};
};

class GUI: public QWidget {
private:
    Service service;
    Repository repository;
    OptionWindow* option_window;
    AdminWindow* admin_window;
    UserWindow* user_window;
    std::vector<Movie> v;

    void connect_user_admin_option_window();

private slots:
    void open_admin(){
        init_admin_window();
        this->admin_window->show();
        this->option_window->close();
    }
    void open_user(){
        this->user_window->show();
        this->user_window->tableView->show();
        this->option_window->close();
    }


public:
    GUI(Service service, Repository repository): service(service), repository(repository) {
        option_window = new OptionWindow();
        admin_window = new AdminWindow();
        user_window = new UserWindow();
        v=this->repository.getData();

//        populate_movies_list();
    }
    void connect_signals_and_slots();
    void init_admin_window();
    void init_admin_fields();
    void init_filtered_movies();
    int get_selected_index();

    void add_admin_handler();
    void remove_admin_handler();
    void update_admin_handler();
    void see_watchlist_CSV_user_handler();
    void see_watchlist_HTML_user_handler();
    void next_movie();
    void like_movie();
    void add_to_watchlist_user_handler();
    void remove_from_watchlist_user_handler();
    void undo_admin_handler();
    void redo_admin_handler();
    void see_watchlist();
    void start();
    void oops_an_error_occurred();
    ~GUI() {};
};

