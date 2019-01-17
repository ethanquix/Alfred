#include <gtest/gtest.h>
#include "Alfred/Serializer/Implementation/StringSerializer.hpp"


class TestSerializerClass : public Alfred::Serializer::ISerializer<Alfred::Serializer::StringSerializer, TestSerializerClass>
{
  private:
    std::string my_string;
    int my_int;
    float my_float;
    double my_double;

  public:
    TestSerializerClass()
    {
        my_string = "salut";
        my_int = 42;
        my_float = 13.37;
        my_double = 13.37;
    }

    const std::string &getMy_string() const
    {
        return my_string;
    }

    void setMy_string(const std::string &my_string)
    {
        TestSerializerClass::my_string = my_string;
    }

    int getMy_int() const
    {
        return my_int;
    }

    void setMy_int(int my_int)
    {
        TestSerializerClass::my_int = my_int;
    }

    float getMy_float() const
    {
        return my_float;
    }

    void setMy_float(float my_float)
    {
        TestSerializerClass::my_float = my_float;
    }

    double getMy_double() const
    {
        return my_double;
    }

    void setMy_double(double my_double)
    {
        TestSerializerClass::my_double = my_double;
    }

    void serialize(Alfred::Serializer::StringSerializer &storage) override
    {
        my_string >> storage;
        my_int >> storage;
        my_float >> storage;
    }

    void deserialize(Alfred::Serializer::StringSerializer &storage) override
    {
        my_string << storage;
        my_int << storage;
        my_float << storage;
    }

    friend std::ostream &operator<<(std::ostream &os, const TestSerializerClass &src)
    {
        os << "a: " << src.my_string << " b: " << src.my_int << " c: " << src.my_float;
        return os;
    }
};

TEST(Serializer, String)
{
    TestSerializerClass test;
    std::string storage;

    test >> storage;
    ASSERT_EQ(storage, "015 salut022 42039 13.370000");

    test.setMy_string("NOPE");
    test.setMy_int(0);
    test.setMy_float(0);
    test.setMy_double(0);

    storage >> test;

    ASSERT_EQ(test.getMy_string(), "salut");

    storage << test;
    ASSERT_EQ(storage, "015 salut022 42039 13.370000");
}
