#pragma once
#include <exception>
#include <iostream>
#include <string>
#include "cstring"

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
    bool checkInteger(std::string integer){
        for (int i = 0; i<strlen(integer.c_str()); i++)
            if(!isdigit(integer.c_str()[i]))
                throw Exception("please introduce integers\n");
        return true;
    }
    bool checkAgePositive(std::string year){
        int age_int=0;
        if (checkInteger(year)){
            age_int = atoi(year.c_str());
        }
        if(age_int >= 0)
            return true;
        throw Exception("please introduce year greater than 1000\n");
    }
    bool checkLink(std::string link){
        std::string link_begin = "https://";
        int length = link_begin.length();
        if (link.length() > length)
            if (link.substr(0, length) == link_begin)
                return true;
        throw Exception("please introduce valid links\n");
    }
};