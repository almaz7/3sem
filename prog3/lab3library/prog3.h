#ifndef PROG3_H
#define PROG3_H
#include <cstring>
//упорядоченная матрица
//STATIC
struct Item {
    static constexpr int unsigned LENGTH = 31;
    int key;
    char str[LENGTH];
};

class Table {
    private:
        static constexpr int SIZE = 30;
        int n;  //текущий размер таблицы
        struct Item item[SIZE]; //массив элементов таблицы
    public:
        Table():n(0){}// пустой конструктор для инициализации таблицы по умолчанию
        Table(Item *item, int k); //создание таблицы с инициализацией k элементов из массива ключей и инфо
        ~Table() { n = 0; }
        int find_item(int key) const; //поиск элемента таблицы по ключу методом двоичного поиска //+= для таблицы (конкатенация) и поиск перегрузить
        void add_item(int key, char* str); //добавление элемента в таблицу //перегрузить //const
        void delete_item(int key); //удаление элемента из таблицы по ключу //перегрузить
        void modify_info(int key, char* str); //модификация информации в записи с заданным ключом
        std::ostream & show_table(std::ostream &c) const; //вывод таблицы в выходной поток //перегрузить
        void get_info(int i, char *str, unsigned int length) const;  //получение информации по индексу в таблице
        void find_and_show() const; //поиск элемента и вывод информации в выходной поток
};
std::istream & init_item(Item &item, std::istream &c); //ввод значения экземпляра структуры из входного потока;
std::istream & init_k_items(Item *item, int &k, std::istream &c);
bool correct_get_int(int &a) noexcept;
int get_int() noexcept;
#endif
