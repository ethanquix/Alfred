///*
//** EventManager.hpp for cpp_arcade in /home/wyzlic_a/delivery/cpp_arcade/EventManager.hpp
//**
//** Made by Dimitri Wyzlic
//** Login   <dimitri1.wyzlic@epitech.eu>
//**
//** Started on  Fri Mar 17 02:22:03 2017 Dimitri Wyzlic
//** Last update Fri Mar 17 02:22:03 2017 Dimitri Wyzlic
//*/
//
//#pragma once
//
//#include <map>
//#include <vector>
//#include <unordered_map>
//#include <iostream>
//#include "EventManagerExceptions.hpp"
//
//namespace Alfred
//{
//    namespace EventManager
//    {
//        class IWatcher
//        {
//        public:
//            virtual void execute(std::string arg) = 0;
//        };
//
//        /**
//         * @details Watcher is here to watch change and handle callback when needed
//         * @tparam T is the class given with the event
//         * @var callback is the callback to be call from the class given
//         */
//        template <typename T>
//        class Watcher : public IWatcher
//        {
//            using _func = void (T::*)(std::string &);
//
//        public:
//            T *obj;
//            _func callback;
//
//            Watcher(T *obj, _func callback) :
//                obj(obj),
//                callback(callback)
//            {}
//
//            void execute(std::string arg) override
//            { (obj->*callback)(arg); }
//        };
//
//        class EventManager
//        {
//            std::vector<IWatcher *> _watchers;
//
//        public:
//            size_t fired{0};
//
//            EventManager() = default;
//
//            template <typename T>
//            /**
//             * Add a watcher to the map
//             * @param obj Event Class
//             * @param func Callback Function
//             */
//            void addWatcher(T *obj, void (T::*func)(std::string &))
//            {
//                _watchers.push_back(new Watcher<T>(obj, func));
//            }
//
//            /*
//             * Loop all watcher and execute their callback(s)
//             */
//            void execute(const std::string &arg)
//            {
//                fired += 1;
//                for (auto &watcher : _watchers)
//                    watcher->execute(arg);
//            }
//        };
//
//        class Manager
//        {
//            using EventsMap = std::unordered_map<std::string, EventManager *>;
//
//            EventsMap _events;
//
//        private:
//            Manager() = default;
//
//        public:
//            /**
//             * Use this to always get the same Manager
//             * @return
//             */
//            static Manager *control()
//            {
//                static Manager cur;
//                return &cur;
//            }
//
//            /**
//             * Check if the name doenst already exist and add an Event
//             * @param name
//             */
//            void createEvent(std::string name)
//            {
//                EventsMap::const_iterator it;
//
//                it = _events.find(name);
//                if (it != _events.end())
//                    throw EventNameExist(name);
//                _events.insert(std::pair<std::string, EventManager *>(name, new EventManager()));
//            }
//
//            /**
//             * Watch an event
//             * @param name Name of event
//             * @param obj Class of event to call callback from
//             * @param func Callback
//             * @return success or failure
//             * We do not raise exception here because we can use that to know if an event exist
//             */
//            template <typename Class>
//            bool watch(const std::string &name, Class *obj, void (Class::*func)(std::string &))
//            {
//                EventsMap::const_iterator it;
//
//                it = _events.find(name);
//                if (it == _events.end())
//                    createEvent(name);
//                it = _events.find(name);
//                if (it == _events.end())
//                    throw std::runtime_error("Event unknown error during event creation");
//                it->second->addWatcher(obj, func);
//                return true;
//            }
//
//            /**
//             * Execute all event watcher from name
//             * @param name
//             */
//            void fire(const std::string &name, const std::string &arg = "")
//            {
//                EventsMap::const_iterator it;
//
//                it = _events.find(name);
//                if (it != _events.end())
//                    it->second->execute(arg);
//                else
//                    throw EventDontExist(name);
//            }
//
//            /**
//             * Delete an event
//             * @param name name of the event to delete
//             */
//            void deleteEvent(const std::string &name)
//            {
//                EventsMap::const_iterator it;
//
//                it = _events.find(name);
//                if (it != _events.end())
//                    _events.erase(it);
//                else
//                    throw EventDontExist(name);
//            }
//
//            /*
//             * Clear all events
//             */
//            void clear()
//            {
//                _events.clear();
//            }
//
//            /**
//             * Dump all the name of all the events
//             */
//            void dump()
//            {
//                if (_events.empty()) {
//                    std::cout << "No event found" << std::endl;
//                    return;
//                }
//                for (const auto &it : _events)
//                    std::cout << "Event in manager -> " << it.first << " fired [" << it.second->fired << "] times"
//                              << std::endl;
//            }
//        };
//    }
//}