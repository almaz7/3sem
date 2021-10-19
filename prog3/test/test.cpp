#include <prog3.h>
#include <gtest/gtest.h>
TEST(Table, Positive) {
    Table t;
    EXPECT_EQ(t.get_n(), 0);
    EXPECT_EQ(t.find_item(1), -1);
    char* str = new char[Item::LENGTH];
    EXPECT_THROW(t.get_info(1, str, Item::LENGTH), const char *);
    EXPECT_THROW(t.get_info(t.get_size()+1, str, Item::LENGTH), const char *);
    EXPECT_THROW(t.modify_info(1, str), const char *);
    EXPECT_THROW(t.get_info(0, str, Item::LENGTH), const char *);
    delete [] str;
}

TEST(Table2, Positive) {
    Item items[] = {{1, "1"},{2, "2"}};
    Table t(items, 2);
    EXPECT_EQ(t.get_n(), 2);
    EXPECT_EQ(t.find_item(2), 1);
    Item items2[] = {{6, "6"},{4, "4"}};
    t = t + items2[0];
    t = t + items2[1];
    EXPECT_EQ(t.get_n(), 4);
    EXPECT_EQ(t.find_item(6), 3);
    char* str = new char[Item::LENGTH];
    t.get_info(1, str, Item::LENGTH);
    EXPECT_STREQ(str, "2");
    t.get_info(2, str, Item::LENGTH);
    EXPECT_STREQ(str, "4");
    char str2[] = {"world"};
    t.modify_info(1, str2);
    t.get_info(0, str, Item::LENGTH);
    EXPECT_STREQ(str, "world");
    EXPECT_THROW(t.get_info(-1, str, Item::LENGTH), const char *);
    t = t - items2[1];
    EXPECT_EQ(t.get_n(), 3);
    EXPECT_EQ(t.find_item(4), -1);
}

TEST(Table3, Positive) {
    Item items[] = {{3, "3"}, {5, "5"}, {10, "10"}, {8, "8"}};
    Table t(items, 4);
    EXPECT_EQ(t.get_n(), 4);
    EXPECT_EQ(t.find_item(8), 2);
    Item items2[] = {{5, "5"},{4, "4"}};
    EXPECT_THROW(t = t + items2[0], const char *);
    t = t + items2[1];
    EXPECT_EQ(t.find_item(5), 2);
    EXPECT_EQ(t.find_item(4), 1);
    EXPECT_EQ(t.get_n(), 5);

    char* str = new char[Item::LENGTH];
    t.get_info(4, str, Item::LENGTH);
    EXPECT_STREQ(str, "10");
    char str2[] = {"world"};
    t.modify_info(10, str2);
    t.get_info(4, str, Item::LENGTH);
    EXPECT_STREQ(str, "world");
    t = t - items2[0];
    EXPECT_EQ(t.get_n(), 4);
    EXPECT_EQ(t.find_item(5), -1);

    Item items3[] = {{15, "15"},{20, "20"}};
    Table t2(items3, 2);
    t += t2;
    EXPECT_EQ(t.get_n(), 6);
    EXPECT_EQ(t.find_item(15), 4);
    EXPECT_EQ(t.find_item(20), 5);
    EXPECT_THROW(t += t2, const char *);
}




