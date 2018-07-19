/*
** testLogger.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testLogger.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Tue May 16 20:06:34 2017 Dimitri Wyzlic
** Last update Tue May 16 20:06:34 2017 Dimitri Wyzlic
*/

#include <gtest/gtest.h>
#include "AlfredBase/Logger/Logger.hpp"

TEST(Logger, Exception)
{
    LOG_SET_CONSOLE;
    LOG_INFO << "info" << LOG_ENDL;
    LOG_DEBUG << "debug" << LOG_ENDL;
    LOG_WARNING <<"warning" << LOG_ENDL;
    LOG_ERROR << "error" << LOG_ENDL;

    ASSERT_THROW(LOG_FATAL << "fatal" << LOG_ENDL, Alfred::LoggerFatal);
}

//TEST(Logger, Timer)
//{
//    LOG.timer_start("yop", "il sert a rien");
//    LOG.timer_fire("yop");
//}