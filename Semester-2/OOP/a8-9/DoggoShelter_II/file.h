#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "domain.h"
#include "exception.h"

class File{
private:
    std::vector<Dog> data;
public:
    std::vector<Dog> getData() {return data;}
    virtual Dog& operator[](int position) {return data[position];};

    virtual void add(Dog& element) {data.push_back(element);};

    virtual void remove(int position) {data.erase(data.begin() + position);};

    virtual int getSize() const { return data.size();};

    virtual void writeInFile() { throw Exception("implement it lol!"); }

    virtual ~File() {};
};


class FileCSV: public File{
public:
    void writeInFile() override{
        std::ofstream f("dogs.csv");	// will append data
        if (!f.is_open())
            return;
        for (auto m : getData()){
            f << m;
        }
        f.close();
    }
    FileCSV() {getData() = std::vector<Dog>();}
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
    void writeInFile() override {
        std::ofstream f("dogs.html");
        if (!f.is_open())
            return;
        std::string intro = "<!DOCTYPE html>  \n"
                            "<html>\n"
                            "<head>\n"
                            "    <title>DOG shelter</title> \n"
                            "</head> \n"
                            "<body>\n"
                            "<table border=\"1\"> \n"
                            "    <tr> \n"
                            "        <td>Breed</td>\n"
                            "        <td>Name</td>\n"
                            "        <td>Age</td>\n"
                            "        <td>Photo</td>\n"
                            "    </tr>\n";
        f << intro;
        for (auto m: getData()) {
            f << "    <tr>\n"
                 "        <td>" << m.getBreed() << "</td>\n"
                                                   "        <td>" << m.getName() << "</td>\n"
                                                                                     "        <td>"
              << m.getAge() << "</td>\n"
                                                                               "        <td><a href=\""
              << m.getPhotograph() << "\">Link</a></td>\n"
                                   "    </tr>\n";
        }
        std::string outro = "</table>\n"
                            "</body>\n"
                            "</html>";
        f << outro;
        f.close();
    }

    FileHTML() { getData() = std::vector<Dog>(); }

    FileHTML(FileHTML &f) : File(f) { getData() = f.getData(); };

    ~FileHTML() {};

    FileHTML &operator=(FileHTML f) {
        if (this == &f)
            return *this;
        getData() = f.getData();
        return *this;
    }
};