#pragma once

#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <string>
#include <array>
#include <memory>
#include <ostream>
#include <iostream>
#include <map>
#include <AlfredBase/Logger/Logger.hpp>
#include <AlfredBase/Utils/MapSingleton.hpp>
#include "AlfredBase/Utils/Counter.hpp"
#include "AlfredBase/config.hpp"
#include "AlfredBase/Utils/Singleton.hpp"
#include "AlfredBase/Ecs/EcsCounter.hpp"
#include "AlfredBase/Ecs/Entity.hpp"

namespace Alfred
{
    namespace Ecs
    {
        class Component;

        class Entity;

        class Manager;

        class SystemDontExist : public std::exception
        {
            std::string message;
        public:
            SystemDontExist(const std::string& msg)
                : message(std::string("Error trying to access bad system: ") + msg)
            {}

            const char* what() const throw() override
            {
                return message.c_str();
            }

        };

        class System
        {
          public:
            Entity *entity; //vector of entity ?

            virtual void update() = 0;

            virtual void print() = 0;

            virtual ~System()
            {}
        };


#if ECS_MULTIMAP_SINGLETON
        class Manager : public Alfred::Utils::MapSingleton<std::string, Manager>
#else
        class Manager : public Alfred::Utils::Singleton<Manager>
#endif
        {
          private:
            std::vector<Entity> _entities;
            std::vector<System *> _system;

            SystemArray _systemArray;
            SystemBitSet _systemBitSet;

          public:
            Manager()
            {
                _entities.reserve(ENTITIES_RESERVED);
            }

            void refresh()
            {
                _entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
                                               [&](const Entity &e) {
                                                   return !e.isActive();
                                               }), std::end(_entities));
            }

            /**
             * @brief Create an entity
             * @return Return a pointer to the entity. WARNING this pointer is only available for a short duration, so you should better use it quickly !!!
             */
            Entity *addEntity()
            {
                unsigned tmpIDX = Alfred::Utils::Counter<Entity>();

                _entities.emplace_back(tmpIDX);

                return &_entities.back();
            }

#pragma warning(disable:4267)
            const unsigned nbEntities() const
            {
                return _entities.size();
            }

            Entity *getEntityByID(unsigned id)
            {
                auto it = std::find_if(_entities.begin(), _entities.end(), [id](const Entity &et) {
                    return et.getID() == id;
                });

                return &(*it);
            }

            template <typename ...Types, typename Fctor>
            void for_each_matching(const Fctor &f)
            {
                std::for_each(_entities.begin(), _entities.end(), [&f](Entity &et) {
                    if (et.template hasComponent<Types...>()) {
                        f(et);
                    }
                });
            }

            template <typename Fctor>
            void for_each_all(const Fctor &f)
            {
                std::for_each(_entities.begin(), _entities.end(), [&f](Entity &et) {
                    f(et);
                });
            }

            template <typename T, typename... TArgs>
            void addSystem(TArgs &&... args)
            {
                T *s(new T(std::forward<TArgs>(args)...));

                _systemArray[getSystemTypeID<T>()] = s;
                _systemBitSet[getSystemTypeID<T>()] = true;

                _system.push_back(s);
            }

            void print()
            {
                LOG_DEBUG << "Entities: " << LOG_ENDL;
                for (auto &it: _entities)
                    it.print();

                LOG_DEBUG << "Systems: " << LOG_ENDL;
                for (auto &it: _system)
                    it->print();
            }

            template <typename T>
            void updateSystem()
            {
                if (_systemBitSet[getSystemTypeID<T>()] == 0)
                    throw SystemDontExist("don't exist");
                auto ptr(_systemArray[getSystemTypeID<T>()]);
                ptr->update();
            }
        };
    }
}