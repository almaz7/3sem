#include <iostream>
#include "prog3.h"
//STATIC
Table::Table(Item *item1, int k) {
    if (k < 1)
        throw "Current table size can't be less than 1";
    this->n = 0;
    int key;
    unsigned int i, length = Item::LENGTH;
    char* str = new char[length];
    for (i = 0; i < k; i++) {
        key = item1[i].key;
        str[0] = '\0';
        strcat(str, item1[i].str);
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
    int i = 0;
    int m = this->n - 1, j;
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
    unsigned int length = Item::LENGTH;
    if (length <= strlen(str)) throw "Info is too long";

    int i = this->n - 1;
    while (item[i].key > key) {
        item[i+1].key = item[i].key;
        item[i+1].str[0] = '\0';
        strcpy(item[i+1].str, item[i].str);
        i--;
    }
    item[i+1].key = key;
    item[i+1].str[0] = '\0';
    strcpy(item[i+1].str, str);
    this->n++;
}

void Table::delete_item(int key) {
    int j = find_item(key);
    if (j < 0)
        throw "Item with this key wasn't found";
    for (int i = j; i < this->n - 1; i++) {
        item[i].key = item[i+1].key;
        item[i].str[0] = '\0';
        strcpy(item[i].str, item[i+1].str);
    }
    this->n--;
}

void Table::modify_info(int key, char* str) {
    int j = find_item(key);
    if (j < 0)
        throw "Item with this key wasn't found";
    unsigned int length = Item::LENGTH;
    if (length <= strlen(str)) throw "Info is too long";
    strcpy(item[j].str, str);
}

std::ostream & Table::show_table(std::ostream &c) const {
    if (this->n < 0)
        throw "Current table size can't be less than 0";
    if (this->n == 0) {
        c << "Table is empty" << std::endl;
    }
    c << "Table:" << std::endl;
    for (int i = 0; i < this->n; i++) {
        c << "Key: " << item[i].key << " Info: \"" << item[i].str << "\"" << std::endl;
    }
    return c;
}

void Table::get_info(int i, char *str, unsigned int length) const {
    if (i < 0)  throw "Index can't be less than 0";
    if (i >= n)  throw "Index can't be more than current size";
    if (length <= strlen(item[i].str))  throw "Length of string isn't enough";
    strcpy(str, item[i].str);
}

void Table::find_and_show() const {
    int key, j;
    char *str = nullptr;
    unsigned int length;
    std::cout << "Enter key:" << std::endl;
    key = get_int();
    j = find_item(key);
    if (j >= 0) {
        length = Item::LENGTH;
        str = new char[length];
        try {
            get_info(j, str, length);
        } catch (const char *msg) {
            std::cerr << msg << std::endl;
            delete [] str;
            return;
        }
    } else {
        std::cout << "Item with this key wasn't found" << std::endl;
        return;
    }
    std::cout << "Info \"" << str << "\"" << std::endl;
    delete [] str;
}

std::istream & init_item(Item &item, std::istream &c) {
    int key;
    unsigned int length = Item::LENGTH;
    char s[1000];
    std::cout << "Enter key:" << std::endl;
    if (!(c >> key))
        throw "Invalid key";
    std::cout << "Enter info:" << std::endl;
    c >> s;
    if (length <= strlen(s)) throw "Info is too long";
    item.key = key;
    item.str[0] = '\0';
    strcat(item.str, s);
    return c;
}

std::istream & init_k_items(Item *item, int &k, std::istream &c) {
    if (k == 0) throw "Count of items can't be less than 1";
    int count = 0;
    for (int i = 0; i < k; i++) {
        try {
            init_item(item[i], c);
        } catch (const char *msg) {
            std::cerr << msg << std::endl;
            k = count;
            return c;
        }
        count++;
    }
    return c;
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
