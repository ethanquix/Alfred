#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <mutex>
#include <cstdint>
#include <Alfred/Utils/MakeFinal.hpp>
#include <ostream>
#include "Alfred/EventManager/EventManagerExceptions.hpp"

#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
//#ifdef __linux__
//#pragma GCC diagnostic ignored "-Wsubobject-linkage"
//#elif _WIN32
//#pragma GCC diagnostic ignored "/Wsubobject-linkage"
//#else

//#endif

namespace detail
{
  // FNV-1a 32bit hashing algorithm.
  constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
  {
    return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
  }
}    // namespace detail

constexpr std::uint32_t operator"" _hash(char const* s, std::size_t count)
{
  return detail::fnv1a_32(s, count);
}

namespace Alfred
{
  namespace EventManager
  {
    using EventListener = int;

    namespace
    {
      class ___event_helper
      {
        public:
          virtual std::string str() = 0;
      };

      template <typename Ret, typename ...Params>
      class ___Event : public ___event_helper
      {
          EventListener _loc = 0;
          std::unordered_map<EventListener, std::function<Ret(Params...)>> _watchers;

        public:

          ___Event() :
            _watchers()
          {}

          virtual ~___Event()
          {
            _watchers.clear();
          }

          EventListener addWatchers(const std::function<Ret(Params...)> &_func)
          {
            _watchers[_loc] = _func;
            _loc += 1;
            return _loc - 1;
          }

          std::vector<Ret> executeAndReturn(Params ... args)
          {
            std::vector<Ret> ret;
            for (const auto &it: _watchers)
              ret.push_back(it.second(args...));
            return ret;
          }

          void execute(Params ... args)
          {
            for (const auto &it: _watchers) {
              it.second(args...);
            }
          }

          void deleteWatcher(const EventListener i)
          {
            _watchers.erase(i);
          }

          std::string str()
          override
          {
            std::string out = std::to_string(_watchers.size());

            return out;
          }
      };
    }

    class Manager : virtual public Alfred::Utils::MakeFinal<Manager>
    {
        std::recursive_mutex _mutex;
        std::unordered_map<int, ___event_helper *> _events;
        std::unordered_map<int, int> _counter;

      public:
        Manager() :
          _events(),
          _counter()
        {
        }

        virtual ~Manager()
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          for (const auto &e : _events)
            delete e.second;
        }

      public:
        template <typename Ret, typename ...Params>
        void addEvent(int name)
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          if (_events.count(name) > 0) {
            throw EventNameExist(name); //todo remove this, put in private
          }

          _counter[name] = 0;

          _events[name] = new ___Event<Ret, Params...>();
        }

        void deleteEvent(int name)
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          _events.erase(name);
        }

        void clear()
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          _events.clear();
        }

        template <typename Ret, typename ...Args>
        std::vector<Ret> fireAndReturn(int name, const Args... args)
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          if (_events.count(name) <= 0) {
            addEvent<Ret, Args...>(name);
//                    throw EventDontExist(name);
          }
          _counter[name] += 1;

          std::vector<Ret> ret = static_cast<___Event<Ret, Args...> *>(_events[name])->executeAndReturn(args...);
          return ret;
        }

        template <typename Ret, typename ...Args>
        void fire(int name, const Args... args)
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          if (_events.count(name) <= 0) {
            addEvent<Ret, Args...>(name);
//                    throw EventDontExist(name);
          }

          _counter[name] += 1;

          static_cast<___Event<Ret, Args...> *>(_events[name])->execute(args...);
        }

        template <typename Ret, typename ...Params, typename Fctor>
        const EventListener listen(int name, const Fctor &func)
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          if (_events.count(name) <= 0) {
            addEvent<Ret, Params...>(name);
//                    throw EventDontExist(name);
          }
          EventListener ret = static_cast<___Event<Ret, Params...> *>(_events[name])->addWatchers(func);
          return ret;
        }

        template <typename Ret, typename ...Args>
        void unlisten(int name, const EventListener listenerID)
        {
          std::lock_guard<std::recursive_mutex> lock(_mutex);
          static_cast<___Event<Ret, Args...> *>(_events[name])->deleteWatcher(listenerID);
        };

        std::string str()
        {
          std::string out = "Events:\n";
          std::lock_guard<std::recursive_mutex> lock(_mutex);

          for (const auto &e : _events) {
            out += "- " + std::to_string(e.first) + "\t- fired " + std::to_string(_counter[e.first]) + " times - [";
            out += e.second->str() + "]\n";
          }
          return out;
        }
    };
  }
}