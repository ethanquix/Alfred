/*
** testLogger.cpp for Alfred in /home/wyzlic_a/delivery/Alfred/testLogger.cpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Tue May 16 20:06:34 2017 Dimitri Wyzlic
** Last update Tue May 16 20:06:34 2017 Dimitri Wyzlic
*/

#include "../src/Logger/Logger.hpp"

int main()
{
    LOG.log("yop");
    LOG.log(Alfred::Logger::DEBUG, "yop");
    LOG.log(Alfred::Logger::INFO, "yop");
    LOG.log(Alfred::Logger::WARNING, "yop");
    LOG.log(Alfred::Logger::ERROR, "yop");
    LOG.log(Alfred::Logger::FATAL, "yop");
    LOG.timer_start("yop", "il sert a rien");
    LOG.timer_fire("yop");
}