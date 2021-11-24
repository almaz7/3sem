#include<iostream>
#include<cstring>
#include<stdexcept>
using std::cout;
using std::cin;
using std::endl;

template<typename T>
void getNum(T &a, std::string msg = "Enter number\n") { 
    cout << msg;
    cin >> a;
    while(!cin.good()) {
        cin.clear();
        cin.ignore(255,'\n');
        cout << msg;
        cin >> a;
    }
}
struct Item {
    static const int s_size = 1000; // please change for your own purposes
    int key;
    char info[s_size];
    void init(int k, const char str[s_size]){
        key = k;
        memcpy(info, str, s_size * sizeof(char));
    };
    Item(): key(0) { info[0] = 0; }
};

class Table { // is ordered table
private:
    int c_size; // current size;
    int t_size; // table size, quantity of allocated Item;
    Item *item;
public:
    //functions
    int getmaxsize() const {return t_size;}
    int getcursize() const {return c_size;}
    //defined for alloc new memory
    static const int quota = 10; // you could change it without problems
    void print(std::ostream &c) const;
    int bin_search(int key) const; 
    std::string get_info(int key) const; //return string related with key
    int insert(int key, const char str[Item::s_size]);
    void item_delete(int key);
    void info_change(int key, char str[Item::s_size]);
    void clear() {c_size = 0;}
    //constructors
    Table(int size = quota);
    Table(Item *item, int count);
    Table(const Table &c):c_size(c.c_size), t_size(c.t_size) {
        item = new Item [c.t_size];
        memcpy(item, c.item, c.c_size * sizeof(Item));
    }
    Table(Table &&c):c_size(c.c_size), t_size(c.t_size), item(c.item) {
        c.item = nullptr;
    };
    ~Table() {delete[] item; item = nullptr;}
    //overload operators
    Table &operator=(const Table &t) {
        if (this != &t) {
            delete [] item;
            item = nullptr;
            c_size = t.c_size;
            t_size = t.t_size;
            item = new Item[t.t_size];
            memcpy(item, t.item, t.c_size * sizeof(Item));
        }
        return *this;
    }
    Table &operator=(Table &&t) {
        int cs = c_size;
        int ts = t_size;
        c_size = t.c_size;
        t_size = t.t_size;
        t.c_size = cs;
        t.t_size = ts;
        Item *i = item;
        item = t.item;
        t.item = i;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &s, Table &t) {
        t.print(s);
        return s;
    }
    friend std::istream &operator>>(std::istream &s, Table &t) {
        int key;
        char str[Item::s_size];
        s >> key >> str;
        if (s.good()) {
            t.insert(key, str);
        }
        else
            s.setstate(std::ios::failbit); 
        return s;
    }
    Table & operator-=(int key) {
            item_delete(key);
            return *this;
    }
    int operator()(int key) {
        int i = bin_search(key);
        return i;
    }
};
