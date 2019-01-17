#pragma once

#include "Alfred/Infinite/InfiniteList.hpp"

namespace Alfred
{
    namespace Infinite
    {
        namespace Premade
        {
#pragma warning(disable:4267)
            int premade_Counter(Alfred::Infinite::InfiniteList<int> &cur)
            {
                return cur.getIdx();
            }

            int premade_Fibonnacci(Alfred::Infinite::InfiniteList<int> &cur)
            {
                return cur[cur.getIdx() - 1] + cur[cur.getIdx() - 2];
            }
        }
    }
}