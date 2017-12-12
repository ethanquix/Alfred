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

class YOLO : public Alfred::Serializer::ISerializer<Alfred::Serializer::StringSerializer, YOLO>
{
  private:
    std::string a;
    int b;
    float c;

  public:
    YOLO()
    {
        a = "salut";
        b = 42;
        c = 13.37;
    }

    void serialize(Alfred::Serializer::StringSerializer &storage) override
    {
        a >> storage;
        b >> storage;
        c >> storage;
    }

    void deserialize(Alfred::Serializer::StringSerializer &storage) override
    {
        a << storage;
        b << storage;
    }

    std::string getX()
    {
        return a;
    }

    void setX(const std::string &src)
    {
        a = src;
    }

    friend std::ostream &operator<<(std::ostream &os, const YOLO &yolo)
    {
        os << "a: " << yolo.a << " b: " << yolo.b << " c: " << yolo.c;
        return os;
    }
};
