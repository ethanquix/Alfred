//      ___  _  __              _   _____
//    / _ \| |/ _|            | | |  ___|
//   / /_\ \ | |_ _ __ ___  __| | | |__  ___ ___
//  |  _  | |  _| '__/ _ \/ _` | |  __|/ __/ __|
//  | | | | | | | | |  __/ (_| | | |__| (__\__ \
//  \_| |_/_|_| |_|  \___|\__,_| \____/\___|___/

// EventManager.hpp created 03/11/17

#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <AlfredBase/Utils/Singleton.hpp>
#include "AlfredBase/EventManager/EventManagerExceptions.hpp"

namespace Alfred
{
    namespace EventManager
    {
        namespace { class ___event_helper {};

        template <typename Ret, typename ...Params>
        class ___Event : public ___event_helper
        {
            std::vector<std::function<Ret(Params...)>> _watchers;

          public:
            void addWatchers(const std::function<Ret(Params...)> &_func)
            {
                _watchers.push_back(_func);
            }

            typename std::conditional<std::is_same<Ret, void>::value, void, std::vector<Ret>>::type execute(Params &&... args)
            {
                if constexpr (!std::is_same<void, Ret>::value) {
                    std::vector<Ret> ret;
                    for (const auto &it: _watchers) {
                        ret.push_back(it(args...));
                    }
                    return ret;
                }
                else {
                    for (const auto &it: _watchers) {
                        it(args...);
                    }
                }
            }
        };
        }

        class Manager : public Alfred::Utils::Singleton<Manager>
        {
            std::unordered_map<std::string, ___event_helper *> _events;

          public:
            template <typename Ret, typename ...Params>
            void addEvent(const std::string &name)
            {
                if (_events.count(name) > 0)
                    throw EventNameExist(name);
                _events[name] = new ___Event<Ret, Params...>();
            }

            void deleteEvent(const std::string &name)
            {
                _events.erase(name);
            }

            void clear()
            {
                _events.clear();
            }

            template <typename Ret, typename ...Args>
            typename std::conditional<std::is_same<Ret, void>::value, void, std::vector<Ret>>::type fire(const std::string &name, Args &&... args)
            {
                if (_events.count(name) <= 0)
                    throw EventDontExist(name);
                return static_cast<___Event<Ret, Args...> *>(_events[name])->execute(std::forward<Args>(args)...);
            }

            template <typename Ret, typename ...Params, typename Fctor>
            void listen(const std::string &name, const Fctor &func)
            {
                if (_events.count(name) <= 0)
                    throw EventDontExist(name);
                static_cast<___Event<Ret, Params...> *>(_events[name])->addWatchers(func);
            }
        };
    }
}


