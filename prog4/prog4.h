#ifndef PROG4_H
#define PROG4_H
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <stdexcept>
class Gun { //пушка
    private:
    int dmg; //урон
    double p; //процент попаданий
    double dist; //дальность стрельбы
    int rof; //скорострельность пушки

    public:
    Gun():dmg(1), p(0.7), dist(10), rof(10){}
    ~Gun() = default;
    void shoot() const; //выстрелить
    int get_dmg() const {return dmg;}
    double get_p() const {return p;}
    double get_dist() const {return dist;}
    int get_rof() const {return rof;}

    void set_dmg(int dmg) noexcept {this->dmg = dmg;}
    void set_p(double p) noexcept {this->p = p;}
    void set_dist(double dist) noexcept {this->dist = dist;}
    void set_rof(int rof) noexcept {this->rof = rof;}
};

class Rocket { //ракетная установка
    private:
    int dmg; //урон
    double dist; //дальность стрельбы
    int rof; //скорострельность ракетной установки
    int max_count; //максимальный боезапас
    int cur_count; //текущий боезапас

    public:
    Rocket():dmg(100), dist(50), rof(1), max_count(2), cur_count(2){}
    ~Rocket() = default;
    void shoot() noexcept; //выстрелить
    int get_dmg() const {return dmg;}
    double get_dist() const {return dist;}
    int get_rof() const {return rof;}
    int get_cur_count() const {return cur_count;}
    int get_max_count() const {return max_count;}

    void set_dmg(int dmg) noexcept {this->dmg = dmg;}
    void set_dist(double dist) noexcept {this->dist = dist;}
    void set_rof(int rof) noexcept {this->rof = rof;}
    void set_cur_count(int count) noexcept {this->cur_count = count;}
    void set_max_count(int count) noexcept {this->max_count = count;}
};

class Plane {
    private:
    int type; //модель истребителя
    int max_health; //маскимальная живучесть
    int cur_health; //текущая живучесть
    double speed; //скорость
    int gun_count; //количество пушек
    Rocket rocket;
    Gun gun;
    double x, y; //текущие координаты
    double r; //радиус обнаружения

    public:
    Plane() {}
    virtual ~Plane() {}
    double get_attack_r() const; //получить радиус атаки
    double get_find_r() const; //получить радиус обнаружения
    void get_gun_damage() noexcept; //получить урон от пушки
    void get_rocket_damage() noexcept; //получить урон от ракеты
    void gun_shoot(); //выстрелить из пушки
    void rocket_shoot(); //выстрелить ракетой
    int get_type() const {return type;}
    int get_max_health() const {return max_health;}
    int get_cur_health() const {return cur_health;}
    double get_speed() const {return speed;}
    int get_gun_count() const {return gun_count;}
    Rocket get_rocket() const {return rocket;}
    Gun get_gun() const {return gun;};
    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_r() const {return r;}

    void set_type(int type) noexcept {this->type = type;}
    void set_max_health(int max_health) noexcept {this->max_health = max_health;}
    void set_cur_health(int cur_health) noexcept {this->cur_health = cur_health;}
    void set_speed(double speed) noexcept {this->speed = speed;}
    void set_gun_count(int gun_count) noexcept {this->gun_count = gun_count;}
    void set_rocket(Rocket rocket) noexcept {this->rocket = rocket;}
    void set_gun(Gun gun) noexcept {this->gun = gun;};
    void set_x(double x) noexcept {this->x = x;}
    void set_y(double y) noexcept {this->y = y;}
    void set_r(double r) noexcept {this->r = r;}

    virtual int get_cur_pro_count() const {return 0;}
    virtual int get_max_pro_count() const {return 0;}
    virtual void set_cur_pro_count(int count) noexcept {}
    virtual void set_max_pro_count(int count) noexcept {}
    virtual double get_reduce_hit() const {return 1;}
    virtual double get_reduce_r() const {return 1;}
    virtual void set_reduce_hit(double rate) noexcept {}
    virtual void set_reduce_r(double rate) noexcept {}
    virtual double get_increase_find_r() const {return 1;}
    virtual void set_increase_find_r(double rate) noexcept {}
    virtual double get_REB_rate() const {return 1;}
    virtual void set_REB_rate(double rate) noexcept {}
};

class PRO: public Plane { //истребитель ПРО
    private:
    int cur_pro_count; //количество зарядов ПРО (противоракетной обороны)
    int max_pro_count; //максимальное количество зарядов ПРО

