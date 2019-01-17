#pragma once

#include <string>
#include <future>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Alfred/Utils/Singleton.hpp"

static constexpr bool ENABLE_LOGGER = true;
static constexpr bool DEBUG = true;

enum __CONSOLE_LOG_ENUM
{
    CONSOLE_LOG = 0,
};

#define LOG_SET_CONSOLE Alfred::Logger::get().setOutput(CONSOLE_LOG)
#define LOG_SET_FILE(path) Alfred::Logger::get().setOutput(path)
#define LOG_SET_FORMAT(format) Alfred::Logger::get().setTimeFormat(format)
#define LOG_ENABLE_DEBUG Alfred::Logger::get().setDebug(true)
#define LOG_DISABLE_DEBUG Alfred::Logger::get().setDebug(false)
#define LOG_DEBUG Alfred::Logger::get().debug(__FUNCTION__, __FILE__, __LINE__)
#define LOG_SUCCESS Alfred::Logger::get().success(__FUNCTION__, __FILE__, __LINE__)
#define LOG_INFO Alfred::Logger::get().info(__FUNCTION__, __FILE__, __LINE__)
#define LOG_WARNING Alfred::Logger::get().warning(__FUNCTION__, __FILE__, __LINE__)
#define LOG_ERROR Alfred::Logger::get().error(__FUNCTION__, __FILE__, __LINE__)
#define LOG_FATAL Alfred::Logger::get().fatal(__FUNCTION__, __FILE__, __LINE__)
//#define LOG_ENDL Logger::get().end()
#define LOG_ENDL Alfred::Logger::get().log_endl()

static constexpr char DEFAULT_LOG_FILENAME[] = "log_default.log";
static constexpr char DEFAULT_LOG_TIME_FORMAT[] = "%Hh%M:%S";

class NullBuffer : public std::streambuf
{
public:
    int overflow(int c)
    { return c; }
};

namespace Alfred
{
    class LoggerFatal: public std::exception
    {
        std::string message;
    public:
        LoggerFatal(const std::string& msg)
            : message(msg)
        {}

        const char* what() const throw() override
        {
            return message.c_str();
        }

    };

    class Logger : public Utils::Singleton<Logger>
    {
    private:
        bool _is_fatal = false;
        std::ostream *_stream;
        std::ostream _nullStream;
        std::ostream *_coutStream;
        std::string _fileName;
        NullBuffer null_buffer;
        std::string _dateFormat = DEFAULT_LOG_TIME_FORMAT;
        bool _isDebug = DEBUG;
        bool _is_prev_debug = false;

    private:

        const std::string getTime()
        {
            if (!ENABLE_LOGGER) {
                return "";
            }
            auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

            std::stringstream ss;

            ss << std::put_time(std::localtime(&in_time_t), _dateFormat.c_str());

            return ss.str();
        }

    public:

        std::string log_endl()
        {
            if (_is_prev_debug && !_isDebug) {
                _is_prev_debug = false;
                return "";
            }

            _is_prev_debug = false;

            *_stream << "\033[0m\n" << std::flush;

            if (_is_fatal)
                throw LoggerFatal("LOG_FATAL Called");

            return "";
        }

        Logger(const Logger &) = delete;
        auto operator=(const Logger &) = delete;

        Logger() :
            _stream((new std::ofstream(DEFAULT_LOG_FILENAME, std::ios_base::out | std::ios_base::trunc))),
            _nullStream(&null_buffer),
            _coutStream(&std::cout),
            _fileName(DEFAULT_LOG_FILENAME),
            null_buffer()
        {
            if (!ENABLE_LOGGER) {
                _stream->setstate(std::ios_base::badbit);
            }
        }

        explicit Logger(const std::string &fileName) :
            _stream((new std::ofstream(fileName.c_str(), std::ios::trunc))),
            _nullStream(&null_buffer),
            _coutStream(&std::cout),
            _fileName(fileName),
            null_buffer()
        {
            if (!ENABLE_LOGGER) {
                _stream->setstate(std::ios_base::badbit);
            }
        }

        explicit Logger(const __CONSOLE_LOG_ENUM console) :
            _stream(&std::cout),
            _nullStream(&null_buffer),
            _coutStream(&std::cout),
            _fileName("console output"),
            null_buffer()
        {
            if (!ENABLE_LOGGER) {
                _stream->setstate(std::ios_base::badbit);
            }
            (void)console;
        }

        virtual ~Logger()
        {
        }

        void setTimeFormat(const std::string &format)
        {
            _dateFormat = format;
        }

        void setOutput(const __CONSOLE_LOG_ENUM console)
        {
            (void)console;
            _fileName = "console output";
            _stream = _coutStream;
        }

        void setOutput(const std::string &filename)
        {
            _fileName = filename;
            _stream = new std::ofstream(filename.c_str(), std::ios::trunc);
        }

        void setOutput()
        {
            _fileName = DEFAULT_LOG_FILENAME;
            _stream = new std::ofstream(DEFAULT_LOG_FILENAME, std::ios::trunc);
        }

        void setDebug(bool src)
        {
            _isDebug = src;
        }

        std::ostream &debug(const std::string &funcName, const std::string &file, int line)
        {
            _is_prev_debug = true;

            if (!ENABLE_LOGGER) {
                return *_stream;
            }
            if (_isDebug) {
                *_stream << "[DEBUG] " << getTime() << " - " << funcName << " in " << file << ":" << line << " - ";
                return *_stream;
            } else {
                return _nullStream;
            }
        }

        std::ostream &info(const std::string &funcName, const std::string &file, int line)
        {
            if (!ENABLE_LOGGER) {
                return *_stream;
            }
            *_stream << "\033[0m[INFO] " << getTime() << " - " << funcName << " in " << file << ":" << line << " - ";
            return *_stream;
        }

        std::ostream &success(const std::string &funcName, const std::string &file, int line)
        {
            if (!ENABLE_LOGGER) {
                return *_stream;
            }
            *_stream << "\033[92m[SUCCESS] " << getTime() << " - " << funcName << " in " << file << ":" << line
                     << " - ";
            return *_stream;
        }

        std::ostream &warning(const std::string &funcName, const std::string &file, int line)
        {
            if (!ENABLE_LOGGER) {
                return *_stream;
            }
            (*_stream) << "\033[0m\033[33m[WARNING] " << getTime() << " - " << funcName << " in " << file << ":" << line
                       << " - ";
            return (*_stream);
        }

        std::ostream &error(const std::string &funcName, const std::string &file, int line)
        {
            if (!ENABLE_LOGGER) {
                return *_stream;
            }
            *_stream << "\033[0m\033[31m[ERROR] " << getTime() << " - " << funcName << " in " << file << ":" << line
                     << " - ";
            return *_stream;
        }

        std::ostream &fatal(const std::string &funcName, const std::string &file, int line)
        {
            _is_fatal = true;
            if (!ENABLE_LOGGER) {
                return *_stream;
            }
            *_stream << "\033[0m\033[1;4;31m[FATAL] " << getTime() << " - " << funcName << " in " << file << ":" << line
                     << " - ";
            return *_stream;
        }
    };
}