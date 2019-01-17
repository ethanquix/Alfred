#pragma once

namespace Alfred
{
    namespace Ecs
    {
        class Component;
        class System;

        using ComponentID = unsigned;
        using SystemID = unsigned;

        using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
        using ComponentArray = std::array<Component *, MAX_COMPONENTS>;

        using SystemArray = std::array<System *, MAX_SYSTEMS>;
        using SystemBitSet = std::bitset<MAX_SYSTEMS>;

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


        inline SystemID getSystemTypeID() noexcept
        {
            static SystemID lastID = 0;
            return lastID++;
        }

        template <typename T>
        inline SystemID getSystemTypeID() noexcept
        {
            static SystemID typeID = getSystemTypeID();
            return typeID;
        }

    }
}