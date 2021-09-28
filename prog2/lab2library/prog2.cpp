#include <iostream>
#include <cmath>
#include "prog2.h"

double Hypo::get_x() const {
    return (R - r) * cos(t) + d * cos(t * (R - r) / r);
}

double Hypo::get_y() const {
    return (R - r) * sin(t) - d * sin(t * (R - r) / r);
}

int Hypo::get_type() const {
    if (fabs(d - r) < (d / 100000)) { //то есть d == r
        return 0;       //обыкновенная
    } else if ((r - d) > (r / 100000)) {
        return -1;      //укороченная
    } else if ((d - r) > (d / 100000)) {
        return 1;
    } else return 2; //error
}

double Hypo::get_rad_curv() const {
    return fabs((R - r) * pow(r*r + d*d - 2*d*r*cos(R*t/r), 1.5) /
    fabs(-r*r*r + d*d*(R-r) - d*r*(R - 2*r)*cos(R*t/r)));
}

double Hypo::get_square() const {
    return fabs((R - r) / 2 * ((R - r - d*d/r)*t + d*(R - 2*r)/R*sin(R*t/r)));
}

void print_type(Hypo &h) {
    int s = h.get_type();
    if (s == 2) std::cout << "Error!!!" << std::endl;
    if (s == -1) std::cout << "Type of hypocycloid: \"shortened\"" << std::endl; //укороченная
    if (s == 0) std::cout << "Type of hypocycloid: \"usual\"" << std::endl; //обыкновенная
    if (s == 1) std::cout << "Type of hypocycloid: \"elongate\"" << std::endl; //удлинненная
}

void print_x_y(Hypo &h) {
    double x, y;
    x = h.get_x();
    y = h.get_y();
    std::cout << "Coordinates:" << std::endl;
    std::cout << "X: " << x << std::endl;
    std::cout << "Y: " << y << std::endl;
}

void print_rad_curv(Hypo &h) {
    double rad = h.get_rad_curv();
    std::cout << "Radius of curvature: " << rad << std::endl; //радиус кривизны
}

void print_square(Hypo &h) {
    double s = h.get_square();
    std::cout << "Sectorial square: " << s << std::endl; //секториальная площадь
}

void print_r_R(Hypo &h) {
    double r = h.get_r();
    double R = h.get_R();
    std::cout << "Circle radii:" << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "R: " << R << std::endl;
}

bool correct_get_int(int &a) {
    std::cin >> a;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

int get_int() {
    int num;
    while (true) {
        if (correct_get_int(num))
            break;
        std::cout << "Wrong number" << std::endl;
    }
    return num;
}

bool correct_get_double(double &a) {
    std::cin >> a;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

double get_double() {
    double num;
    while (true) {
        if (correct_get_double(num))
            break;
        std::cout << "Wrong number" << std::endl;
    }
    return num;
}

int create_hypocycloid(Hypo &h) {
    double r, R, t, d;
    const char *s = "";
    std::cout << "Enter radius of generating circle (r > 0)" << std::endl;
    do {
        std::cout << s << std::endl;
        r = get_double();
        s = "You are wrong! Try again";
    } while (r <= 0);
    s = "";

    std::cout << "Enter radius of guide circle (R > 0)" << std::endl;
    do {
        std::cout << s << std::endl;
        R = get_double();
        s = "You are wrong! Try again";
    } while (R <= 0);
    s = "";

    std::cout << "Enter distance from point on hypocycloid to centre of generating circle (d >= 0)" << std::endl;
    do {
        std::cout << s << std::endl;
        d = get_double();
        s = "You are wrong! Try again";
    } while (d < 0);

    std::cout << "Enter beam angle" << std::endl;
    t = get_double();

    h.set_r(r); h.set_R(R); h.set_d(d); h.set_t(t);
    return 0;
}

int change_parameters(Hypo &h) {
    int c;
    double r, t, d, R;
    const char *s = "";
    do {
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Change r" << std::endl;
        std::cout << "2. Change R" << std::endl;
        std::cout << "3. Change d (distance)" << std::endl;
        std::cout << "4. Change t (angle)" << std::endl;
        c = get_int();
        switch (c) {
            case 0:
                std::cout << "***Exit***" << std::endl;
                break;

            case 1:
                std::cout << "***Change r***" << std::endl;
                std::cout << "Enter radius of generating circle (r > 0)" << std::endl;
                do {
                    std::cout << s << std::endl;
                    r = get_double();
                    s = "You are wrong! Try again";
                } while (r <= 0);
                s = "";
                h.set_r(r);
                break;

            case 2:
                std::cout << "***Change R***" << std::endl;
                std::cout << "Enter radius of guide circle (R > 0)" << std::endl;
                do {
                    std::cout << s << std::endl;
                    R = get_double();
                    s = "You are wrong! Try again";
                } while (R <= 0);
                s = "";
                h.set_R(R);
                break;

            case 3:
                std::cout << "***Change d (distance)***" << std::endl;
                std::cout << "Enter distance from point on hypocycloid to centre of generating circle (d >= 0)" << std::endl;
                do {
                    std::cout << s << std::endl;
                    d = get_double();
                    s = "You are wrong! Try again";
                } while (d < 0);
                s = "";
                h.set_d(d);
                break;

            case 4:
                std::cout << "***Change t (angle)***" << std::endl;
                std::cout << "Enter beam angle" << std::endl;
                t = get_double();
                h.set_t(t);
                break;

            default:
                std::cout << "You are wrong! Try again" << std::endl;
                break;
        }
    } while (c != 0);
    return 0;
}