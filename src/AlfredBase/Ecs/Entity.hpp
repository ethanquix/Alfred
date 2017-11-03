//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/

// Entity.hpp created 02/11/17

#pragma once

#include "AlfredBase/Ecs/Manager.hpp"
#include "AlfredBase/Ecs/Component.hpp"

namespace Alfred
{
    namespace Ecs
    {
        class Component;

        class Entity
        {
          private:
            bool _active = true;
            std::vector<Component *> _components;

            ComponentArray _componentArray;
            ComponentBitSet _componentBitSet;

            unsigned _idx;

          public:
            Entity(unsigned int idx) :
                _idx(idx)
            {}

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
                std::cout << "ID: " << _idx << std::endl;
                for (auto &c : _components)
                {
                    c->print();
                }
            }

            const unsigned getID() const
            {
                return _idx;
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
    }
}


