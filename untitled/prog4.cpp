#include "prog4.h"
#include <cmath>
float Plane::get_attack_r() const {
    float d;
    if (rocket.get_cur_count() > 0) {
        d = my_max(gun.get_dist(), rocket.get_dist());
    } else d = gun.get_dist();
    return d;
}

void Plane::get_gun_damage(const int& dmg, const int& p, const int& rof, const int& gun_count, const float& plane_reduce_hit) noexcept {
    srand(time(0));
    for (int i = 0; i < rof; i++) {
        if (rand() % 100 < p * plane_reduce_hit) cur_health -= dmg * gun_count;
    }
    if (cur_health < 0) cur_health = 0;
}

void Plane::get_rocket_damage(const int& dmg, const int& rof, int r_count, const int& REB_p) noexcept {
    int pro_count = get_cur_pro_count();
    for (int i = 0; i < rof; i++) {
        if (r_count <= 0) break;
        if (pro_count > 0) {
            if (rand() % 100 < REB_p) cur_health -= dmg * r_count;
            pro_count--;
        } else cur_health -= dmg * r_count;
        r_count--;
    }
    set_cur_pro_count(pro_count);
    if (cur_health < 0) cur_health = 0;
}

void Plane::gun_shoot(Plane &plane, const int& REB_p) noexcept {
    float x1 = x, x2 = plane.get_x(), y1 = y, y2 = plane.get_y();
    if (gun.get_dist() < sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))) {
        return;
    }
    int dmg = gun.get_dmg(), p = gun.get_p(), rof = gun.get_rof();
    float plane_reduce_hit;
    if (typeid(plane) == typeid(Mask)) {
        plane_reduce_hit = plane.get_reduce_hit();  //коэффициент изменения процента попаданий
        //REB_p - процент игнорирования маскировки(0 - для обычного, >=0 для REB)
        plane_reduce_hit += float(REB_p)/100;
        if (plane_reduce_hit > 1) plane_reduce_hit = 1;
    } else plane_reduce_hit = 1;
    plane.get_gun_damage(dmg, p, rof, gun_count, plane_reduce_hit);
}

void Plane::rocket_shoot(Plane &plane, const int& REB_p) noexcept {
    float x1 = x, x2 = plane.get_x(), y1 = y, y2 = plane.get_y();
    int dmg = rocket.get_dmg(), rof = rocket.get_rof(), r_count = rocket.get_cur_count();
    if (rocket.get_dist() < sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))) {
        r_count -= rof;
        if (r_count < 0) r_count = 0;
        rocket.set_cur_count(r_count);
        return;
    }
    plane.get_rocket_damage(dmg, rof, r_count, REB_p);
    r_count -= rof;
    if (r_count < 0) r_count = 0;
    rocket.set_cur_count(r_count);
}

Link::Link(Plane **p, const int& count) {
    if (!p) throw std::logic_error("Pointer is nullptr");
    if (count < 0) throw std::logic_error("Count of planes in Link can't be less than 0");
    if (count > 4) throw std::logic_error("Count of planes in Link can't be more than 4");
    plane = nullptr;
    if (count > 0) {
        plane = new Plane*[4];
        for (int i = 0; i < count; i++) {
            if (typeid(*p[i]) == typeid(PRO)) {
                plane[i] = new PRO;
                *plane[i] = *p[i];
            } else if (typeid(*p[i]) == typeid(Mask)) {
                plane[i] = new Mask;
                *plane[i] = *p[i];
            } else if (typeid(*p[i]) == typeid(Radio)) {
                plane[i] = new Radio;
                *plane[i] = *p[i];
            } else if (typeid(*p[i]) == typeid(REB)) {
                plane[i] = new REB;
                *plane[i] = *p[i];
            } else if (typeid(*p[i]) == typeid(Scout)) {
                plane[i] = new Scout;
                *plane[i] = *p[i];
            } else plane[i] = nullptr;
        }
    }
    isSelectToMove = false;
    isMove = false;
    for (int i = 0; i < 4; i++) {
        isSelectToGun[i] = false;
        isSelectToRocket[i] = false;
    }
    plane_count = count;
}

Link::Link(const Link &l):plane_count(l.plane_count), command(l.command), x(l.x), y(l.y) {
    plane = nullptr;
    if (l.plane_count > 0) {
        plane = new Plane*[4];

        for (int i = 0; i < l.plane_count; i++) {
            if (typeid(*l.plane[i]) == typeid(PRO)) {
                plane[i] = new PRO;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(Mask)) {
                plane[i] = new Mask;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(Radio)) {
                plane[i] = new Radio;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(REB)) {
                plane[i] = new REB;
                *plane[i] = *l.plane[i];
            } else if (typeid(*l.plane[i]) == typeid(Scout)) {
                plane[i] = new Scout;
                *plane[i] = *l.plane[i];
            } else plane[i] = nullptr;
        }
    }
    isSelectToMove = l.isSelectToMove;
    isMove = l.isMove;
    for (int i = 0; i < 4; i++) {
        s[i] = l.s[i];
        isSelectToGun[i] = l.isSelectToGun[i];
        isSelectToRocket[i] = l.isSelectToRocket[i];
    }
}

