//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// ComponentPosition.hpp created 02/11/17

#pragma once

#include "Alfred/Ecs/Manager.hpp"

namespace Component
{
    class ComponentPosition : public Alfred::Ecs::Component
    {
      public:
        int _x;
        int _y;

        void init() override
        {
            _x = 0;
            _y = 0;
        }

        void print() override
        {
            LOG_DEBUG << "\t\tPosition " << _x << " " << _y << LOG_ENDL;
        }
    };

    class Acceleration : public Alfred::Ecs::Component
    {
      public:
        int _grav;

        void init() override
        {
            _grav = 9;
        }

        void print() override
        {
            LOG_DEBUG << "\t\tAcceleration " << _grav << LOG_ENDL;
        }
    };
}

namespace System
{
    class Movement : public Alfred::Ecs::System
    {
      public:
        void update() override
        {
            Alfred::Ecs::Manager::getSingleton().for_each_matching<Component::ComponentPosition, Component::Acceleration>([&] (Alfred::Ecs::Entity &e) {
                e.getComponent<Component::ComponentPosition>()._x += e.getComponent<Component::Acceleration>()._grav;
                e.getComponent<Component::ComponentPosition>()._y += e.getComponent<Component::Acceleration>()._grav / 2;
            });
        }

        void print() override
        {
            LOG_DEBUG << "\t\tMovement system" << LOG_ENDL;
        }
    };
}

