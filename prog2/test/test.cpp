#include <prog2.h>
#include <gtest/gtest.h>

TEST(Hypo, Positive) {
    Hypo h(1, 5, 1);

    EXPECT_NEAR(h.get_x(3.14),-3, 0.01);
    EXPECT_NEAR(h.get_y(3.14), 0.01274, 0.01);
    EXPECT_NEAR(h.get_square(3.14), 18.8496, 0.01);
    EXPECT_NEAR(h.get_rad_curv(3.14), 5.33329, 0.01);
    EXPECT_NEAR(h.get_r(),1, 0.01);
    EXPECT_EQ(h.get_type(), USUAL);
    EXPECT_NEAR(h.get_R(), 5, 0.01);
}

TEST(Hypo2, Positive) {
    Hypo h(2, 3, 0);

    EXPECT_NEAR(h.get_x(1),0.540302, 0.01);
    EXPECT_NEAR(h.get_y(1), 0.841471, 0.01);
    EXPECT_NEAR(h.get_square(1), 0.5, 0.01);
    EXPECT_NEAR(h.get_rad_curv(1), 1, 0.01);
    EXPECT_NEAR(h.get_r(),2, 0.01);
    EXPECT_EQ(h.get_type(),SHORTENED);
    EXPECT_NEAR(h.get_R(), 3, 0.01);
}

TEST(Hypo3, Positive) {
    Hypo h(5.5, 15.6, 7.9);

    EXPECT_NEAR(h.get_x(2),-11.0147, 0.01);
    EXPECT_NEAR(h.get_y(2), 13.1853, 0.01);
    EXPECT_NEAR(h.get_square(2), 19.341, 0.01);
    EXPECT_NEAR(h.get_rad_curv(2), 3.34366, 0.01);
    EXPECT_NEAR(h.get_r(),5.5, 0.01);
    EXPECT_EQ(h.get_type(), ELONGATE);
    EXPECT_NEAR(h.get_R(), 15.6, 0.01);
}

TEST(Hypo4, Positive) {
    Hypo h;
    EXPECT_ANY_THROW(h.set_r(-1));
    EXPECT_ANY_THROW(h.set_R(-8));
    EXPECT_ANY_THROW(h.set_d(-4));
    EXPECT_ANY_THROW(h.set_r(0));
    EXPECT_ANY_THROW(h.set_R(0));
}

TEST(Hypo5, Positive) {

    EXPECT_ANY_THROW(Hypo h(-1, 1, 1));
    EXPECT_ANY_THROW(Hypo h(0, 1, 1));
    EXPECT_ANY_THROW(Hypo h(1, -1, 1));
    EXPECT_ANY_THROW(Hypo h(1, 0, 1));
    EXPECT_ANY_THROW(Hypo h(-1, 1, -6));
}


