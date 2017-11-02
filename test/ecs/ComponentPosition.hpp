//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// ComponentPosition.hpp created 02/11/17

#pragma once

#include "AlfredBase/Ecs/Manager.hpp"

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

        void update() override
        {
            std::cout << "X: " << _x << "\nY: " << _y << std::endl;
        }

        void print() override
        {
            std::cout << "Position" << std::endl;
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

        void update() override
        {
            Alfred::Ecs::Manager::getSingleton().for_each_matching<ComponentPosition, Acceleration>([&] (Alfred::Ecs::Entity &e) {
                e.getComponent<ComponentPosition>()._x += _grav;
                e.getComponent<ComponentPosition>()._y += _grav / 2;
            });
        }

        void print() override
        {
            std::cout << "Acceleration" << std::endl;
        }
    };

}

