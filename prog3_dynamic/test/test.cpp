#include <prog3.h>
#include <gtest/gtest.h>
TEST(Table, Positive) {
    Table t;
    EXPECT_EQ(t.get_n(), 0);
    EXPECT_EQ(t.find_item(1), -1);
    EXPECT_EQ(t.get_item(), nullptr);
    char* str = new char[1000];
    EXPECT_THROW(t.get_info(1), const char *);
    EXPECT_THROW(t.modify_info(1, str), const char *);
    EXPECT_THROW(t.get_info(0), const char *);
    delete [] str;
}

TEST(Table2, Positive) {
    Item *items = new Item[2];
    items[0].str = new char[10];
    items[1].str = new char[10];
    items[0].key = 2;
    items[1].key = 5;
    strcat(items[0].str,"2");
    strcat(items[1].str,"5");
    Table t(items, 2);
    EXPECT_EQ(t.get_n(), 2);
    EXPECT_EQ(t.find_item(5), 1);
    EXPECT_EQ(t.find_item(2), 0);
    char *str= nullptr;
    str = t.get_info(1);
    EXPECT_STREQ(str, "5");
    delete [] str;
    str = t.get_info(0);
    EXPECT_STREQ(str, "2");
    EXPECT_THROW(t = t + items[0], const char *);
    EXPECT_THROW(t = t + items[1], const char *);

    t = t - items[1];
    EXPECT_EQ(t.get_n(), 1);
    EXPECT_EQ(t.find_item(5), -1);
    t.modify_info(2, items[1].str);
    delete [] str;
    str = t.get_info(0);
    EXPECT_STREQ(str, "5");
    EXPECT_THROW(t = t - items[1], const char *);
    delete [] str;
    delete_items(items, 2);
}

TEST(Table3, Positive) {
    Item *items1 = new Item[2];
    items1[0].str = new char[10];
    items1[1].str = new char[10];
    items1[0].key = 2;
    items1[1].key = 5;
    strcat(items1[0].str,"2");
    strcat(items1[1].str,"5");
    Table t1(items1, 2);

    Item *items2 = new Item[2];
    items2[0].str = new char[10];
    items2[1].str = new char[10];
    items2[0].key = 2;
    items2[1].key = 1;
    strcat(items2[0].str,"6");
    strcat(items2[1].str,"1");
    Table t2(items2, 2);
    EXPECT_THROW(t1 += t2, const char *);

    items2[0].key = 6;
    Table t3(items2, 2);
    t1 += t3;
    EXPECT_EQ(t1.get_n(), 4);
    EXPECT_EQ(t3.get_n(), 2);
    EXPECT_EQ(t1.find_item(1), 0);
    EXPECT_EQ(t1.find_item(2), 1);
    EXPECT_EQ(t1.find_item(5), 2);
    EXPECT_EQ(t1.find_item(6), 3);
    delete_items(items1, 2);
    delete_items(items2, 2);
}


