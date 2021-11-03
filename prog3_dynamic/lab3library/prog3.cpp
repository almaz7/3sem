#include "prog3.h"
//DYNAMIC
Table::Table(Item *item1, int k) {
    if (k < 1)
        throw "Current table size can't be less than 1";
    this->n = 0;
    this->item = nullptr;
    if (!item1) throw "Item is nullptr";
    int i;
    for (i = 0; i < k; i++) {
        try {
            *this = *this + item1[i];
        } catch (const char *msg) {
            clear();
            throw msg;
        }
    }
}

Table::Table(const Table &t) {
    this->n = t.n;
    if (t.n > 0) {
        try {
            item = new Item[t.n];
        } catch (std::bad_alloc &ba) {
            throw "Size of table is too big ";
        }
        for (int i = 0; i < t.n; i++) {
            item[i].key = t.item[i].key;
            try {
                item[i].str = new char[strlen(t.item[i].str) + 1];
            } catch (std::bad_alloc &ba) {
                item[i].str = nullptr;
                this->n = i;
                throw "Length of info is too long";
            }
            item[i].str[0] = '\0';
            strcpy(item[i].str, t.item[i].str);
        }
    }
    //std::cout << "Copy Operator" << std::endl;
}

Table& Table::operator = (const Table &t) noexcept {
    if (this != &t) {
        //std::cout << this->n << std::endl;
        clear();
        this->n = t.n;
        if (t.n > 0) {
            try {
                item = new Item[t.n];
            } catch (std::bad_alloc &ba) {
                std::cerr << "Size of table is too big: " << ba.what() << std::endl;
                item = nullptr;
                return *this;
            }

            for (int i = 0; i < t.n; i++) {
                item[i].key = t.item[i].key;
                try {
                    item[i].str = new char[strlen(t.item[i].str) + 1];
                } catch (std::bad_alloc &ba) {
                    std::cerr << "Length of info is too long: " << ba.what() << std::endl;
                    item[i].str = nullptr;
                    this->n = i;
                    return *this;
                }
                item[i].str[0] = '\0';
                strcpy(item[i].str, t.item[i].str);
            }
        }
        //std::cout << "Operator =" << std::endl;
    }
    return *this;
}

Table Table::operator += (const Table &t) {
    Table tmp;
    tmp = *this;
    for (int i = 0; i < t.n; i++) {
        try {
            tmp = tmp + t.item[i];
        } catch (const char *msg) {
            throw msg;
        }
    }
    *this = tmp;
    return *this;
}

int items_copy(Item *dest, const Item *src, const int size1, const int size2) {
    if (!src) throw "Source item is nullptr";
    if (!dest) throw "Destination item is nullptr";
    if (size1 < size2) throw "Destination size can't be less than source size";
    for (int i = 0; i < size2; i++) {
        dest[i].key = src[i].key;
        try {
            dest[i].str = new char[strlen(src[i].str) + 1];
        } catch (std::bad_alloc &ba) {
            std::cout << "Length of info is too long: " << ba.what() << std::endl;
            dest[i].str = nullptr;
            return i;
        }
        dest[i].str[0] = '\0';
        strcpy(dest[i].str, src[i].str);
    }
    return size2;
}

