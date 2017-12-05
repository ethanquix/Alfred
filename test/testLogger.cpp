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
    LOG.log("log");
    LOG.log(Alfred::Logger::LOG_DEBUG, "debug");
    LOG.log(Alfred::Logger::LOG_INFO, "info");
    LOG.log(Alfred::Logger::LOG_WARNING, "warning");
    LOG.log(Alfred::Logger::LOG_ERROR, "error");

    ASSERT_THROW(LOG.log(Alfred::Logger::LOG_FATAL, "fatal"), Alfred::LoggerFatal);
}

TEST(Logger, Timer)
{
    LOG.timer_start("yop", "il sert a rien");
    LOG.timer_fire("yop");
}