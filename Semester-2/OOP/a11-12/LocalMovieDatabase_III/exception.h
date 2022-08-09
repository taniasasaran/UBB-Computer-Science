#pragma once
#include <exception>
#include <iostream>
#include <string>

class Exception : public std::exception
{
    std::string message;
public:
    Exception(const std::string& msg) : message(msg){}

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }
};


class Validate{
public:
    bool check_integer(std::string integer){
        for (int i = 0; i<strlen(integer.c_str()); i++)
            if(!isdigit(integer.c_str()[i]))
                throw Exception("please introduce integers\n");
        return true;
    }
    bool check_year_greater_1000(std::string year){
        int year_int=0;
        if (check_integer(year)){
            year_int = atoi(year.c_str());
        }
        if(year_int>=1000)
            return true;
        throw Exception("please introduce year greater than 1000\n");
    }
    bool check_link(std::string link){
        std::string link_begin = "https://";
        int length = link_begin.length();
        if (link.length() > length)
            if (link.substr(0, length) == link_begin)
                return true;
        throw Exception("please introduce valid links\n");
    }
};