#include "Alfred/Logger/Logger.hpp"

int main()
{
    LOG_SET_CONSOLE;

    LOG_INFO << "This is an info" << LOG_ENDL;
    LOG_DEBUG << "This is only shown on debug" << LOG_ENDL;
    LOG_SUCCESS << "This is a success" << LOG_ENDL;
    LOG_WARNING << "This is a warning" << LOG_ENDL;
    LOG_ERROR << "This is an error" << LOG_ENDL;

    try {
        LOG_FATAL << "This is a throw" << LOG_ENDL;
    } catch (Alfred::LoggerFatal loggerFatal) {
        std::cout << loggerFatal.what() << std::endl;
    }

    LOG_SET_FILE("log_example.log");
    LOG_SET_FORMAT("%Hh%M");
    LOG_DISABLE_DEBUG;

    LOG_SUCCESS << "Hurray !" << LOG_ENDL;

    return 0;
}