Link& Link::operator=(const Link &l) {
    if (this != &l) {
        for (int i = 0; i < plane_count; i++) {
            delete plane[i];
            plane[i] = nullptr;
        }
        delete [] plane;
        plane = nullptr;
        plane_count = l.plane_count;
        command = l.command;
        x = l.x;
        y = l.y;
        if (l.plane_count > 0) {
            plane = new Plane*[4];

            for (int i = 0; i < l.plane_count; i++) {
                if (typeid(*l.plane[i]) == typeid(PRO)) {
                    plane[i] = new PRO;
                    *plane[i] = *l.plane[i];
                } else if (typeid(*l.plane[i]) == typeid(Mask)) {
                    plane[i] = new Mask;
                    *plane[i] = *l.plane[i];
                } else if (typeid(*l.plane[i]) == typeid(Radio)) {
                    plane[i] = new Radio;
                    *plane[i] = *l.plane[i];
                } else if (typeid(*l.plane[i]) == typeid(REB)) {
                    plane[i] = new REB;
                    *plane[i] = *l.plane[i];
                } else if (typeid(*l.plane[i]) == typeid(Scout)) {
                    plane[i] = new Scout;
                    *plane[i] = *l.plane[i];
                } else plane[i] = nullptr;
            }
        }
    }
    isSelectToMove = l.isSelectToMove;
    isMove = l.isMove;
    for (int i = 0; i < 4; i++) {
        s[i] = l.s[i];
        isSelectToGun[i] = l.isSelectToGun[i];
        isSelectToRocket[i] = l.isSelectToRocket[i];
    }
    return *this;
}

void Link::insert_plane(const Plane &p) {
    if (plane_count >= 4) throw std::logic_error("Count of planes in Link can't be more than 4");
    PRO pro; Mask mask; Radio radio; REB reb; Scout scout;

    if (plane_count == 0)  {
        try {
            plane = new Plane *[4];
            isSelectToMove = false;
            isMove = false;
            for (int i = 0; i < 4; i++) {
                isSelectToGun[i] = false;
                isSelectToRocket[i] = false;
            }
        } catch (std::bad_alloc &ba) {
            std::cout << ba.what() << std::endl;
            return;
        }
    }

    isSelectToGun[plane_count] = false;
    isSelectToRocket[plane_count] = false;
    if (typeid(p) == typeid(pro)) {
        plane[plane_count] = new PRO;
        *plane[plane_count++] = p;
    } else if (typeid(p) == typeid(mask)) {
        plane[plane_count] = new Mask;
        *plane[plane_count++] = p;
    } else if (typeid(p) == typeid(radio)) {
        plane[plane_count] = new Radio;
        *plane[plane_count++] = p;
    } else if (typeid(p) == typeid(reb)) {
        plane[plane_count] = new REB;
        *plane[plane_count++] = p;
    } else if (typeid(p) == typeid(scout)) {
        plane[plane_count] = new Scout;
        *plane[plane_count++] = p;
    } else throw std::logic_error("Plane should be derived class");
}

void Link::delete_plane(const int& num) {
    if (num < 1 || num > 4) throw std::logic_error("Invalid index");
    if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
    if (num > plane_count) throw std::logic_error("Count of planes is less than entered number");
    delete plane[num-1];
    plane[num-1] = nullptr;
    for (int i = num-1; i < plane_count-1; i++) {
        plane[i] = plane[i+1];
        s[i] = s[i+1];
        isSelectToGun[i] = isSelectToGun[i+1];
        isSelectToRocket[i] = isSelectToRocket[i+1];
    }
    plane[plane_count-1] = nullptr;
    plane_count--;
}

float Link::get_r() const {   //максимальный радиус обнаружения среди истребителей звена
    if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
    float r = plane[0]->get_r();
    for (int i = 1; i < plane_count; i++) {
        r = my_max(r,plane[i]->get_r());
    }
    return r;
}
int Link::get_REB_p() const {  //максимальный процент радиоэлектронной борьбы среди истребителей звена
    if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
    double p = plane[0]->get_REB_p();
    for (int i = 1; i < plane_count; i++) {
        p = my_max(p,plane[i]->get_REB_p());
    }
    return p;
}
float Link::get_reduce_r() const {  //минимальный коэффициент уменьшения собственного радиуса обнаружения среди истребителей звена
    if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
    float rate = plane[0]->get_reduce_r();
    for (int i = 1; i < plane_count; i++) {
        rate = my_max(rate,plane[i]->get_reduce_r());
    }
    return rate;
}
float Link::get_increase_r() const {  //максимальный коэффициент увеличения радиуса обнаружения противников среди истребителей звена
    if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
    float rate = plane[0]->get_increase_find_r();
    for (int i = 1; i < plane_count; i++) {
        rate = my_max(rate,plane[i]->get_increase_find_r());
    }
    return rate;
}
float Link::get_enemy_find_r(const Link& enemy_link) const {  //радиус обнаружения звеном звена противника
    if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
    if (enemy_link.get_plane_count() <= 0) throw std::logic_error("Enemy link is empty");
    float reduce_r = enemy_link.get_reduce_r(), increase_r = get_increase_r();

    if (reduce_r < 1) {
        reduce_r += (float)get_REB_p()/100;
    }
    if (reduce_r > 1) reduce_r = 1;

    if (increase_r > 1) {
        increase_r -= (float)(enemy_link.get_REB_p())/100;
    }
    if (increase_r < 1) increase_r = 1;

    return increase_r * reduce_r * enemy_link.get_r();
}

