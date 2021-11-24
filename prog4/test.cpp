#include "prog4.h"
#include <gtest/gtest.h>
TEST(Table, Positive) {
    Table t;
    EXPECT_THROW(t.get_Link(5), std::logic_error);
    EXPECT_THROW(t.delete_Link(2), std::logic_error);

    Item item1; item1.id = 3;
    t.insert_Link(item1);

    Plane **plane = new Plane*[4];
    PRO *pro = new PRO;
    plane[0] = pro;
    Link link(plane, 1);
    Item item2(1, link);
    t.insert_Link(item2);

    EXPECT_THROW(Link l1(nullptr, 5), std::logic_error);
    EXPECT_THROW(Link l2(nullptr, -1), std::logic_error);

    EXPECT_EQ(t.get_Link_count(), 2);
    Link l = t.get_Link(1);
    EXPECT_NE(l.get_plane(), link.get_plane());

    Const_It it = t.find(1);
    EXPECT_EQ(it->id, 1);

    t.delete_Link(1);
    EXPECT_EQ(t.get_Link_count(), 1);
    EXPECT_THROW(t.get_Link(1), std::logic_error);

}
