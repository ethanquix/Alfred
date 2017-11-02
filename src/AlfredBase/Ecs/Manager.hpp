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
#include "AlfredBase/Ecs/Entity.hpp"

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

            virtual void init() {}
            virtual void update() {}
            virtual void draw() {}

            virtual ~Component() {}
        };

        class Entity
        {
          private:
            bool _active = true;
            std::vector<std::unique_ptr<Component>> _components;

            ComponentArray _componentArray;
            ComponentBitSet _componentBitSet;

          public:
            void update()
            {
                for (auto &c : _components)
                    c->update();
                for (auto &c : _components)
                    c->draw();
            }

            void draw() {};

            bool isActive() const
            {
                return _active;
            }

            void destroy ()
            {
                _active = false;
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
                static bool hasCompHelper(const Entity& e)
                {
                    return e._hasComponent<T>() && RecHelper<Others...>::hasCompHelper(e);
                }
            };

            template <typename T>
            struct RecHelper<T>
            {
                static bool hasCompHelper(const Entity& e)
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
            T& addComponent(TArgs &&... mArgs)
            {
                T *c(new T(std::forward<TArgs>(mArgs)...));
                c->entity = this;
                std::unique_ptr<Component> uniquePtr{c};
                _components.emplace_back(std::move(uniquePtr));

                _componentArray[getComponentTypeID<T>()] = c;
                _componentBitSet[getComponentTypeID<T>()] = true;

                c->init();
                return *c;
            }

            template <typename T>
            T &getComponent() const
            {
                auto ptr(_componentArray[getComponentTypeID<T>()]);
                return *static_cast<T *>(ptr);
            }

        };

        class Manager : Alfred::Utils::Singleton<Manager>
        {
          private:
            std::vector<std::unique_ptr<Entity>> _entities;

          public:
            void update()
            {
                for (auto &e :  _entities)
                    e->update();
            }

            void draw()
            {
                for (auto &e :  _entities)
                    e->draw();
            }

            void refresh()
            {
                _entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
                [] (const std::unique_ptr<Entity> &e) {
                    return !e->isActive();
                }), std::end(_entities));
            }

            Entity &addEntity()
            {
                Entity *e = new Entity();
                std::unique_ptr<Entity> uniquePtr{e};
                _entities.emplace_back(std::move(uniquePtr));
                return *e;
            }
        };
    }
}


