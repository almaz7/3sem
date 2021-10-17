#ifndef PROG3_H
#define PROG3_H
#include <cstring>
//упорядоченная матрица
namespace STATIC {

    struct Item {
        static constexpr unsigned int LENGTH = 31;
        int key;
        char str[LENGTH];
    };

    class Table {
        private:
            static constexpr unsigned int SIZE = 30;
            unsigned int n;  //текущий размер таблицы
            struct Item item[SIZE]; //массив элементов таблицы
        public:
            Table():n(0){}// пустой конструктор для инициализации таблицы по умолчанию
            Table(Item *item, unsigned int k); //создание таблицы с инициализацией k элементов из массива ключей и инфо
            ~Table() { n = 0; }
            int find_item(int key) const; //поиск элемента таблицы по ключу методом двоичного поиска //+= для таблицы (конкатенация) и поиск перегрузить
            void add_item(int key, char* str); //добавление элемента в таблицу //перегрузить //const
            void delete_item(int key) noexcept; //удаление элемента из таблицы по ключу //перегрузить
            void modify_info(int key, char* str) noexcept; //модификация информации в записи с заданным ключом
            void show_table() const; //вывод таблицы в выходной поток //перегрузить
            void get_info(int i, char *str) const { //получение информации по индексу в таблице
                if (i < 0)  throw "Index can't be less than 0";
                if (i >= n)  throw "Index can't be more than current size";
                strcpy(str, item[i].str);
            }
            void find_and_show() const; //поиск элемента и вывод информации в выходной поток
    };
    int init_k_items(Item *item, unsigned int k);
}

bool correct_get_int(int &a) noexcept;
int get_int() noexcept;
bool correct_get_u_int(unsigned int &a) noexcept;
int get_u_int() noexcept;

#endif
