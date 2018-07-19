#pragma once

#include "AlfredBase/Ecs/Manager.hpp"
#include "AlfredBase/Ecs/Component.hpp"

namespace Alfred
{
    namespace Ecs
    {
        class Component;

        class ComponentDontExist : public std::exception
        {
            std::string message;
        public:
            ComponentDontExist(const std::string& msg)
                : message(std::string("Error trying to access bad component: ") + msg)
            {}

            const char* what() const throw() override
            {
                return message.c_str();
            }

        };

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
                LOG_DEBUG << "\tID: " << _idx << LOG_ENDL;
                LOG_DEBUG << "\t\tComponents: " << LOG_ENDL;
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
                    throw ComponentDontExist("don't exist");
                auto ptr(_componentArray[getComponentTypeID<T>()]);
                return *static_cast<T *>(ptr);
            }
        };
    }
}


