//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// Counter.hpp created 02/11/17

#pragma once

namespace Alfred
{
    namespace Utils
    {
        namespace
        {
            template <typename T>
            class __counter
            {
                unsigned lastID = 0;
              public:
                inline unsigned Counter() noexcept
                {
                    return lastID++;
                }
            };

            static unsigned __last_cursor = 0;

            template <typename T>
            class __typeId__
            {
                unsigned _typeID = __last_cursor;
              public:
                __typeId__()
                {
                    __last_cursor += 1;
                }

                inline unsigned GetTypeID() noexcept
                {
                    return _typeID;
                }
            };
        }

        template <typename T>
        inline unsigned Counter() noexcept
        {
            static __counter<T> c;
            return c.Counter();
        }

        template <typename T>
        inline unsigned GetTypeID() noexcept
        {
            static __typeId__<T> t;
            return t.GetTypeID();
        }
    }
}


