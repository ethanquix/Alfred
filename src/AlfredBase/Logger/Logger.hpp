#pragma once

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <map>
#include <cassert>
#include "AlfredBase/Utils/Singleton.hpp"

#pragma warning(disable:4996)

namespace Alfred
{
    class LoggerFatal : public std::exception
    {
        std::string msg;
    public:
        LoggerFatal(const std::string &msg) :
            msg(std::string("Fatal Error: ") + msg)
        {}

        virtual const char *what() const throw()
        { return msg.c_str(); }
    };

    class Logger : public Utils::Singleton<Logger>
    {
        //Var
    private:
        std::map<std::string, std::pair<std::clock_t, std::string>> _timers;

    public:
        enum level
        {
            LOG_DEBUG = 0,
            LOG_INFO,
            LOG_WARNING,
            LOG_ERROR,
            LOG_FATAL
        };

    private:
        std::string getTime()
        {
            auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%X");
            return std::string("[" + ss.str() + "] ");
        }

        template <typename T>
        constexpr void log_format(const std::string &begin, const std::string &color, T str)
        {
            std::cerr << color
                      << begin << getTime()
                      << str
                      << std::string("\033[0m") << std::endl;
            std::flush(std::cerr);
        }

    public:

        template <typename T>
        inline void log(T str)
        {
            std::cerr << "INFO - " << getTime() << str << std::endl;
            std::flush(std::cerr);
        }

        template <typename T>
        inline void info(T str)
        {
            std::cerr << "INFO - " << getTime() << str << std::endl;
            std::flush(std::cerr);
        }

        template <typename T>
        void log(level level, T str)
        {
            switch (level) {
#if DEBUG_MODE
                case LOG_DEBUG:
                    log_format("DEBUG - ", "\033[34m", str);
                    break;
#endif
                default:
		  break;
                case LOG_INFO:
                    log(str);
                    break;
                case LOG_WARNING:
                    log_format("WARNING - ", "\033[33m", str);
                    break;
                case LOG_ERROR:
                    log_format("ERROR - ", "\033[31m", str);
                    break;
                case LOG_FATAL:
                    log_format("FATAL - ", "\033[1;4;31m", str);
                    throw LoggerFatal(str);
                    break;
            }
        }

        template <typename T>
        void error(T str)
        {
            log_format("ERROR - ", "\033[31m", str);
        }

        template <typename T>
        void warning(T str)
        {
            log_format("WARNING - ", "\033[33m", str);
        }

        template <typename T>
        void debug(T str)
        {
#if DEBUG_MODE
            log_format("DEBUG - ", "\033[34m", str);
#endif
        }

        template <typename T>
        void fatal(T str)
        {
            log_format("FATAL - ", "\033[1;4;31m", str);
            throw LoggerFatal(str);
        }

        void timer_start(const std::string &name, const std::string &desc = "")
        {
            _timers[name].first = std::clock();
            _timers[name].second = desc;
        }

        double timer_fire(const std::string &name)
        {
            //This key don't exist
            assert(_timers.count(name) == 1);
            double elapsed = (double(std::clock() - _timers[name].first) / double(CLOCKS_PER_SEC));
            std::cerr << "TIMER - " << getTime() << name << "\t" << _timers[name].second << ": " << int(elapsed * 1000)
                      << "ms" << std::endl;
            std::flush(std::cerr);
            _timers.erase(name);
            return elapsed;
        }
    }; //Logger Class
} //Alfred Namespace

#define LOG Alfred::Logger::getSingleton()
