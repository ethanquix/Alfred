#pragma once

#include <string>
#include <sstream>
#include <ostream>

#include "Implementation/StringSerializer.hpp"

namespace Alfred
{
    namespace Serializer
    {
        template <typename SerializerType, typename Child>
        class ISerializer
        {
          private:
            SerializerType __alfred__storage;

          public:
            virtual void serialize(SerializerType &storage) = 0;

            virtual void deserialize(SerializerType &storage) = 0;

            void feedWith(const decltype(std::declval<SerializerType>().getData()) input)
            {
                __alfred__storage.feedWith(input);
                deserialize(__alfred__storage);
            }

            auto getAs()
            {
                __alfred__storage.prepareSerialization();
                serialize(__alfred__storage);
                return __alfred__storage.getData();
            }

            friend void operator>>(decltype(std::declval<SerializerType>().getData()) &input, Child &child)
            {
                child.feedWith(input);
            }

            friend void operator>>(Child &child, decltype(std::declval<SerializerType>().getData()) &input)
            {
                input = child.getAs();
            }

            friend void operator<<(Child &child, decltype(std::declval<SerializerType>().getData()) &input)
            {
                child.feedWith(input);
            }

            friend void operator<<(decltype(std::declval<SerializerType>().getData()) &input, Child &child)
            {
                input = child.getAs();
            }
        };
    }
}
