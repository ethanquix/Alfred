/*
** Singleton.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Singleton.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Tue May 30 16:08:04 2017 Dimitri Wyzlic
** Last update Tue May 30 16:08:04 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_SINGLETON_HPP
#define ALFRED_SINGLETON_HPP

#include "NonCopyable.hpp"

namespace Alfred
{
    namespace Utils
    {
        template <typename T>
        struct Singleton : public NonCopyable
        {
            inline static T &getSingleton()
            {
                static T _singletonValue;
                return _singletonValue;
            }

            static T &get()
            {
                return getSingleton();
            }
        };
    }
}
#endif //ALFRED_SINGLETON_HPP
