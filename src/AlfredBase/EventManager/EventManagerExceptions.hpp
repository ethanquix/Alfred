#pragma once

#include <exception>
#include <string>

class EventNameExist : public std::exception
{
    std::string message;
  public:
    EventNameExist(const std::string& msg)
            : message(std::string("Error Event with this name already exist: ") + msg)
    {}

    const char* what() const throw() override
    {
        return message.c_str();
    }

};

class EventDontExist : public std::exception
{
    std::string message;
public:
    EventDontExist(const std::string& msg)
        : message(std::string("Error this Event doesn't exist: ") + msg)
    {}

    const char* what() const throw() override
    {
        return message.c_str();
    }

};