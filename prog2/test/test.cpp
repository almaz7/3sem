#include <prog2.h>
#include <gtest/gtest.h>

TEST(Hypo, Positive) {
Hypo h(1, 5, 1, 3.14);

EXPECT_NEAR(h.get_x(),-3, 0.01);
EXPECT_NEAR(h.get_y(), 0.01274, 0.01);
EXPECT_NEAR(h.get_square(), 18.8496, 0.01);
EXPECT_NEAR(h.get_rad_curv(), 5.33329, 0.01);
EXPECT_EQ(h.get_r(),1);
EXPECT_EQ(h.get_type(),0);
EXPECT_NE(h.get_R(), 6);
}


