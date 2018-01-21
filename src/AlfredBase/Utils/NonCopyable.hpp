#pragma once

namespace Alfred
{
    namespace Utils
    {
        class NonCopyable
        {
          public:
            NonCopyable() = default;
            virtual ~NonCopyable() = default;

            NonCopyable(NonCopyable const &) = delete;

            NonCopyable(NonCopyable &&) = delete;

            NonCopyable &operator=(const NonCopyable &) = delete;

            NonCopyable &operator=(NonCopyable &&) = delete;
        };
    }
}