    public:
    PRO() {}
    ~PRO() {}
    int get_cur_pro_count() const {return cur_pro_count;}
    int get_max_pro_count() const {return max_pro_count;}
    void set_cur_pro_count(int count) noexcept {this->cur_pro_count = count;}
    void set_max_pro_count(int count) noexcept {this->max_pro_count = count;}
};

class Mask: public Plane { //истребитель маскировки
    private:
    double reduce_hit; //коэффициент уменьшения процента попаданий из пушки (< 1)
    double reduce_r; //коэффициент уменьшения радиуса обнаружения (< 1)

    public:
    Mask() {}
    ~Mask() {}
    double get_reduce_hit() const {return reduce_hit;}
    double get_reduce_r() const {return reduce_r;}
    void set_reduce_hit(double rate) noexcept {this->reduce_hit = rate;}
    void set_reduce_r(double rate) noexcept {this->reduce_r = rate;}
};

class Radio: public Plane { //истребитель радиообнаружения
    private:
    double increase_find_r; //коэффициент игнорирования маскировки (увеличения радиуса обнаружения) (> 1)

    public:
    Radio() {}
    ~Radio() {}
    double get_increase_find_r() const {return increase_find_r;}
    void set_increase_find_r(double rate) noexcept {this->increase_find_r = rate;}
};

class REB: public Plane { //истребитель РЭБ (радиоэлектронной борьбы)
    private:
    double REB_rate; //коэффициент подавления ПРО, маскировки, радиообнаружения (< 1)

    public:
    REB() {}
    ~REB() {}
    double get_REB_rate() const {return REB_rate;}
    void set_REB_rate(double rate) noexcept {this->REB_rate = rate;}
};

class Scout: public Plane { //истребитель разведки
    private:
    double reduce_r; //коэффициент уменьшения собственного радиуса обнаружения (< 1)
    double increase_find_r; //коэффициент увеличения радиуса обнаружения вражеской техники (> 1)

    public:
    Scout() {}
    ~Scout() {}
    double get_reduce_r() const {return reduce_r;}
    double get_increase_find_r() const {return increase_find_r;}
    void set_reduce_r(double rate) noexcept {this->reduce_r = rate;}
    void set_increase_find_r(double rate) noexcept {this->increase_find_r = rate;}
};

class Link { //звено истребителей
    private:
    Plane **plane;
    int plane_count; //количество истребителей в звене (<= 4)
    int command; //текущий приказ //0 - сохранять позицию //1 - перемещаться в точку //2 - атака
    double x, y; //координаты звена

    public:
    Link(): plane_count(0), plane(nullptr), command(0), x(0), y(0) {}
    Link(Plane **p, const int& count) {
        if (count < 0) throw std::logic_error("Count of planes in Link can't be less than 0");
        if (count > 4) throw std::logic_error("Count of planes in Link can't be more than 4");
        plane = p;
        plane_count = count;
    }
    Link(const Link &l);
    ~Link() {
        for (int i = 0; i < plane_count; i++) {
            delete plane[i];
            plane[i] = nullptr;
        }
        plane_count = 0;
        delete [] plane;
        plane = nullptr;
    }
    void insert_plane(const Plane& p);
    void delete_plane(const int& i);
    int get_plane_count() {return plane_count;}
    double get_x() const {return x;}
    double get_y() const {return y;}
    int get_command() const {return command;}
    Plane **get_plane() const {return plane;}
    void set_x(double x) noexcept {this->x = x;}
    void set_y(double y) noexcept {this->y = y;}
    void set_command(int c) noexcept {this->command = c;}
};

struct Item {
    int id;
    Link link;
    Item() {}
    Item(const int& i, const Link& l): id(i), link(l) {}
    Item(const Item& item): id(item.id), link(item.link){}
};

typedef std::vector<Item>::iterator It;
typedef std::vector<Item>::const_iterator Const_It;
class Table {
private:
    std::vector<Item> vec;
public:
    Table() {}
    Table(const Table &t): vec(t.vec) {}
    Table(const std::vector<Item> v): vec(v) {}
    ~Table() = default;
    Const_It find(const int& id) const;
    Link& get_Link(const int& id);
    int get_Link_count() const;
    void insert_Link(Item &item);
    void delete_Link(const int& id);
};



#endif
