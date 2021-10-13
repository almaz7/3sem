#include <iostream>
#include <prog3.h>
using namespace STATIC;
int main() {
    int c, key;
    char str[LENGTH];
    Table *t = nullptr;
    do {
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Create default table" << std::endl;
        std::cout << "2. Create table and initialize n elements" << std::endl;
        std::cout << "3. Find element by key" << std::endl;
        std::cout << "4. Add new element" << std::endl;
        std::cout << "5. Delete element by key" << std::endl;
        std::cout << "6. Modify info of element by key" << std::endl;
        std::cout << "7. Show table" << std::endl;

        c = get_int();
        switch (c) {
            case 0:
                std::cout << "***Exit***" << std::endl;
                break;

            case 1:
                std::cout << "***Create default table***" << std::endl;
                delete t;
                try {
                    t = new Table;
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    break;
                }
                break;

            case 2:
                std::cout << "***Create table and initialize n elements***" << std::endl;
                int n;
                std::cout << "Enter n:" << std::endl;
                n = get_int();
                delete t;
                try {
                    t = new Table(n);
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    break;
                }
                break;

            case 3:
                std::cout << "***Find element by key***" << std::endl;
                if (!t) {
                    std::cout << "Table is empty" << std::endl;
                    break;
                }
                t->find_and_show();
                break;

            case 4:
                std::cout << "***Add new element***" << std::endl;
                if (!t) {
                    try {
                        t = new Table(1);
                    } catch (const char *msg) {
                        std::cerr << msg << std::endl;
                        break;
                    }
                    break;
                }

                std::cout << "Enter key:" << std::endl;
                key = get_int();
                std::cout << "Enter info:" << std::endl;
                std::cin >> str;
                try {
                    t->add_item(key, str);
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    break;
                }
                break;

            case 5:
                std::cout << "***Delete element by key***" << std::endl;
                if (!t) {
                    std::cout << "Table is empty" << std::endl;
                    break;
                }
                std::cout << "Enter key:" << std::endl;
                key = get_int();
                t->delete_item(key);
                break;

            case 6:
                std::cout << "***Modify info of element by key***" << std::endl;
                if (!t) {
                    std::cout << "Table is empty" << std::endl;
                    break;
                }
                std::cout << "Enter key:" << std::endl;
                key = get_int();
                std::cout << "Enter new info:" << std::endl;
                std::cin >> str;
                t->modify_info(key, str);
                break;

            case 7:
                std::cout << "***Show table***" << std::endl;
                if (!t) {
                    std::cout << "Table is empty" << std::endl;
                    break;
                }
                try {
                    t->show_table();
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    break;
                }
                break;

            default:
                std::cout << "You are wrong! Try again" << std::endl;
                break;
        }
    } while (c != 0);
    delete t;
    return 0;
}
