//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// EcsCounter.hpp created 03/11/17

#pragma once

namespace Alfred
{
    namespace Ecs
    {
        class Component;

        using ComponentID = unsigned;

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

    }
}