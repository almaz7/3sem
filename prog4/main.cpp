#include <iostream>
#include "prog4.h"
template <typename T>
void print(T a) {
    std::cout << a << std::endl;
}
int table() {
    Table t;
    try {
        t.get_Link(5);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        t.delete_Link(2);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    Item item1; item1.id = 3;
    t.insert_Link(item1);

    Plane **plane = new Plane*[4];
    PRO *pro = new PRO;
    plane[0] = pro;
    Link link(plane, 1);

    Item item2(1, link);
    t.insert_Link(item2);

    Link l = t.get_Link(1);
    Const_It it = t.find(1);
    print(it->id);

    t.delete_Link(1);
    print(t.get_Link_count());

    try {
        t.get_Link(1);
    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        Link l1(nullptr, 5);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Link l1(nullptr, -1);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }

    Mask *mask = new Mask;
    Link l1;
    l1.insert_plane(*mask);
    Item item3(5, l1);
    t.insert_Link(item3);
    print(t.get_Link_count());

    delete plane[0];
    delete [] plane;
    delete mask;
    return  0;
}

int link() {
    Plane **plane = new Plane*[4];
    PRO *pro = new PRO;
    plane[0] = pro;
    Mask *mask = new Mask;
    plane[1] = mask;
    Link link(plane,2);
    std::cout << link << std::endl;

    Scout *scout = new Scout;
    try {
        link.insert_plane(*scout);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "*****" << std::endl;
    std::cout << link << std::endl;
    try {
        link.delete_plane(1);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "*****" << std::endl;
    std::cout << link << std::endl;
    REB *reb = new REB;
    try {
        link.insert_plane(*reb);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        link.insert_plane(*pro);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "*****" << std::endl;
    std::cout << link << std::endl;
    try {
        link.insert_plane(*scout);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "*****" << std::endl;
    std::cout << link << std::endl;

    try {
        link.delete_plane(5);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        link.delete_plane(0);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        link.delete_plane(2);
        link.delete_plane(3);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        link.delete_plane(4);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "*****" << std::endl;
    std::cout << link << std::endl;
    delete scout;
    delete pro;
    delete reb;
    delete mask;
    delete [] plane;
    return 0;
}

int link_radius() {
    Plane **plane = new Plane*[4];
    PRO *pro = new PRO;
    plane[0] = pro;
    Mask *mask = new Mask;
    plane[1] = mask;
    Link link1(plane,2);
    std::cout << link1 << std::endl;


    Link link2;
    REB *reb = new REB;
    Scout *scout = new Scout;
    link2.insert_plane(*reb);
    link2.insert_plane(*scout);
    std::cout << link2 << std::endl;

    Link link3;
    link3.insert_plane(*mask);
    link3.insert_plane(*scout);
    std::cout << link3 << std::endl;

    Link link4;
    link4.insert_plane(*mask);
    link4.insert_plane(*mask);
    std::cout << link4 << std::endl;

    print(link3.get_enemy_find_r(link4));
    print(link1.get_enemy_find_r(link4));
    print(link2.get_enemy_find_r(link4));
    print(link2.get_enemy_find_r(link1));
    print(link3.get_enemy_find_r(link2));
    delete scout;
    delete pro;
    delete reb;
    delete mask;
    delete [] plane;
    return 0;
}


int plane() {
    Plane *plane = new Plane;
    PRO *pro = new PRO;
    Mask *mask = new Mask;
    Radio *radio = new Radio(10,0);
    REB *reb = new REB;
    Scout *scout = new Scout;

    print("Attacking area");
    print(plane->get_attack_r());
    print(pro->get_attack_r());

    print("Finding radius");
    print(plane->get_r());
    print(pro->get_r());


    print("Shoot 2 planes with rockets");
    pro->rocket_shoot(*scout, pro->get_REB_p());
    pro->rocket_shoot(*reb, pro->get_REB_p());
    print(pro->get_attack_r());
    print(scout->get_cur_health());
    print(reb->get_cur_health());

    Mask *mask1 = new Mask;
    print("Shoot 2 planes with gun");
    pro->gun_shoot(*mask, pro->get_REB_p());
    pro->gun_shoot(*radio, pro->get_REB_p());
    reb->gun_shoot(*mask1, reb->get_REB_p());
    print(pro->get_attack_r());
    print(mask->get_cur_health());
    print(mask1->get_cur_health());
    print(radio->get_cur_health());

    delete plane; delete pro; delete mask; delete radio; delete reb; delete scout; delete mask1;
    return 0;
}

int mission() {
    Mission m;
    //m.get_plane_t(1,2);
    //m.delete_plane_enemy_t(2,5);

    Mask *mask = new Mask;
    REB *reb = new REB;
    PRO *pro = new PRO;
    Link l1;
    l1.insert_plane(*mask);

    Item item(5, l1);
    m.insert_Link_t(item);
    Plane *p = m.get_plane_t(5,1);
    //if (p) std::cout << *p << std::endl;

    m.insert_plane_t(1,*reb);
    m.insert_plane_enemy_t(2,*pro);
    m.insert_plane_enemy_t(2,*reb);
    std::cout << m;

    m.gun_shoot_plane_in_enemy_t(1,1,2,1);
    m.gun_shoot_plane_in_t(2,1,5,1);
    std::cout << m;

    m.rocket_shoot_plane_in_enemy_t(5,1,2,2);
    m.rocket_shoot_plane_in_enemy_t(1,1,2,1);
    std::cout << m;

    delete mask; delete pro; delete reb;
    return 0;
}

int main() {
    table();
    link();
    link_radius();
    plane();
    mission();
    return 0;
}