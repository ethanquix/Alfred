//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/

// Component.hpp created 02/11/17

#pragma once

#include "AlfredBase/Ecs/EcsCounter.hpp"

namespace Alfred
{
    namespace Ecs
    {
        class Entity;

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
    }
}


