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
#include "AlfredBase/config.hpp"
#include "AlfredBase/Utils/Singleton.hpp"

namespace Alfred
{
    namespace Ecs
    {
        class Component;
        class Entity;
        class Manager;

        using ComponentID = std::size_t;
        using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
        using ComponentArray = std::array<Component *, MAX_COMPONENTS>;

        inline ComponentID getComponentTypeID() noexcept
        {
            static ComponentID lastID = 0;
            //TODO return throw if lastID > MAX_COMPONENTS
            return lastID++;
        }

        template <typename T>
        inline ComponentID getComponentTypeID() noexcept
        {
            static ComponentID typeID = getComponentTypeID();
            return typeID;
        }

        class Component
        {
          public:
            Entity *entity;

            virtual void init()
            {}

            virtual void update()
            {}

            virtual void print() = 0;

            virtual ~Component()
            {}
        };

        class Entity
        {
          private:
            bool _active = true;
            std::vector<Component *> _components;

            ComponentArray _componentArray;
            ComponentBitSet _componentBitSet;

          public:
            void update()
            {
                for (auto &c : _components)
                    c->update();
            }

            bool isActive() const
            {
                return _active;
            }

            void destroy()
            {
                _active = false;
            }

            void print()
            {
                for (auto &c : _components)
                    c->print();
            }

          private:
            /** <metaprogramming mess> */
            template <typename T>
            bool _hasComponent() const
            {
                return _componentBitSet[getComponentTypeID<T>()];
            }

            template <typename T, typename ...Others>
            struct RecHelper
            {
                static bool hasCompHelper(const Entity &e)
                {
                    return e._hasComponent<T>() && RecHelper<Others...>::hasCompHelper(e);
                }
            };

            template <typename T>
            struct RecHelper<T>
            {
                static bool hasCompHelper(const Entity &e)
                {
                    return e._hasComponent<T>();
                }
            };
            /** </metaprogramming mess> */

          public:

            template <typename ...Types>
            bool hasComponent() const
            {
                return RecHelper<Types...>::hasCompHelper(*this);
            }

            template <typename T, typename... TArgs>
            T &addComponent(TArgs &&... mArgs)
            {
                T *c(new T(std::forward<TArgs>(mArgs)...));
                c->entity = this;
                _components.emplace_back(c);

                _componentArray[getComponentTypeID<T>()] = c;
                _componentBitSet[getComponentTypeID<T>()] = true;

                c->init();
                return *c;
            }

            template <typename T>
            T &getComponent() const
            {
                if (_componentBitSet[getComponentTypeID<T>()] == 0)
                    std::cout << "ERROR TRYING TO ACCESS BAD COMPONENT"
                              << std::endl; //TODO replace this by custom exception
                auto ptr(_componentArray[getComponentTypeID<T>()]);
                return *static_cast<T *>(ptr);
            }
        };

        class Manager : public Alfred::Utils::Singleton<Manager>
        {
          private:
            std::vector<Entity> _entities;

          public:

            void update()
            {
                for (auto &e :  _entities)
                    e.update();
            }

            void refresh()
            {
                _entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
                                               [](const Entity &e) {
                                                   return !e.isActive();
                                               }), std::end(_entities));
            }

            Entity *addEntity() //TODO need to do this again
            {
                _entities.emplace_back();
                return &_entities.back();
            }

            const unsigned nbEntities() const
            {
                return _entities.size();
            }

            template <typename ...Types, typename Fctor>
            void for_each_matching(const Fctor& f)
            {
                std::for_each(_entities.begin(), _entities.end(), [&f](Entity& et)
                {
                    if (et.template hasComponent<Types...>())
                    {
                        f(et);
                    }
                });
            }

            void print()
            {
                for (auto &it: _entities)
                    it.print();
            }
        };
    }
}


