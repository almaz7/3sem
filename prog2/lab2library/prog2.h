#ifndef PROG2_H
#define PROG2_H
//гипоциклоида
class Hypo {
    private:
        double r; //радиус порождающего (внутреннего) круга
        double R; //радиус направляющей (внешнего круга)
        double d; //расстояние от центра порождающего круга до точки гипоциклоиды
        double t; //угол, является изменяющимся параметром

    public:
        Hypo(): r(0), R(0), d(0), t(0){}
        Hypo(double r, double R, double d, double t): r(r), R(R), d(d), t(t){}
        ~Hypo()= default;

        double get_r() const {return r;}
        double get_R() const {return R;}
        double get_t() const {return t;}
        double get_d() const {return d;}

        void set_r(double r) {
            this->r = r;
        }

        void set_R(double R) {
            this->R = R;
        }

        void set_t(double t) {
            this->t = t;
        }

        void set_d(double d) {
            this->d = d;
        }

        double get_x() const; //координаты х и у
        double get_y() const;
        int get_type() const; //тип гипоциклоиды
        double get_rad_curv() const; //радиус кривизны
        double get_square() const; //секториальная площадь
};

void print_type(Hypo &h);
void print_x_y(Hypo &h);
void print_rad_curv(Hypo &h);
void print_square(Hypo &h);
void print_r_R(Hypo &h);
bool correct_get_int(int &a);
int get_int();
int create_hypocycloid(Hypo &h);
int change_parameters(Hypo &h);
#endif
