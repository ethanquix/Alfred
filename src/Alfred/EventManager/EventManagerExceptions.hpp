#pragma once

#include <exception>
#include <string>

class EventNameExist : public std::exception
{
    std::string message;
  public:
    EventNameExist(int msg)
            : message(std::string("Error Event with this name already exist: ") + std::to_string(msg))
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
    EventDontExist(int msg)
        : message(std::string("Error this Event doesn't exist: ") + std::to_string(msg))
    {}

    const char* what() const throw() override
    {
        return message.c_str();
    }

};