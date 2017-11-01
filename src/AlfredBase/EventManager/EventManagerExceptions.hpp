/*
** Exceptions.hpp for cpp_arcade in /home/wyzlic_a/delivery/cpp_arcade/Exceptions.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Fri Mar 17 03:28:06 2017 Dimitri Wyzlic
** Last update Fri Mar 17 03:28:06 2017 Dimitri Wyzlic
*/

#pragma once

#include <exception>
#include <string>

class EventNameExist : public std::exception
{
    std::string msg;
  public:
    EventNameExist(const std::string& msg)
            : msg(std::string("Error Event with this name already exist: ") + msg)
    {}

    const char* what() const throw() override
    {
        return msg.c_str();
    }

};

class EventDontExist : public std::exception
{
    std::string msg;
public:
    EventDontExist(const std::string& msg)
        : msg(std::string("Error this Event doesn't exist: ") + msg)
    {}

    const char* what() const throw() override
    {
        return msg.c_str();
    }

};