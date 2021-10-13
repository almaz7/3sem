#include <prog3.h>
#include <gtest/gtest.h>
using namespace STATIC;
TEST(Table, Positive) {
    Table t;
    char* str = new char[LENGTH];
    EXPECT_EQ(t.find_item(5), 4);
    EXPECT_EQ(t.find_item(1), 0);
    t.get_info(0, str);
    EXPECT_STREQ(str, "");
    EXPECT_THROW(t.get_info(-1, str), const char *);
    EXPECT_THROW(t.get_info(SIZE+1, str), const char *);
    delete str;
}

TEST(Table2, Positive) {
    Table t;
    char* str = new char[LENGTH];
    EXPECT_EQ(t.find_item(7), 6);
    EXPECT_EQ(t.find_item(3), 2);
    char str2[] = {"hello"};
    t.modify_info(3, str2);
    t.get_info(2, str);
    EXPECT_STREQ(str, "hello");
    t.delete_item(5);
    EXPECT_EQ(t.find_item(5), -1);
    EXPECT_THROW(t.get_info(-5, str), const char *);
    EXPECT_THROW(t.get_info(SIZE, str), const char *);
    delete str;
}

TEST(Table3, Positive) {
    Table t;
    char* str = new char[LENGTH];
    EXPECT_EQ(t.find_item(-10), -1);
    EXPECT_EQ(t.find_item(-4), -1);
    char str2[] = {"world"};
    t.modify_info(7, str2);
    t.get_info(6, str);
    EXPECT_STREQ(str, "world");
    t.delete_item(10);
    EXPECT_EQ(t.find_item(10), -1);
    EXPECT_THROW(t.add_item(1, str2), const char *);
    EXPECT_THROW(t.add_item(SIZE, str2), const char *);
    delete str;
}




