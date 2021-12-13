#ifndef PROG4_H
#define PROG4_H
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <SFML/Graphics.hpp>
#define my_max(x,y) x > y ? x : y


class Gun { //пушка
private:
    int dmg; //урон
    int p; //процент попаданий (<=100)
    float dist; //дальность стрельбы
    int rof; //скорострельность пушки

public:
    sf::Sprite s;
    bool isMove;
    Gun():dmg(3), p(90), dist(300.f), rof(10), isMove(false){}
    ~Gun() = default;
    int get_dmg() const {return dmg;}
    int get_p() const {return p;}
    float get_dist() const {return dist;}
    int get_rof() const {return rof;}

    void set_dmg(int dmg) noexcept {this->dmg = dmg;}
    void set_p(int p) noexcept {this->p = p;}
    void set_dist(float dist) noexcept {this->dist = dist;}
    void set_rof(int rof) noexcept {this->rof = rof;}
};

class Rocket { //ракетная установка
private:
    int dmg; //урон
    float dist; //дальность стрельбы
    int rof; //скорострельность ракетной установки
    int max_count; //максимальный боезапас
    int cur_count; //текущий боезапас

public:
    sf::Sprite s;
    bool isMove;
    Rocket():dmg(100), dist(1000.f), rof(1), max_count(2), cur_count(2), isMove(false) {}
    ~Rocket() = default;
    int get_dmg() const {return dmg;}
    float get_dist() const {return dist;}
    int get_rof() const {return rof;}
    int get_cur_count() const {return cur_count;}
    int get_max_count() const {return max_count;}

    void set_dmg(int dmg) noexcept {this->dmg = dmg;}
    void set_dist(float dist) noexcept {this->dist = dist;}
    void set_rof(int rof) noexcept {this->rof = rof;}
    void set_cur_count(int count) noexcept {this->cur_count = count;}
    void set_max_count(int count) noexcept {this->max_count = count;}
};

class Plane {
protected:
    int type; //модель истребителя
    int max_health; //маскимальная живучесть
    int cur_health; //текущая живучесть
    double speed; //скорость
    int gun_count; //количество пушек
    Rocket rocket;
    Gun gun;
    float x, y; //текущие координаты
    float r; //радиус обнаружения

public:
    Plane(): type(0), max_health(100), cur_health(100), speed(5),
        gun_count(1), x(0), y(0), r(100) {}
    Plane(float x, float y): type(0), max_health(100), cur_health(100),
        speed(5), gun_count(1), x(x), y(y), r(100) {}
    Plane(float x): type(0), max_health(100), cur_health(100), speed(5),
        gun_count(1), x(x), y(x), r(100){}
    virtual ~Plane() = default;
    float get_attack_r() const; //получить радиус атаки

    void get_gun_damage(const int& dmg, const int& p, const int& rof, const int& gun_count, const float& plane_reduce_hit) noexcept; //получить урон от пушки
    void get_rocket_damage(const int& dmg, const int& rof, int r_count, const int& REB_p) noexcept; //получить урон от ракеты
    void gun_shoot(Plane &plane, const int& REB_p) noexcept; //выстрелить из пушки
    void rocket_shoot(Plane &plane, const int& REB_p) noexcept; //выстрелить ракетой
    int get_type() const {return type;}
    int get_max_health() const {return max_health;}
    int get_cur_health() const {return cur_health;}
    float get_speed() const {return speed;}
    int get_gun_count() const {return gun_count;}
    Rocket get_rocket() const {return rocket;}
    Gun get_gun() const {return gun;};
    float get_x() const {return x;}
    float get_y() const {return y;}
    float get_r() const {return r;} //получить радиус обнаружения противником данного истребителя

    void set_type(int type) noexcept {this->type = type;}
    void set_max_health(int max_health) noexcept {this->max_health = max_health;}
    void set_cur_health(int cur_health) noexcept {this->cur_health = cur_health;}
    void set_speed(float speed) noexcept {this->speed = speed;}
    void set_gun_count(int gun_count) noexcept {this->gun_count = gun_count;}
    void set_rocket(Rocket rocket) noexcept {this->rocket = rocket;}
    void set_gun(Gun gun) noexcept {this->gun = gun;};
    void set_x(float x) noexcept {this->x = x;}
    void set_y(float y) noexcept {this->y = y;}
    void set_r(float r) noexcept {this->r = r;}

