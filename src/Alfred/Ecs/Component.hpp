#pragma once

#include "Alfred/Ecs/EcsCounter.hpp"

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

            virtual void print() = 0;

            virtual ~Component()
            {}
        };
    }
}


