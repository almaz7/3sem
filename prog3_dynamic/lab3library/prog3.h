#ifndef PROG3_H_DYNAMIC
#define PROG3_H_DYNAMIC
#include <cstring>
#include <iostream>
//упорядоченная матрица
//DYNAMIC
struct Item {
    int key;
    char *str;
};

class Table {
    private:
        int n;  //текущий размер таблицы
        struct Item *item; //массив элементов таблицы
        void clear() {
            for (int i = 0; i < n; i++)
                delete [] item[i].str;
            delete [] item;
            item = nullptr;
            n = 0;
        }
    public:
        Table():n(0), item(nullptr){}// пустой конструктор для инициализации таблицы по умолчанию
        Table(Item *item, int k=1); //создание таблицы с инициализацией k элементов из массива ключей и инфо
        Table(const Table &t); //копирующий конструктор
        Table& operator = (const Table &t) noexcept;
        ~Table() {clear();}
        int get_n() const {return this->n;}
        Item* get_item() {return this->item;}
        Table operator += (const Table &t);
        int find_item(int key) const; //поиск элемента таблицы по ключу методом двоичного поиска
        friend Table operator + (const Table &t, const Item &item1); //добавление элемента в таблицу
        friend Table operator - (const Table &t, const Item &item1); //удаление элемента из таблицы по ключу
        void modify_info(int key, char* str); //модификация информации в записи с заданным ключом
        friend std::ostream & operator << (std::ostream &c, const Table &t); //вывод таблицы в выходной поток
        char* get_info(int i) const;  //получение информации по индексу в таблице
        void find_and_show() const; //поиск элемента и вывод информации в выходной поток
};
int items_copy(Item *dest, const Item *src, const int size1, const int size2); //возвращает количество успешно скопированных элементов
void delete_items(Item *item, const int count);
std::istream & operator >> (std::istream &c, Item &item);
std::istream & init_k_items(Item *item, int &k, std::istream &c);
bool correct_get_int(int &a) noexcept;
int get_int() noexcept;
#endif
