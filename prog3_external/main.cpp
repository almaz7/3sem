#include "external.h"
static const char *info = "\n1 - добавить рецепт\n2 - удалить рецепт\n3 - изменить рецепт\n4 - показать\
 один из рецептов\n5 - показать все рецепты\n6 - записать рецепты в файл\n7 - взять рецепты из файла\n\
8 - удалить все рецепты\n(-1) - Выход\n";
void dialog(Table *t) {
    int cs;
    int c_count = 0;
    int t_count = 0;
    while (1) {
        cout << info;
        getNum(cs, "Make choice\n");
        switch (cs) {
            case 1: //добавить рецепт
            {
                Table *a = nullptr;
                try {
                    a = add_recipe(t, c_count, t_count);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
                if (a) t = a;
            }
                break;
            case 2: //удалить рецепт
            {
                int k;
                getNum(k, "Введите номер удаляемого рецепта (блюда)\n");
                try {
                    t = delete_recipe(t, c_count, t_count, k);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3: //изменить рецепт
            {
                int k;
                getNum(k, "Введите номер изменяемого рецепта (блюда)\n");
                try {
                    t = change_recipe(t, c_count, t_count, k);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
            }
                break;
            case 4: //показать один из рецептов
            {
                int k;
                getNum(k, "Введите номер рецепта (блюда), который хотите посмотреть\n");
                try {
                    show_one_recipe(t, c_count, k);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 5: //показать все рецепты
                try {
                    show_list_recipes(t, c_count);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
                break;
            case 6: //записать рецепты в файл
                try {
                    output_file(t, c_count);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
                break;
            case 7: //взять рецепты из файла
            {
                Table *a = nullptr;
                try {
                    a = input_file(t, c_count, t_count);
                }
                catch (std::logic_error &e) {
                    cout << e.what() << endl;
                }
                if (a) t = a;
            }
                break;
            case 8: //удалить все рецепты
                delete [] t;
                t = nullptr;
                c_count = 0;
                t_count = 0;
                break;
            case -1:
                delete [] t;
                return;
            default:
                cout << "You are wrong! Try again\n";
                break;
        }
    }
}

int main() {
    Table *t = nullptr;
    dialog(t);
    return 0;
}
