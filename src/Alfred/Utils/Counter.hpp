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


