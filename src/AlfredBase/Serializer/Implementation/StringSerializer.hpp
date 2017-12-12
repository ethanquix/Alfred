
#pragma once

#include <unordered_map>
#include "AlfredBase/Utils/Counter.hpp"
#include "AlfredBase/Serializer/Serializer.hpp"
#include <iostream>

namespace Alfred
{
    namespace Serializer
    {
        static std::string __SERIALIZER_STRING_IDENTIFIER_STRING = "01";
        static std::string __SERIALIZER_STRING_IDENTIFIER_INT = "02";
        static std::string __SERIALIZER_STRING_IDENTIFIER_FLOAT = "03";
        static std::string __SERIALIZER_STRING_IDENTIFIER_DOUBLE = "04";

        class StringSerializer
        {
          private:
            size_t _cursorPosition;
            std::string _data;

          public:
            std::string &getData()
            {
                return _data;
            }

            void feedWith(const std::string &input)
            {
                _data = input;
            }

            //SERIALIZE

            //std::string
            friend void operator>>(const std::string &input, StringSerializer &storage)
            {
                storage._data += __SERIALIZER_STRING_IDENTIFIER_STRING + std::to_string(input.size()) + " " + input;
            }

            //int
            friend void operator>>(const int input, StringSerializer &storage)
            {
                std::string tmp = std::to_string(input);
                storage._data += __SERIALIZER_STRING_IDENTIFIER_INT + std::to_string(tmp.size()) + " " + tmp;
            }

            //double
            friend void operator>>(const double input, StringSerializer &storage)
            {
                std::string tmp = std::to_string(input);
                storage._data += __SERIALIZER_STRING_IDENTIFIER_DOUBLE + std::to_string(tmp.size()) + " " + tmp;
            }

            //float
            friend void operator>>(const float &input, StringSerializer &storage)
            {
                std::string tmp = std::to_string(input);
                storage._data += __SERIALIZER_STRING_IDENTIFIER_FLOAT + std::to_string(tmp.size()) + " " + tmp;
            }

            //DESERIALIZE

            friend std::string &operator<<(std::string &input, StringSerializer &storage)
            {
                input = storage._data;
            }

            //UTILS

            friend std::ostream &operator<<(std::ostream &os, const StringSerializer &storage)
            {
                os << "_data: " << storage._data;
                return os;
            }
        };
    }
}

