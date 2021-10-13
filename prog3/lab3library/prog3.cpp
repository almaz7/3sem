#include <iostream>
#include "prog3.h"
using namespace STATIC;
Table::Table(int n) {
    if (n < 1)
        throw "Current table size can't be less than 1";
    if (n > SIZE)
        throw "Current table size can't be more than SIZE";
    if (LENGTH < 1)
        throw "Length of information can't be less than 1";
    this->n = 0;
    int i, key;
    char str[LENGTH];
    for (i = 0; i < n; i++) {
        std::cout << "Enter key:" << std::endl;
        key = get_int();
        std::cout << "Enter information:" << std::endl;
        std::cin >> str;
        try {
            add_item(key, str);
        } catch (const char *msg) {
            std::cerr << msg << std::endl;
            return;
        }
    }
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
    std::cout << "Enter key:" << std::endl;
    key = get_int();
    j = find_item(key);
    if (j >= 0)  {
        str = new char[LENGTH];
        get_info(j, str);
    } else {
        std::cout << "Item with this key wasn't found" << std::endl;
        return;
    }
    std::cout << "Info \"" << str << "\"" << std::endl;
    delete str;
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