    virtual std::ostream& print(std::ostream &c) const {
        return c << "In Plane, (" << x << ","<< y << "), health = " << cur_health << ", find_r = "
                 << get_r() << ", rocket_count = " << rocket.get_cur_count();
    }
    friend std::ostream& operator << (std::ostream &c, const Plane &p) {
        return p.print(c);
    }

    virtual int get_cur_pro_count() const {return 0;}
    virtual int get_max_pro_count() const {return 0;}
    virtual void set_cur_pro_count(int count) noexcept {}
    virtual void set_max_pro_count(int count) noexcept {}
    virtual float get_reduce_hit() const {return 1.f;}
    virtual float get_reduce_r() const {return 1.f;}
    virtual void set_reduce_hit(float rate) noexcept {}
    virtual void set_reduce_r(float rate) noexcept {}
    virtual float get_increase_find_r() const {return 1.f;}
    virtual void set_increase_find_r(float rate) noexcept {}
    virtual int get_REB_p() const {return 0;}
    virtual void set_REB_p(int p) noexcept {}
};

class PRO: public Plane { //истребитель ПРО
private:
    int cur_pro_count; //количество зарядов ПРО (противоракетной обороны)
    int max_pro_count; //максимальное количество зарядов ПРО

public:
    PRO():Plane(), cur_pro_count(4), max_pro_count(4) {type = 1;}
    PRO(double x, double y): Plane(x,y), cur_pro_count(4), max_pro_count(4) {type = 1;}
    PRO(double x): Plane(x), cur_pro_count(4), max_pro_count(4) {type = 1;}
    ~PRO() = default;
    int get_cur_pro_count() const {return cur_pro_count;}
    int get_max_pro_count() const {return max_pro_count;}
    void set_cur_pro_count(int count) noexcept {this->cur_pro_count = count;}
    void set_max_pro_count(int count) noexcept {this->max_pro_count = count;}

    std::ostream& print(std::ostream &c) const {
        return c << "Type \"PRO\", (" << x << ","<< y << "), health = " << cur_health << ", find_r = "
                 << get_r() << ", rocket_count = " << rocket.get_cur_count() << ", pro_count = " << get_cur_pro_count();
    }
    friend std::ostream& operator << (std::ostream &c, const PRO &p) {
        return p.print(c);
    }
};

class Mask: public Plane { //истребитель маскировки
private:
    float reduce_hit; //коэффициент уменьшения процента попаданий из пушки (<= 1)
    float reduce_r; //коэффициент уменьшения радиуса обнаружения (<= 1)

public:
    Mask(): Plane(), reduce_hit(0.5f), reduce_r(0.5f) {type = 2;}
    Mask(float x, float y): Plane(x,y), reduce_hit(0.5f), reduce_r(0.5f) {type = 2;}
    Mask(float x): Plane(x), reduce_hit(0.5f), reduce_r(0.5f) {type = 2;}
    ~Mask() = default;

    float get_reduce_hit() const {return reduce_hit;}
    float get_reduce_r() const {return reduce_r;}
    void set_reduce_hit(float rate) noexcept {this->reduce_hit = rate;}
    void set_reduce_r(float rate) noexcept {this->reduce_r = rate;}

    std::ostream& print(std::ostream &c) const {
        return c << "Type \"Mask\", (" << x << ","<< y << "), health = " << cur_health << ", find_r = "
                 << get_r() << ", rocket_count = " << rocket.get_cur_count() << ", reduce_hit = "
                 << get_reduce_hit() << ", reduce_r = " << get_reduce_r();
    }
    friend std::ostream& operator << (std::ostream &c, const Mask &p) {
        return p.print(c);
    }
};

class Radio: public Plane { //истребитель радиообнаружения
private:
    float increase_find_r; //коэффициент игнорирования маскировки (увеличения радиуса обнаружения) (> 1)

public:
    Radio(): Plane(), increase_find_r(2.f) {type = 3;}
    Radio(float x, float y): Plane(x,y), increase_find_r(2.f) {type = 3;}
    Radio(float x): Plane(x), increase_find_r(2.f) {type = 3;}
    ~Radio() = default;
    float get_increase_find_r() const {return increase_find_r;}
    void set_increase_find_r(float rate) noexcept {this->increase_find_r = rate;}

