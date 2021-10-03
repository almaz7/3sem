#include <iostream>
#include <prog2.h>

int main() {
    int c;
    double t;
    Hypo h;
    do {
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Create hypocycloid" << std::endl;
        std::cout << "2. Change parameters of hypocycloid" << std::endl;
        std::cout << "3. Get coordinates of hypocycloid point" << std::endl;
        std::cout << "4. Get circle radii" << std::endl;
        std::cout << "5. Get radius of curvature" << std::endl;
        std::cout << "6. Get type of hypocycloid" << std::endl;
        std::cout << "7. Get sectorial square" << std::endl;

        c = get_int();
        switch (c) {
            case 0:
                std::cout << "***Exit***" << std::endl;
                break;

            case 1:
                std::cout << "***Create hypocycloid***" << std::endl;
                if (create_hypocycloid(h) == 1) return 1;
                break;

            case 2:
                std::cout << "***Change parameters of hypocycloid***" << std::endl;
                if (change_parameters(h) == 1) return 1;
                break;

            case 3:
                std::cout << "***Get coordinates of hypocycloid point***" << std::endl;
                std::cout << "Enter beam angle in radians:" << std::endl;
                t = get_double();
                print_x_y(h,t);
                break;

            case 4:
                std::cout << "***Get circle radii***" << std::endl;
                print_r_R(h);
                break;

            case 5:
                std::cout << "***Get radius of curvature***" << std::endl;
                std::cout << "Enter beam angle in radians:" << std::endl;
                t = get_double();
                print_rad_curv(h,t);
                break;

            case 6:
                std::cout << "***Get type of hypocycloid***" << std::endl;
                print_type(h);
                break;

            case 7:
                std::cout << "***Get sectorial square***" << std::endl;
                std::cout << "Enter beam angle in radians:" << std::endl;
                t = get_double();
                print_square(h,t);
                break;

            default:
                std::cout << "You are wrong! Try again" << std::endl;
                break;
        }
    } while (c != 0);
    return 0;
}
