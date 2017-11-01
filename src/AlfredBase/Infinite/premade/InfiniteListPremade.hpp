#pragma once

#include "AlfredBase/Infinite/InfiniteList.hpp"

namespace Alfred
{
    namespace Infinite
    {
        namespace Premade
        {
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