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

template <typename T>
class Singleton
{
private:
    T _singletonValue;

public:
    T &getSingleton()
    {
        if (_singletonValue)
            return _singletonValue;
        _singletonValue = T();
        return _singletonValue;
    }
};

#endif //ALFRED_SINGLETON_HPP
