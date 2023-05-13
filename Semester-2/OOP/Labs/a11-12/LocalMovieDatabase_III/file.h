//
// Created by TANIA on 4/17/2022.
//

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "domain.h"
#include "exception.h"

class File{
private:
    std::vector<Movie> data;
public:
    std::vector<Movie> getData() {return data;}
    virtual Movie& operator[](int position) {return data[position];};

    virtual void add(Movie& element) {data.push_back(element);};

    virtual void remove(int position) {data.erase(data.begin() + position);};

    virtual int get_size() const { return data.size();};

    virtual void writeMovies() { throw Exception("implement it lol!"); }

    virtual ~File() {};
};


class FileCSV: public File{
public:
    void writeMovies() override{
        std::ofstream f("movies.csv");	// will append data
        if (!f.is_open())
            return;
        for (auto m : getData()){
            f << m;
        }
        f.close();
    }
    FileCSV() {getData() = std::vector<Movie>();}
    FileCSV(FileCSV& f) : File(f) {getData() = f.getData();};
    ~FileCSV() {};
    FileCSV& operator=(FileCSV f){
        if (this == &f)
            return *this;
        getData() = f.getData();
        return *this;
    }
};

class FileHTML: public File {
public:
    void writeMovies() override {
        std::ofstream f("movies.html");
        if (!f.is_open())
            return;
        std::string intro = "<!DOCTYPE html>  \n"
                            "<html>\n"
                            "<head>\n"
                            "    <title>IMDB watchlist</title> \n"
                            "</head> \n"
                            "<body>\n"
                            "<table border=\"1\"> \n"
                            "    <tr> \n"
                            "        <td>Title</td>\n"
                            "        <td>Genre</td>\n"
                            "        <td>YearRelease</td>\n"
                            "        <td>NrLikes</td>\n"
                            "        <td>Trailer</td>\n"
                            "    </tr>\n";
        f << intro;
        for (auto m: getData()) {
            f << "    <tr>\n"
                 "        <td>" << m.getTitle() << "</td>\n"
                                                   "        <td>" << m.getGenre() << "</td>\n"
                                                                                     "        <td>"
              << m.getYearRelease() << "</td>\n"
                                       "        <td>" << m.getNumberLikes() << "</td>\n"
                                                                               "        <td><a href=\""
              << m.getTrailer() << "\">Link</a></td>\n"
                                   "    </tr>\n";
        }
        std::string outro = "</table>\n"
                            "</body>\n"
                            "</html>";
        f << outro;
        f.close();
    }

    FileHTML() { getData() = std::vector<Movie>(); }

    FileHTML(FileHTML &f) : File(f) { getData() = f.getData(); };

    ~FileHTML() {};

    FileHTML &operator=(FileHTML f) {
        if (this == &f)
            return *this;
        getData() = f.getData();
        return *this;
    }
};