    std::ostream& print(std::ostream &c) const {
        return c << "Type \"Radio\", (" << x << ","<< y << "), health = " << cur_health << ", find_r = "
                 << get_r() << ", rocket_count = " << rocket.get_cur_count() << ", increase_r = " << get_increase_find_r();
    }
    friend std::ostream& operator << (std::ostream &c, const Radio &p) {
        return p.print(c);
    }
};

class REB: public Plane { //истребитель РЭБ (радиоэлектронной борьбы)
private:
    int REB_p; //процент(вероятность) подавления ПРО, маскировки, радиообнаружения (<= 100)

public:
    REB(): Plane(), REB_p(40) {type = 4;}
    REB(float x, float y): Plane(x,y), REB_p(40) {type = 4;}
    REB(float x): Plane(x), REB_p(40) {type = 4;}
    ~REB() = default;

    int get_REB_p() const {return REB_p;}
    void set_REB_p(int p) noexcept {this->REB_p = p;}

    std::ostream& print(std::ostream &c) const {
        return c << "Type \"REB\", (" << x << ","<< y << "), health = " << cur_health << ", find_r = "
                 << get_r() << ", rocket_count = " << rocket.get_cur_count() << ", REB_p = " << get_REB_p();
    }
    friend std::ostream& operator << (std::ostream &c, const REB &p) {
        return p.print(c);
    }
};

class Scout: public Plane { //истребитель разведки
private:
    float reduce_r; //коэффициент уменьшения собственного радиуса обнаружения (< 1)
    float increase_enemy_find_r; //коэффициент увеличения радиуса обнаружения вражеской техники (> 1)

public:
    Scout(): Plane(), reduce_r(0.5f), increase_enemy_find_r(2.f) {type = 5;}
    Scout(float x, float y): Plane(x,y), reduce_r(0.5f), increase_enemy_find_r(2.f) {type = 5;}
    Scout(float x): Plane(x), reduce_r(0.5f), increase_enemy_find_r(2.f) {type = 5;}
    ~Scout() = default;

    float get_reduce_r() const {return reduce_r;}
    float get_increase_find_r() const {return increase_enemy_find_r;}
    void set_reduce_r(float rate) noexcept {this->reduce_r = rate;}
    void set_increase_find_r(float rate) noexcept {this->increase_enemy_find_r = rate;}

    std::ostream& print(std::ostream &c) const {
        return c << "Type \"Scout\", (" << x << ","<< y << "), health = " << cur_health << ", find_r = "
                 << get_r() << ", rocket_count = " << rocket.get_cur_count() << ", reduce_r = "
                 << get_reduce_r() << ", increase_r = " << get_increase_find_r();
    }
    friend std::ostream& operator << (std::ostream &c, const Scout &p) {
        return p.print(c);
    }
};


