#include"table.h"
Table::Table(int size): c_size(0), t_size(size), item(new Item [size]) {}

Table::Table(Item *item1, int count) {
    try {
        item = new Item [count];
    }
    catch (std::bad_alloc &g) {
        cout << g.what() << endl;
        return;
    }
    t_size = c_size = count;
    for (int i = 0; i < count; ++i) {
        item[i] = item1[i];
    }
}

void Table::print(std::ostream &c) const {
    c << "\nORDERED TABLE:\n";
    if (!c_size) 
        c << "EMPTY\n";
    for (int i = 0; i < c_size; ++i) {
        c << item[i].key << " - " << item[i].info << endl;
    }
    c << "c_size: " << c_size << endl; // for debug
    c << endl;
}

static int first; 
int Table::bin_search(int key) const {
    first = 0;
    if (c_size == 0)
        return -1;
    int last = c_size - 1, cur;
    while (first < last) {
    cur = (first + last) / 2;
        if (item[cur].key == key)
            return cur;
        if (item[cur].key < key) {
            first = cur + 1;
        }
        else {
            last = cur - 1;
        }
    }
    if (item[first].key == key)
        return first;
    return -1; 
}

int Table::insert(int key, const char str[Item::s_size]) {
    int ind = bin_search(key); 
    if (ind >= 0)
        throw std::logic_error("Element is already exist\n");
    if (c_size >= t_size) { // current size less than max table size
        Item *tmp;
            try {
                tmp = new Item[t_size += quota];
            }
            catch (std::bad_alloc &g) {
                cout << g.what() << endl;
                return -1;
            }
            memcpy(tmp, item, c_size * sizeof(Item));
            delete [] item;
            item = tmp;
            cout << "memalloc\n";
    }
    for (int i = first; i <= c_size; ++i) {
        if (i >= c_size) {
                item[i].init(key, str);
                ++c_size;
                return 0;
            }
            else if (item[i].key > key) {
                memmove(item + i + 1, item + i, (c_size - i) * sizeof(Item));
                item[i].init(key, str);
                ++c_size;
                return 0;
            }
    }
    return 0;
}

void Table::item_delete(int key) {
    int ind = bin_search(key);
    if (ind < 0) {
        throw std::logic_error("Element don't exist\n");
    }
    memmove(item + ind, item + ind + 1, sizeof(Item) * (--c_size - ind));
}

void Table::info_change(int key, char str[Item::s_size]) {
    int ind = bin_search(key);
    if (ind < 0) {
        throw std::logic_error("Element don't exist\n");
    }
    memcpy(item[ind].info, str, Item::s_size);
}

std::string Table::get_info(int key) const {
    int ind = bin_search(key);
    if (ind < 0) {
        throw std::logic_error("Element don't exist\n");
    }
    std::string str = item[ind].info;
    return str;
}
