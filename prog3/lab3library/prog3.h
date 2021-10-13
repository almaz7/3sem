#ifndef PROG3_H
#define PROG3_H
#include <cstring>
//упорядоченная матрица
namespace STATIC {
    #define SIZE 30
    #define LENGTH 31
    typedef struct Item {
        int key;
        char str[LENGTH];
    } Item;

    class Table {
        private:
            int n;  //текущий размер таблицы
            Item item[SIZE]; //массив элементов таблицы
        public:
            Table() { // пустой конструктор для инициализации таблицы по умолчанию
                if (LENGTH < 1)
                    throw "Length of information can't be less than 1";
                if (SIZE < 1)
                    throw "Table size can't be less than 1";
                for (int i = 0; i < SIZE; i++) {
                    item[i].key = i+1; item[i].str[0] = '\0'; n = SIZE;
                }
            }
            Table(int n); //создание таблицы с инициализацией n элементов
            ~Table() { n = 0; }
            int find_item(int key) const; //поиск элемента таблицы по ключу методом двоичного поиска
            void add_item(int key, char* str); //добавление элемента в таблицу
            void delete_item(int key) noexcept; //удаление элемента из таблицы по ключу
            void modify_info(int key, char* str) noexcept; //модификация информации в записи с заданным ключом
            void show_table() const; //вывод таблицы в выходной поток
            void get_info(int i, char *str) const { //получение информации по индексу в таблице
                if (i < 0)  throw "Index can't be less than 0";
                if (i >= n)  throw "Index can't be more than current size";
                strcpy(str, item[i].str);
            }
            void find_and_show() const; //поиск элемента и вывод информации в выходной поток
    };
}

bool correct_get_int(int &a) noexcept;
int get_int() noexcept;


#endif
