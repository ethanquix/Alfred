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
#include <AlfredBase/Utils/MakeFinal.hpp>
#include "AlfredBase/EventManager/EventManagerExceptions.hpp"

#pragma GCC diagnostic ignored "-Wsubobject-linkage"

namespace Alfred
{
    namespace EventManager
    {
        using EventListener = int;

        namespace
        {
            class ___event_helper
            {
            };

            template <typename Ret, typename ...Params>
            class ___Event : public ___event_helper
            {
                EventListener _loc = 0;
                std::map<EventListener, std::function<Ret(Params...)>> _watchers;

              public:
                EventListener addWatchers(const std::function<Ret(Params...)> &_func)
                {
                    _watchers[_loc++] = _func;
                    return _loc - 1;
                }

                auto
                execute(Params ... args)
                {
                    if constexpr (!std::is_same<void, Ret>::value) {
                        std::vector<Ret> ret;
                        for (const auto &it: _watchers) {
                            ret.push_back(it.second(args...));
                        }
                        return ret;
                    } else {
                        for (const auto &it: _watchers) {
                            it.second(args...);
                        }
                    }
                }

                void deleteWatcher(const EventListener i)
                {
                    _watchers.erase(i);
                }
            };
        }

        class Manager : public Alfred::Utils::Singleton<Manager>, virtual public Alfred::Utils::MakeFinal<Manager>
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
            auto
            fire(const std::string &name, const Args... args)
            {
                if (_events.count(name) <= 0)
                    throw EventDontExist(name);
                return static_cast<___Event<Ret, Args...> *>(_events[name])->execute(args...);
            }

            template <typename Ret, typename ...Params, typename Fctor>
            const EventListener listen(const std::string &name, const Fctor &func)
            {
                if (_events.count(name) <= 0)
                    throw EventDontExist(name);
                return static_cast<___Event<Ret, Params...> *>(_events[name])->addWatchers(func);
            }

            template <typename Ret, typename ...Args>
            void unlisten(const std::string &name, const EventListener listenerID)
            {
                static_cast<___Event<Ret, Args...> *>(_events[name])->deleteWatcher(listenerID);
            };
        };
    }
}


