#include <iostream>
#include "prog4.h"
void print(int a) {
    std::cout << a << std::endl;
}
int table() {
    Table t;
    try {
        t.get_Link(5);
    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        t.delete_Link(2);
    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
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
    std::cout << l.get_plane() << std::endl;
    std::cout << link.get_plane() << std::endl;
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
        std::cout << e.what() << std::endl;
    }

    try {
        Link l1(nullptr, -1);
    } catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }

    return  0;
}

int main() {
    table();
    return 0;
}