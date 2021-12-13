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

    Const_It it = t.find(1);
    EXPECT_EQ(it->id, 1);

    t.delete_Link(1);
    EXPECT_EQ(t.get_Link_count(), 1);
    EXPECT_THROW(t.get_Link(1), std::logic_error);

    Mask *mask = new Mask;
    Link l1;
    l1.insert_plane(*mask);
    Item item3(5, l1);
    t.insert_Link(item3);
    EXPECT_EQ(t.get_Link_count(), 2);

    delete plane[0];
    delete [] plane;
    delete mask;
}

TEST(Link, Positive) {
    Plane **plane = new Plane*[4];
    PRO *pro = new PRO;
    plane[0] = pro;
    Mask *mask = new Mask;
    Scout *scout = new Scout;
    plane[1] = mask;
    Link link(plane,2);
    EXPECT_EQ(link.get_plane_count(), 2);

    link.insert_plane(*scout);
    EXPECT_EQ(link.get_plane_count(), 3);
    link.delete_plane(1);
    EXPECT_EQ(link.get_plane_count(), 2);

    REB *reb = new REB;

    link.insert_plane(*reb);
    EXPECT_EQ(link.get_plane_count(), 3);
    link.insert_plane(*pro);
    EXPECT_EQ(link.get_plane_count(), 4);
    EXPECT_THROW(link.insert_plane(*scout), std::logic_error);

    EXPECT_THROW(link.delete_plane(5), std::logic_error);
    EXPECT_THROW(link.delete_plane(0), std::logic_error);

    link.delete_plane(2);
    link.delete_plane(3);
    EXPECT_EQ(link.get_plane_count(), 2);
    EXPECT_THROW(link.delete_plane(4), std::logic_error);

    delete scout;
    delete pro;
    delete reb;
    delete mask;
    delete [] plane;
}

TEST(Plane, Positive) {
    Plane *plane = new Plane;
    PRO *pro = new PRO;
    Mask *mask = new Mask;
    Radio *radio = new Radio;
    REB *reb = new REB;
    Scout *scout = new Scout;


    EXPECT_EQ(plane->get_attack_r(), 50);
    EXPECT_EQ(pro->get_attack_r(), 50);

    EXPECT_EQ(plane->get_r(), 100);
    EXPECT_EQ(pro->get_r(), 100);

    pro->rocket_shoot(*scout, pro->get_REB_p());
    EXPECT_EQ(pro->get_rocket().get_cur_count(), 1);
    EXPECT_EQ(pro->get_attack_r(), 50);
    pro->rocket_shoot(*reb, pro->get_REB_p());
    EXPECT_EQ(pro->get_rocket().get_cur_count(), 0);
    EXPECT_EQ(pro->get_attack_r(), 10);
    EXPECT_EQ(scout->get_cur_health(), 0);
    EXPECT_EQ(reb->get_cur_health(), 0);

    pro->gun_shoot(*mask, pro->get_REB_p());
    pro->gun_shoot(*radio, pro->get_REB_p());

    EXPECT_NE(mask->get_cur_health(), 100);
    EXPECT_NE(radio->get_cur_health(), 100);
    EXPECT_EQ(mask->get_cur_health() >= radio->get_cur_health(), 1);

    delete plane; delete pro; delete mask; delete radio; delete reb; delete scout;
}

TEST(Mission, Positive) {
    Mission m;
    Mask *mask = new Mask;
    REB *reb = new REB;
    PRO *pro = new PRO;
    Link l1;
    l1.insert_plane(*mask);

    Item item(5, l1);
    m.insert_Link_t(item);
    Plane *p = m.get_plane_t(5,1);
    EXPECT_EQ(p->get_type(), 2);
    EXPECT_EQ(m.get_Link_count_t(), 1);

    m.insert_plane_t(1,*reb);
    p = m.get_plane_t(1,1);
    EXPECT_EQ(p->get_type(), 4);
    EXPECT_EQ(m.get_Link_count_t(), 2);

    m.insert_plane_enemy_t(2,*pro);
    m.insert_plane_enemy_t(2,*reb);
    p = m.get_plane_enemy_t(2,1);
    EXPECT_EQ(m.get_Link_count_enemy_t(), 1);
    EXPECT_EQ(p->get_type(), 1);
    p = m.get_plane_enemy_t(2,2);
    EXPECT_EQ(p->get_type(), 4);

    m.gun_shoot_plane_in_enemy_t(1,1,2,1);
    m.gun_shoot_plane_in_t(2,1,5,1);
    p = m.get_plane_enemy_t(2,1);
    EXPECT_NE(p->get_cur_health(), 100);
    p = m.get_plane_t(5,1);
    EXPECT_EQ(p->get_cur_health() <= 100, 1);

    m.rocket_shoot_plane_in_enemy_t(5,1,2,2);
    EXPECT_EQ(m.get_Link_count_enemy_t(), 1);

    m.delete_plane_enemy_t(2,1);
    EXPECT_EQ(m.get_Link_count_enemy_t(), 0);


    delete mask; delete pro; delete reb;
}