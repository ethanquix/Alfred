//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/

// Manager.hpp created 02/11/17

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

        class System
        {
          public:
            Entity *entity;

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
                LOG.log("Entities: ");
                for (auto &it: _entities)
                    it.print();

                LOG.log("Systems: ");
                for (auto &it: _system)
                    it->print();
            }

            template <typename T>
            void updateSystem()
            {
                if (_systemBitSet[getSystemTypeID<T>()] == 0)
                    std::cout << "ERROR TRYING TO ACCESS BAD SYSTEM"
                              << std::endl; //TODO replace this by custom exception
                auto ptr(_systemArray[getSystemTypeID<T>()]);
                ptr->update();
            }
        };
    }
}