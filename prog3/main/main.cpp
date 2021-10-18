#include <iostream>
#include <prog3.h>

int main() {
    int c, key;
    char str[1000];
    Table *t = nullptr;
    do {
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Create default table" << std::endl;
        std::cout << "2. Create table and initialize k elements" << std::endl;
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
                t = new Table;
                break;

            case 2:
                std::cout << "***Create table and initialize k elements***" << std::endl;
                int k;
                std::cout << "Enter k:" << std::endl;
                k = get_int();
                Item* items;
                items = new Item[k];
                int count;
                count = k;
                try {
                    init_k_items(items, k, std::cin);
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    delete [] items;
                    break;
                }
                if (k < count) std::cout << "Not all data were added" << std::endl;
                delete t;
                try {
                    t = new Table(items, k);
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    delete [] items;
                    break;
                }
                delete [] items;
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
                if (!t)
                    t = new Table;
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
                try {
                    t->delete_item(key);
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    break;
                }
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
                try {
                    t->modify_info(key, str);
                } catch (const char *msg) {
                    std::cerr << msg << std::endl;
                    break;
                }
                break;

            case 7:
                std::cout << "***Show table***" << std::endl;
                if (!t) {
                    std::cout << "Table is empty" << std::endl;
                    break;
                }
                try {
                    t->show_table(std::cout);
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