///Класс Звена Истребителей
class Link { //звено истребителей
private:
    Plane **plane;
    int plane_count; //количество истребителей в звене (<= 4)
    int command; //текущий приказ //0 - сохранять позицию //1 - перемещаться в точку //2 - атака
    float x, y; //координаты звена

public:
    sf::Sprite s[4];
    bool isSelectToMove;
    bool isSelectToGun[4];
    bool isSelectToRocket[4];
    bool isMove;
    Link(): plane_count(0), plane(nullptr), command(0), x(0.f), y(0.f), isSelectToMove(false), isMove(false) {
        for (int i = 0; i < 4; i++) {
            isSelectToGun[i] = false;
            isSelectToRocket[i] = false;
        }
    }
/*!
 *  @brief конструктор для звена
 *  @param p указатель на массив указателей на самолеты; в случае пустого указателя будет выброшено
 *  исключения типа std::logic_error
 *  @param count количество самолетов; в случае невалидного количества самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    Link(Plane **p, const int& count);
/*!
 *  @brief конструктор копирования
 *  @param l звено
 */
    Link(const Link &l);
/*!
 *  @brief копирующий оператор присваивания
 *  @param l звено
 *  @return ссылка на звено
 */
    Link& operator=(const Link &l);
    ~Link() {
        for (int i = 0; i < plane_count; i++) {
            delete plane[i];
            plane[i] = nullptr;
        }
        plane_count = 0;
        delete [] plane;
        plane = nullptr;
    }

/*!
 *  @brief добавляет самолет в звено
 *  @param p самолет, который необходимо добавить в звено; в случае если количество самолетов
 *  в звене равно 4, самолет добавлен не будет
 */
    void insert_plane(const Plane& p);
/*!
 *  @brief удаляет самолет из звена
 *  @param num порядковый номер самолета в звене; в случае невалидного номера или отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    void delete_plane(const int& num);
/*!
 *  @brief получение максимальный радиуса обнаружения среди истребителей звена
 *  @return double максимальный радиус обнаружения среди истребителей звена; в случае отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    float get_r() const;   //максимальный радиус обнаружения среди истребителей звена
/*!
 *  @brief получение максимального процента радиоэлектронной борьбы среди истребителей звена
 *  @return int максимальный процент радиоэлектронной борьбы среди истребителей звена; в случае отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    int get_REB_p() const;  //максимальный процент радиоэлектронной борьбы среди истребителей звена
/*!
 *  @brief получение минимального коэффициента уменьшения собственного радиуса обнаружения среди истребителей звена
 *  @return double минимальный коэффициент уменьшения собственного радиуса обнаружения среди истребителей звена; в случае отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    float get_reduce_r() const;  //минимальный коэффициент уменьшения собственного радиуса обнаружения среди истребителей звена
/*!
 *  @brief получение максимального коэффициента увеличения радиуса обнаружения противников среди истребителей звена
 *  @return double максимальный коэффициент увеличения радиуса обнаружения противников среди истребителей звена; в случае отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    float get_increase_r() const;  //максимальный коэффициент увеличения радиуса обнаружения противников среди истребителей звена
/*!
 *  @brief получение радиуса обнаружения звеном звена противника
 *  @param enemy_link вражеское звено
 *  @return double радиус обнаружения звеном звена противника; в случае отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 */
    float get_enemy_find_r(const Link& enemy_link) const;  //радиус обнаружения звеном звена противника
/*!
 *  @brief получение указателя на самолет в звене
 *  @param num порядковый номер самолета в звене; в случае невалидного номера или отсутствия в звене самолетов
 *  будет выброшено исключение типа std::logic_error
 *  @return Plane* указатель на самолет в звене
 */
    Plane* get_plane(const int& num) {
        if (num < 1 || num > 4) throw std::logic_error("Invalid index");
        if (plane_count <= 0 || !plane) throw std::logic_error("Link is empty");
        if (num > plane_count) throw std::logic_error("Count of planes is less than entered number");
        return plane[num-1];
    }
/*!
 *  @brief нахождение количества самолетов в звене
 *  @return int количество самолетов в звене
 */
    int get_plane_count() const {return plane_count;}
/*!
 *  @brief получение координаты x звена
 *  @return double координата x
 */
    float get_x() const {return x;}
/*!
 *  @brief получение координаты y звена
 *  @return double координата y
 */
    float get_y() const {return y;}
/*!
 *  @brief получение текущей команды для звена
 *  @return int: "0" - сохранять позицию, "1" - перемещаться в точку, "2" - атака
 */
    int get_command() const {return command;}
/*!
 *  @brief задание координаты x для звена
 *  @param x координата x
 */
    void set_x(float x) noexcept {this->x = x;}
/*!
 *  @brief задание координаты y для звена
 *  @param y координата y
 */
    void set_y(float y) noexcept {this->y = y;}
/*!
 *  @brief задание текущей команды для звена
 *  @param c: "0" - сохранять позицию, "1" - перемещаться в точку, "2" - атака
 */
    void set_command(int c) noexcept {this->command = c;}
/*!
 *  @brief дружественный оператор вывода в поток данных звена
 *  @param c ссылка на поток для вывода данных
 *  @param link звено
 *  @return std::ostream& ссылка на обновленный поток
 */
    friend std::ostream& operator << (std::ostream &c, const Link &link) noexcept {
        if (link.plane_count <= 0 || !link.plane) return c << "Link is empty\n";
        c << "Link description: r = "<< link.get_r() << ", REB_p = " << link.get_REB_p()
          << ", reduce_r = " << link.get_reduce_r() << ", increase_r = " << link.get_increase_r() << '\n';
        for (int i = 0; i < link.plane_count; i++) {
            c << "Plane #" << i+1 << ": " << *link.plane[i] << '\n';
        }
        return c;
    }
};

