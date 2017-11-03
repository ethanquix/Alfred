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
            //TODO entity vector (map ?)
          public:
        };

        class Manager : public Alfred::Utils::Singleton<Manager>
        {
          private:
            std::vector<std::unique_ptr<Entity>> _entities;
            std::map<unsigned, Entity *> _idxID_Entitie;

          public:
            Manager()
            {
//                _entities.reserve(ENTITIES_RESERVED);
            }

            void update()
            {
                for (auto &e :  _entities)
                    e->update();
            }

            void refresh()
            {
                _entities.erase(std::remove_if(std::begin(_entities), std::end(_entities),
                                               [&](const std::unique_ptr<Entity> &e) {
                                                   if (!e->isActive()) {
                                                       _idxID_Entitie.erase(e->getID());
                                                       return false;
                                                   }
                                                   return true;
                                               }), std::end(_entities));
            }

            /**
             * @brief Create an entity
             * @return Return a pointer to the entity. WARNING this pointer is only available for a short duration, so you should better use it quickly !!!
             */
            Entity *addEntity()
            {
                unsigned tmpIDX = Alfred::Utils::Counter<Entity>();

                _entities.emplace_back(new Entity(tmpIDX));

                _idxID_Entitie[tmpIDX] = _entities.back().get();

                return _entities.back().get();
            }

            const unsigned nbEntities() const
            {
                return _entities.size();
            }

            Entity* getEntityByID(unsigned id)
            {
                auto it = std::find_if(_entities.begin(), _entities.end(), [id](const std::unique_ptr<Entity>& et)
                {
                    return et->getID() == id;
                });

                return (*it).get();
            }

            template <typename ...Types, typename Fctor>
            void for_each_matching(const Fctor& f)
            {
                std::for_each(_entities.begin(), _entities.end(), [&f](std::unique_ptr<Entity>& et)
                {
                    if (et.get()->template hasComponent<Types...>())
                    {
                        f(et);
                    }
                });
            }

            template <typename Fctor>
            void for_each_all(const Fctor& f)
            {
                std::for_each(_entities.begin(), _entities.end(), [&f](Entity& et)
                {
                    f(et);
                });
            }

            void print()
            {
                for (auto &it: _entities)
                    it->print();
            }

            Entity *getEntity(unsigned idx)
            {
                if (_idxID_Entitie[idx] == nullptr)
                    throw std::runtime_error("TODO CUSTOM EXEC NOT FOUND ENTITIE IN GET ENTITIE"); //TODO
                return _idxID_Entitie[idx];
            }
        };
    }
}