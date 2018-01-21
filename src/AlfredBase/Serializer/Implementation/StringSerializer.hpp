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
            size_t _cursorPosition = 0;
            std::string _data;

          public:
            void prepareSerialization()
            {
                _data.clear();
                _cursorPosition = 0;
            }

            std::string &getData()
            {
                return _data;
            }

            void feedWith(const std::string &input)
            {
                _cursorPosition = 0;
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

            //std::string
            friend std::string &operator<<(std::string &input, StringSerializer &storage)
            {
                unsigned long max = storage._data.size();
                unsigned long i = storage._cursorPosition + 2;
                unsigned long bckpI = i;
                int len;

                if (i >= max)
                    throw std::runtime_error("Corrupt data");

                if (!storage.verifyIdentifier(__SERIALIZER_STRING_IDENTIFIER_STRING, i - 2, 2))
                    throw std::runtime_error("Bad verification code");

                while (i < max && storage._data[i] != ' ') {
                    i += 1;
                }

                if (storage._data[i] != ' ')
                    throw std::runtime_error("Corrupt data");

                len = std::stoi(storage._data.substr(bckpI, i - bckpI));

                if (i + len >= max)
                    throw std::runtime_error("Corrupt data");

                i += 1;

                storage._cursorPosition = i + len;

                input = storage._data.substr(i, len);

                return input;
            }

            //int
            friend int operator<<(int &input, StringSerializer &storage)
            {
                unsigned long max = storage._data.size();
                unsigned long i = storage._cursorPosition + 2;
                unsigned long bckpI = i;
                int len;

                if (i >= max)
                    throw std::runtime_error("Corrupt data");

                if (!storage.verifyIdentifier(__SERIALIZER_STRING_IDENTIFIER_INT, i - 2, 2))
                    throw std::runtime_error("Bad verification code");

                while (i < max && storage._data[i] != ' ') {
                    i += 1;
                }

                if (storage._data[i] != ' ')
                    throw std::runtime_error("Corrupt data");

                len = std::stoi(storage._data.substr(bckpI, i - bckpI));

                if (i + len >= max)
                    throw std::runtime_error("Corrupt data");

                i += 1;

                storage._cursorPosition = i + len;

                input = std::stoi(storage._data.substr(i, len));

                return input;
            }

            //float
            friend float operator<<(float &input, StringSerializer &storage)
            {
                unsigned long max = storage._data.size();
                unsigned long i = storage._cursorPosition + 2;
                unsigned long bckpI = i;
                int len;

                if (i >= max)
                    throw std::runtime_error("Corrupt data");

                if (!storage.verifyIdentifier(__SERIALIZER_STRING_IDENTIFIER_FLOAT, i - 2, 2))
                    throw std::runtime_error("Bad verification code");

                while (i < max && storage._data[i] != ' ') {
                    i += 1;
                }

                if (storage._data[i] != ' ')
                    throw std::runtime_error("Corrupt data");

                len = std::stoi(storage._data.substr(bckpI, i - bckpI));

                if (i + len >= max)
                    throw std::runtime_error("Corrupt data");

                i += 1;

                storage._cursorPosition = i + len;

                input = std::stof(storage._data.substr(i, len));

                return input;
            }

            //double
            friend float operator<<(double &input, StringSerializer &storage)
            {
                unsigned long max = storage._data.size();
                unsigned long i = storage._cursorPosition + 2;
                unsigned long bckpI = i;
                int len;

                if (i >= max)
                    throw std::runtime_error("Corrupt data");

                if (!storage.verifyIdentifier(__SERIALIZER_STRING_IDENTIFIER_DOUBLE, i - 2, 2))
                    throw std::runtime_error("Bad verification code");

                while (i < max && storage._data[i] != ' ') {
                    i += 1;
                }

                if (storage._data[i] != ' ')
                    throw std::runtime_error("Corrupt data");

                len = std::stoi(storage._data.substr(bckpI, i - bckpI));

                if (i + len >= max)
                    throw std::runtime_error("Corrupt data");

                i += 1;

                storage._cursorPosition = i + len;

                input = std::stod(storage._data.substr(i, len));

                return input;
            }

            //UTILS

          private:

            const bool verifyIdentifier(const std::string &waitedID, unsigned long start, unsigned long len) const
            {
                return _data.substr(start, len) == waitedID;
            }
        };
    }
}

