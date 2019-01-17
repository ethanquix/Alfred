#pragma once

namespace Alfred
{
    namespace Utils
    {
        template <typename T>
        class MakeFinal
        {
          private:
            ~MakeFinal()
            {};
            friend T;
        };
    }
}