struct Item {
    int id;
    Link link;
    Item() = default;
    Item(const int& i, const Link& l): id(i), link(l) {}
    Item(const Item& item): id(item.id), link(item.link) {}
};


typedef std::vector<Item>::iterator It;
typedef std::vector<Item>::const_iterator Const_It;
class Table {
private:
    std::vector<Item> vec;
public:
    Table() = default;
    Table(const Table &t): vec(t.vec) {}
    Table(const std::vector<Item> &v): vec(v) {}
    ~Table() = default;
    It find(const int& id);
    Const_It get_end() const {return vec.end();}
    It get_begin() {return vec.begin();}
    Link& get_Link(const int& id);
    int get_Link_count() const;
    void insert_Link(const Item &item);
    void delete_Link(const int& id);
    friend std::ostream& operator << (std::ostream &c, Table &t) noexcept {
        if (t.vec.begin() == t.vec.end()) {
            c << "Table is empty\n";
            return c;
        }
        for (It it = t.vec.begin(); it != t.vec.end(); it++) {
            c << "ID: " << it->id << std::endl;
            c << it->link;
        }
        return c;
    }
};

class Mission {
private:
    Table t;
    Table enemy_t;
public:
    Mission() = default;
    ~Mission() = default;
    It get_begin_t() {return t.get_begin();}
    Const_It get_end_t() {return t.get_end();}
    It get_begin_enemy_t() {return enemy_t.get_begin();}
    Const_It get_end_enemy_t() {return enemy_t.get_end();}
    Plane* get_plane_t(const int& id, const int& num) {
        Plane *p = nullptr;
        try {
            p = t.get_Link(id).get_plane(num);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
        return p;
    }

    Plane* get_plane_enemy_t(const int& id, const int& num) {
        Plane *p = nullptr;
        try {
            p = enemy_t.get_Link(id).get_plane(num);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
        return p;
    }

    Link& get_link_t(const int& id) {
        try {
            return t.get_Link(id);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
            throw std::logic_error(e);
        }
    }

    Link& get_link_enemy_t(const int& id) {
        try {
            return enemy_t.get_Link(id);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
            throw std::logic_error(e);
        }
    }

    int get_Link_count_t() const {return t.get_Link_count();}
    int get_Link_count_enemy_t() const {return enemy_t.get_Link_count();}

    void insert_Link_t(Item &item) {
        try {
            t.insert_Link(item);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    void insert_Link_enemy_t(Item &item) {
        try {
            enemy_t.insert_Link(item);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    void delete_Link_t(const int& id) {
        try {
            t.delete_Link(id);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    void delete_Link_enemy_t(const int& id) {
        try {
            enemy_t.delete_Link(id);
        } catch (std::logic_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    void insert_plane_t(const int& id, const Plane& p);
    void insert_plane_enemy_t(const int& id, const Plane& p);
    void delete_plane_t(const int& id, const int& num);
    void delete_plane_enemy_t(const int& id, const int& num);

    void gun_shoot_plane_in_enemy_t(const int& id1, const int& num1, const int& id2, const int& num2);
    void gun_shoot_plane_in_t(const int& id2, const int& num2,const int& id1, const int& num1);
    void rocket_shoot_plane_in_enemy_t(const int& id1, const int& num1, const int& id2, const int& num2);
    void rocket_shoot_plane_in_t(const int& id2, const int& num2,const int& id1, const int& num1);

    friend std::ostream& operator << (std::ostream &c, Mission &m) noexcept {
        c << "\n***Table***\n";
        c << m.t;
        c << "***Enemy table***\n";
        c << m.enemy_t;
        return c;
    }
};
#endif