#include"table.h"
Table* add_recipe(Table *t1, int &c_count, int &t_count);
Table* delete_recipe(Table *t, int &c_count, int &t_count, const int &k);
Table* change_recipe(Table *t, int &c_count, int &t_count, const int &k);
void show_one_recipe(const Table *t, const int &c_count, const int &k);
void show_list_recipes(const Table *t, const int &c_count);
void output_file(const Table *t, const int &c_count);
Table* input_file(Table *t1, int &c_count, int &t_count);