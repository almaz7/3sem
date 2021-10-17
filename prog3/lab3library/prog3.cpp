#include <iostream>
#include "prog3.h"
using namespace STATIC;
Table::Table(Item *item, unsigned int k) {
    if (k < 1)
        throw "Current table size can't be less than 1";
    this->n = 0;
    int i, key, length = item->LENGTH;
    char* str = new char[length];
    for (i = 0; i < k; i++) {
        std::cout << "Enter key:" << std::endl;
        key = item[i].key;
        strcat(str, item[i].str);
        try {
            add_item(key, str);
        } catch (const char *msg) {
            std::cerr << msg << std::endl;
            delete [] str;
            return;
        }
    }
    delete [] str;
}

int Table::find_item(int key) const {
    int i = 0, m = this->n - 1, j;
    while (i <= m) {
        j = (i + m)/2;
        if (item[j].key == key) {
            return j;
        }
        if (item[j].key < key) {
            i = j + 1;
        } else m = j - 1;
    }
    return -1;
}

void Table::add_item(int key, char *str) {
    if (find_item(key) >= 0) throw "Item with this key already exists";
    if (n == SIZE) throw "Table is full";
    int i = this->n - 1;
    while (i >= 0 && item[i].key > key) {
        item[i+1].key = item[i].key;
        strcpy(item[i+1].str, item[i].str);
        i--;
    }
    item[i+1].key = key;
    strcpy(item[i+1].str, str);
    this->n++;
}

void Table::delete_item(int key) noexcept {
    int j = find_item(key);
    if (j < 0) {
        std::cout << "Item with this key wasn't found" << std::endl;
        return;
    }
    for (int i = j; i < this->n - 1; i++) {
        item[i].key = item[i+1].key;
        strcpy(item[i].str, item[i+1].str);
    }
    this->n--;
}

void Table::modify_info(int key, char* str) noexcept {
    int j = find_item(key);
    if (j < 0) {
        std::cout << "Item with this key wasn't found" << std::endl;
        return;
    }
    strcpy(item[j].str, str);
}

void Table::show_table() const {
    if (this->n < 0)
        throw "Current table size can't be less than 0";
    if (this->n == 0) {
        std::cout << "Table is empty" << std::endl;
        return;
    }
    std::cout << "Table:" << std::endl;
    for (int i = 0; i < this->n; i++) {
        std::cout << "Key: " << item[i].key << " Info: \"" << item[i].str << "\"" << std::endl;
    }
}

void Table::find_and_show() const {
    int key,j;
    char *str = nullptr;
    unsigned int length;
    std::cout << "Enter key:" << std::endl;
    key = get_int();
    j = find_item(key);
    if (j >= 0)  {
        length = item[j].LENGTH;
        str = new char[length];
        get_info(j, str);
    } else {
        std::cout << "Item with this key wasn't found" << std::endl;
        return;
    }
    std::cout << "Info \"" << str << "\"" << std::endl;
    delete str;
}

int init_k_items(Item *item, unsigned int k, std::istream &c) {
    if (k == 0) throw "Count of items can't be less than 1";
    unsigned int length = item->LENGTH;
    char s[1000];
    int key, count = 0;
    for (int i = 0; i < k; i++) {
        std::cout << "Enter key:" << std::endl;
        if (!(c >> key)) return count;
        std::cout << "Enter info:" << std::endl;
        c >> s;
        count++;
    }
    return count;
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

bool correct_get_u_int(unsigned int &a) noexcept {
    std::cin >> a;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

int get_u_int() noexcept {
    unsigned int num;
    while (true) {
        if (correct_get_u_int(num))
            break;
        std::cout << "Wrong number" << std::endl;
    }
    return num;
}