It Table::find(const int& id) {
    It it;
    for (it = vec.begin(); it != vec.end(); ++it) {
        if (it->id == id) return it;
    }
    return it;
}

Link& Table::get_Link(const int& id)  {
    It it;
    it = find(id);
    if (it == vec.end()) throw std::logic_error("There is no link with such id");
    return it->link;
}

int Table::get_Link_count() const {return vec.size();}

void Table::insert_Link(const Item &item) {
    It it;
    it = find(item.id);
    if (it != vec.end()) throw std::logic_error("Item with such id already exists");
    vec.push_back(item);
}

void Table::delete_Link(const int& id) {
    It it;
    it = find(id);
    if (it == vec.end()) throw std::logic_error("There is no link with such id");
    vec.erase(it);
}

void Mission::insert_plane_t(const int& id, const Plane& p) {
    Const_It it(t.find(id));
    if (it == t.get_end()) {
        Link link;
        link.insert_plane(p);
        Item item(id, link);
        t.insert_Link(item);
        return;
    }
    try {
        t.get_Link(id).insert_plane(p);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Mission::insert_plane_enemy_t(const int& id, const Plane& p) {
    Const_It it(enemy_t.find(id));
    if (it == enemy_t.get_end()) {
        Link link;
        link.insert_plane(p);
        Item item(id, link);
        enemy_t.insert_Link(item);
        return;
    }
    try {
        enemy_t.get_Link(id).insert_plane(p);
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Mission::delete_plane_t(const int& id, const int& num) {
    try {
        t.get_Link(id).delete_plane(num);
        if (t.get_Link(id).get_plane_count() == 0) {
            t.delete_Link(id);
        }
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Mission::delete_plane_enemy_t(const int& id, const int& num) {
    try {
        enemy_t.get_Link(id).delete_plane(num);
        if (enemy_t.get_Link(id).get_plane_count() == 0) {
            enemy_t.delete_Link(id);
        }
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Mission::gun_shoot_plane_in_enemy_t(const int& id1, const int& num1, const int& id2, const int& num2) {
    Plane *p = get_plane_t(id1, num1);
    if (!p) return;
    Plane *enemy_p = get_plane_enemy_t(id2, num2);
    if (!enemy_p) return;
    int REB_p = 0;
    try {
        REB_p = t.get_Link(id1).get_REB_p();
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    p->gun_shoot(*enemy_p, REB_p);
    if (enemy_p->get_cur_health() <= 0) delete_plane_enemy_t(id2, num2);
}

void Mission::gun_shoot_plane_in_t(const int& id2, const int& num2,const int& id1, const int& num1) {
    Plane *p = get_plane_t(id1, num1);
    if (!p) return;
    Plane *enemy_p = get_plane_enemy_t(id2, num2);
    if (!enemy_p) return;
    int REB_p = 0;
    try {
        REB_p = enemy_t.get_Link(id2).get_REB_p();
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    enemy_p->gun_shoot(*p, REB_p);
    if (p->get_cur_health() <= 0) delete_plane_t(id1, num1);
}

void Mission::rocket_shoot_plane_in_enemy_t(const int& id1, const int& num1, const int& id2, const int& num2) {
    Plane *p = get_plane_t(id1, num1);
    if (!p) return;
    Plane *enemy_p = get_plane_enemy_t(id2, num2);
    if (!enemy_p) return;
    int REB_p = 0;
    try {
        REB_p = t.get_Link(id1).get_REB_p();
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    p->rocket_shoot(*enemy_p, REB_p);
    if (enemy_p->get_cur_health() <= 0) delete_plane_enemy_t(id2, num2);
}

void Mission::rocket_shoot_plane_in_t(const int& id2, const int& num2,const int& id1, const int& num1) {
    Plane *p = get_plane_t(id1, num1);
    if (!p) return;
    Plane *enemy_p = get_plane_enemy_t(id2, num2);
    if (!enemy_p) return;
    int REB_p = 0;
    try {
        REB_p = enemy_t.get_Link(id2).get_REB_p();
    } catch (std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
    enemy_p->rocket_shoot(*p, REB_p);
    if (p->get_cur_health() <= 0) delete_plane_t(id1, num1);
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
