#ifndef PROG2_H
#define PROG2_H
//гипоциклоида
class Hypo {
    private:
        double r; //радиус порождающего (внутреннего) круга
        double R; //радиус направляющей (внешнего круга)
        double d; //расстояние от центра порождающего круга до точки гипоциклоиды
        void check() const;
    public:
        Hypo(): r(1), R(1), d(1){check();}
        Hypo(double r, double R, double d): r(r), R(R), d(d){check();}
        ~Hypo()= default;

        double get_r() const {return r;}
        double get_R() const {return R;}
        double get_d() const {return d;}

        void set_r(double r) {
            this->r = r;
            check();
        }

        void set_R(double R) {
            this->R = R;
            check();
        }

        void set_d(double d) {
            this->d = d;
            check();
        }

        double get_x(double t) const; //координаты х и у
        double get_y(double t) const;
        int get_type() const; //тип гипоциклоиды
        double get_rad_curv(double t) const; //радиус кривизны
        double get_square(double t) const; //секториальная площадь
};

void print_type(Hypo &h) noexcept;
void print_x_y(Hypo &h, double t) noexcept;
void print_rad_curv(Hypo &h, double t) noexcept;
void print_square(Hypo &h, double t) noexcept;
void print_r_R(Hypo &h) noexcept;
bool correct_get_int(int &a) noexcept;
int get_int() noexcept;
bool correct_get_double(double &a) noexcept;
double get_double() noexcept;
int create_hypocycloid(Hypo &h);
int change_parameters(Hypo &h);
#endif
