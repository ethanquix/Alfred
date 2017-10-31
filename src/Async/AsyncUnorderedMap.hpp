#pragma once

#include <unordered_map>
#include <mutex>

namespace Alfred
{
    namespace Async
    {
        template <typename S, typename T>
        class AsyncUnorderedMap : public std::unordered_map<S, T>
        {
          private:
            std::mutex map_mutex;

          public:

            T &async_at(const S &key)
            {
                map_mutex.lock();
                T *ret = &this->at(key);
                map_mutex.unlock();
                return *ret;
            }

            AsyncUnorderedMap &async_erase(const S &key)
            {
                map_mutex.lock();
                this->erase(key);
                return *this;
            }
        };
    }
};
