#include <iostream>
#include <prog2.h>

int main() {
    int c;
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
                create_hypocycloid(h);
                break;

            case 2:
                std::cout << "***Change parameters of hypocycloid***" << std::endl;
                change_parameters(h);
                break;

            case 3:
                std::cout << "***Get coordinates of hypocycloid point***" << std::endl;
                print_x_y(h);
                break;

            case 4:
                std::cout << "***Get circle radii***" << std::endl;
                print_r_R(h);
                break;

            case 5:
                std::cout << "***Get radius of curvature***" << std::endl;
                print_rad_curv(h);
                break;

            case 6:
                std::cout << "***Get type of hypocycloid***" << std::endl;
                print_type(h);
                break;

            case 7:
                std::cout << "***Get sectorial square***" << std::endl;
                print_square(h);
                break;

            default:
                std::cout << "You are wrong! Try again" << std::endl;
                break;
        }
    } while (c != 0);
    return 0;
}
