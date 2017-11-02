////
//// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______
/////\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\
////\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____
//// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\
////  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/
//
//// Entity.hpp created 02/11/17
//
//#pragma once
//
//#include "AlfredBase/Ecs/Manager.hpp"
//#include "AlfredBase/Ecs/Component.hpp"
//
//namespace Alfred
//{
//    namespace Ecs
//    {
//        class Entity
//        {
//          private:
//            bool _active = true;
//            std::vector<std::unique_ptr<Component>> _components;
//
//            ComponentArray _componentArray;
//            ComponentBitSet _componentBitSet;
//
//          public:
//            void update()
//            {
//                for (auto &c : _components)
//                    c->update();
//                for (auto &c : _components)
//                    c->draw();
//            }
//
//            void draw() {};
//
//            bool isActive() const
//            {
//                return _active;
//            }
//
//            void destroy ()
//            {
//                _active = false;
//            }
//
//            template <typename T>
//            bool hasComponent() const
//            {
//                return _componentBitSet[getComponentTypeID<T>()];
//            }
//
//            template <typename T, typename... TArgs>
//            T& addComponent(TArgs &&... mArgs)
//            {
//                T *c(new T(std::forward<TArgs>(mArgs)...));
//                c->entity = this;
//                std::unique_ptr<Component> uniquePtr{c};
//                _components.emplace_back(std::move(uniquePtr));
//
//                _componentArray[getComponentTypeID<T>()] = c;
//                _componentBitSet[getComponentTypeID<T>()] = true;
//
//                c->init();
//                return *c;
//            }
//
//            template <typename T>
//            T &getComponent() const
//            {
//                auto ptr(_componentArray[getComponentTypeID<T>()]);
//                return *static_cast<T *>(ptr);
//            }
//
//        };
//    }
//}
//
//
