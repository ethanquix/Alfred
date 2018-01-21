#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <AlfredBase/Utils/Singleton.hpp>
#include <AlfredBase/Utils/MakeFinal.hpp>
#include <mutex>
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
                std::unordered_map<EventListener, std::function<Ret(Params...)>> _watchers;

              public:
                EventListener addWatchers(const std::function<Ret(Params...)> &_func)
                {
                    _watchers[_loc] = _func;
                    _loc += 1;
                    return _loc - 1;
                }

                typename std::conditional<std::is_same<Ret, void>::value, void, std::vector<Ret>>::type
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
            std::mutex _eventsMutex;
            std::unordered_map<std::string, ___event_helper *> _events;

          public:
            template <typename Ret, typename ...Params>
            void addEvent(const std::string &name)
            {
                _eventsMutex.lock();
                if (_events.count(name) > 0) {
                    _eventsMutex.unlock();
                    throw EventNameExist(name);
                }
                _events[name] = new ___Event<Ret, Params...>();
                _eventsMutex.unlock();
            }

            void deleteEvent(const std::string &name)
            {
                _eventsMutex.lock();
                _events.erase(name);
                _eventsMutex.unlock();
            }

            void clear()
            {
                _eventsMutex.lock();
                _events.clear();
                _eventsMutex.unlock();
            }

            template <typename Ret, typename ...Args>
            typename std::conditional<std::is_same<Ret, void>::value, void, std::vector<Ret>>::type
            fire(const std::string &name, const Args... args)
            {
                _eventsMutex.lock();
                if (_events.count(name) <= 0) {
                    _eventsMutex.unlock();
                    throw EventDontExist(name);
                }

                if constexpr (std::is_same<Ret, void>::value) {
                    static_cast<___Event<Ret, Args...> *>(_events[name])->execute(args...);
                    _eventsMutex.unlock();
                    return;
                } else {
                    std::vector<Ret> ret = static_cast<___Event<Ret, Args...> *>(_events[name])->execute(args...);
                    _eventsMutex.unlock();
                    return ret;
                }
            }

            template <typename Ret, typename ...Params, typename Fctor>
            const EventListener listen(const std::string &name, const Fctor &func)
            {
                _eventsMutex.lock();
                if (_events.count(name) <= 0) {
                    _eventsMutex.unlock();
                    throw EventDontExist(name);
                }
                EventListener ret = static_cast<___Event<Ret, Params...> *>(_events[name])->addWatchers(func);
                _eventsMutex.unlock();
                return ret;
            }

            template <typename Ret, typename ...Args>
            void unlisten(const std::string &name, const EventListener listenerID)
            {
                _eventsMutex.lock();
                static_cast<___Event<Ret, Args...> *>(_events[name])->deleteWatcher(listenerID);
                _eventsMutex.unlock();
            };
        };
    }
}