int Table::find_item(int key) const {
    if (!item) return -1;
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

Table operator + (const Table &t, const Item &item1) {
    if (t.find_item(item1.key) >= 0) throw "Item with this key already exists";
    Table tmp;
    try {
        tmp.item = new Item[t.n + 1];
    } catch (std::bad_alloc &ba) {
        std::cerr << "Size of table is too big: " << ba.what() << std::endl;
        tmp.item = nullptr;
        tmp.n = 0;
        return tmp;
    }
    tmp.item[t.n].str = nullptr;
    tmp.n = t.n;
    if (t.n > 0) {
        int count = items_copy(tmp.item, t.item, t.n + 1, t.n);
        if (count < t.n)
            throw "Not all items were copied";
    }
    int i = t.n - 1;
    while (i >= 0 && tmp.item[i].key > item1.key) {
        tmp.item[i+1].key = tmp.item[i].key;
        delete [] tmp.item[i+1].str;
        try {
            tmp.item[i+1].str = new char[strlen(tmp.item[i].str)+1];
        } catch (std::bad_alloc &ba) {
            throw "Length of info is too long";
        }
        tmp.item[i+1].str[0] = '\0';
        strcpy(tmp.item[i+1].str, tmp.item[i].str);
        i--;
    }

    tmp.item[i+1].key = item1.key;
    delete [] tmp.item[i+1].str;
    try {
        tmp.item[i+1].str = new char[strlen(item1.str)+1];
    } catch (std::bad_alloc &ba) {
        throw "Length of info is too long";
    }
    tmp.item[i+1].str[0] = '\0';
    strcpy(tmp.item[i+1].str, item1.str);
    tmp.n = t.n + 1;
    //std::cout << "Operator +" << std::endl;
    return tmp;
}

Table operator - (const Table &t, const Item &item1) {
    int j = t.find_item(item1.key);
    if (j < 0)
        throw "Item with this key wasn't found";
    Table tmp;
    if (t.n == 1)
        return tmp;
    try {
        tmp = t;
    } catch (const char *msg) {
        throw msg;
    }
    for (int i = j; i < tmp.n - 1; i++) {
        tmp.item[i].key = tmp.item[i+1].key;
        delete [] tmp.item[i].str;
        try {
            tmp.item[i].str = new char[strlen(tmp.item[i+1].str)+1];
        } catch (std::bad_alloc &ba) {
            throw "Length of info is too long";
        }
        tmp.item[i].str[0] = '\0';
        strcpy(tmp.item[i].str, tmp.item[i+1].str);
    }
    delete [] tmp.item[tmp.n-1].str;
    tmp.n--; //утечка памяти
    //std::cout << "Operator -" << std::endl;
    return tmp;
}

void Table::modify_info(int key, char* str) {
    int j = find_item(key);
    if (j < 0)
        throw "Item with this key wasn't found";
    delete [] item[j].str;
    try {
        item[j].str = new char[strlen(str)+1];
    } catch (std::bad_alloc &ba) {
        throw "Length of info is too long";
    }
    item[j].str[0] = '\0';
    strcpy(item[j].str, str);
}

std::ostream& operator << (std::ostream &c, const Table &t) {
    if (t.n < 0)
        throw "Current table size can't be less than 0";
    if (t.n == 0 || !t.item) {
        c << "Table is empty" << std::endl;
        return c;
    }
    c << "Table:" << std::endl;
    for (int i = 0; i < t.n; i++) {
        c << "Key: " << t.item[i].key << " Info: \"" << t.item[i].str << "\"" << std::endl;
    }
    return c;
}

char* Table::get_info(int i) const {
    if (i < 0)  throw "Index can't be less than 0";
    if (i >= n)  throw "Index can't be more than current size";
    char *str = nullptr;
    try {
        str = new char[strlen(item[i].str)+1];
    } catch (std::bad_alloc &ba) {
        throw "Length of info is too long";
    }
    str[0] = '\0';
    strcpy(str, item[i].str);
    return str;
}

void Table::find_and_show() const {
    int key, j;
    char *str = nullptr;
    std::cout << "Enter key:" << std::endl;
    key = get_int();
    j = find_item(key);
    if (j >= 0) {
        try {
            str = get_info(j);
        } catch (const char *msg) {
            delete [] str;
            throw msg;
        }
    } else {
        throw "Item with this key wasn't found";
    }
    std::cout << "Info \"" << str << "\"" << std::endl;
    delete [] str;
}

std::istream & operator >> (std::istream &c, Item &item) {
    int key;
    char s[1000];
    std::cout << "Enter key:" << std::endl;
    if (!(c >> key))
        throw "Invalid key";
    std::cout << "Enter info:" << std::endl;
    c >> s;
    int length = strlen(s);
    item.key = key;
    try {
        item.str = new char[length+1];
    } catch (std::bad_alloc &ba) {
        std::cerr << "Length of info is too long: " << ba.what() << std::endl;
        item.str = nullptr;
        return c;
    }
    item.str[0] = '\0';
    strcat(item.str, s);
    return c;
}

std::istream & init_k_items(Item *item, int &k, std::istream &c) {
    if (k == 0) throw "Count of items can't be less than 1";
    int count = 0;
    for (int i = 0; i < k; i++) {
        try {
            std::cin >> item[i];
        } catch (const char *msg) {
            std::cerr << msg << std::endl;
            k = count;
            return c;
        }
        if (item[i].str == nullptr) {
            k = count;
            return c;
        }
        count++;
    }
    return c;
}

void delete_items(Item *item, const int count) {
    for (int i = 0; i < count; i++)
        delete [] item[i].str;
    delete [] item;
    item = nullptr;
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
