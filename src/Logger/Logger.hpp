/*
** Logger.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Logger.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu May 04 03:26:19 2017 Dimitri Wyzlic
** Last update Thu May 04 03:26:19 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_LOGGER_HPP
#define ALFRED_LOGGER_HPP

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

#define LOG getLogger()

namespace Alfred
{
    class Logger
    {
    public:
        static Logger *getLogger()
        {
            static Logger *_curr = nullptr;

            if (_curr == nullptr)
                _curr = new Logger();
            return _curr;
        }

    private:
        const std::string getTime()
        {
            auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%X");
            return std::string("[" + ss.str() + "] ");
        }

    public:
        template <typename T>
        void log(T str)
        {
            std::string tmp;

            std::cout << getTime() << str << std::endl;
        }
    };

    inline Alfred::Logger *getLogger()
    {
        return Logger::getLogger();
    };
}

#endif //ALFRED_LOGGER_HPP
