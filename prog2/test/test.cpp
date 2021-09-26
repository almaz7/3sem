#include <prog2.h>
#include <gtest/gtest.h>

TEST(Hypo, Positive) {
Hypo h(1, 5, 1, 3.14);

EXPECT_NEAR(h.get_x(),-3, 3);
EXPECT_NEAR(h.get_y(), 0.01274, 3);
EXPECT_NEAR(h.get_square(), 18.8496, 3);
EXPECT_EQ(h.get_r(),1);
EXPECT_NE(h.get_R(), 6);
}


