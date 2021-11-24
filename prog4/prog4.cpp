#include "prog4.h"

Link::Link(const Link &l):plane_count(l.plane_count), command(l.command), x(l.x), y(l.y) {
    plane = nullptr;
    if (l.plane_count > 0) {
        plane = new Plane*[4];
        PRO pro; Mask mask; Radio radio; REB reb; Scout scout;
        for (int i = 0; i < l.plane_count; i++) {
            if (typeid(*l.plane[i]) == typeid(pro)) {
                plane[i] = new PRO;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(mask)) {
                plane[i] = new Mask;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(radio)) {
                plane[i] = new Radio;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(reb)) {
                plane[i] = new REB;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(scout)) {
                plane[i] = new Scout;
                *plane[i] = *l.plane[i];
            } else plane[i] = nullptr;
        }
    }
}

void Link::insert_plane(const Plane &p) {
    if (plane_count >= 4) throw std::logic_error("Count of planes in Link can't be more than 4");
    PRO pro; Mask mask; Radio radio; REB reb; Scout scout;
    
}

void Link::delete_plane(const int& i) {

}

Const_It Table::find(const int& id) const {
    std::vector<Item>::const_iterator it;
    for (it = vec.begin(); it != vec.end(); ++it) {
        if (it->id == id) return it;
    }
    return it;
}

Link& Table::get_Link(const int& id)  {
    Const_It it;
    it = find(id);

    if (it == vec.end()) throw std::logic_error("There is no link with such id");
    return const_cast<Link&>(it->link);
}

int Table::get_Link_count() const {return vec.size();}

void Table::insert_Link(Item &item) {
    Const_It it;
    it = find(item.id);
    if (it != vec.end()) throw std::logic_error("Item with such id already exists");
    vec.push_back(item);
}

void Table::delete_Link(const int& id) {
    Const_It it;
    it = find(id);
    if (it == vec.end()) throw std::logic_error("There is no link with such id");
    vec.erase(it);
}

bool correct_get_int(int &a) noexcept {
    std::cin >> a;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

int get_int() noexcept {
    int num;
    while (true) {
        if (correct_get_int(num))
            break;
        std::cout << "Wrong number" << std::endl;
    }
    return num;
}
