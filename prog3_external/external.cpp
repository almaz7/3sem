#include"external.h"
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

Table* add_recipe(Table *t1, int &c_count, int &t_count) {
    if (c_count < 0 || t_count < 0)
        throw std::logic_error("Size less 0\n");
    Table *t = nullptr;
    if (c_count >= t_count || !t1) {
        t_count += 10;
        try {
            t = new Table[t_count];
        } catch (std::bad_alloc &g) {
            cout << g.what() << endl;
            return nullptr;
        }
        for (int i = 0; i < c_count; i++) {
            t[i] = t1[i];
        }
        delete [] t1;
    } else {
        t = t1;
    }
    cin.ignore();
    char str[9][Item::s_size];
    cout << "Введите название блюда:" << endl; //1
    cin.getline(str[0], Item::s_size, '\n');
    cout << "Введите описание:" << endl; //2
    cin.getline(str[1], Item::s_size, '\n');
    cout << "Введите калорийность:" << endl; //3
    cin.getline(str[2], Item::s_size, '\n');
    cout << "Введите белки:" << endl; //4
    cin.getline(str[3], Item::s_size, '\n');
    cout << "Введите жиры:" << endl; //5
    cin.getline(str[4], Item::s_size, '\n');
    cout << "Введите углеводы:" << endl; //6
    cin.getline(str[5], Item::s_size, '\n');
    cout << "Введите время, необходимое для готовки:" << endl; //7
    cin.getline(str[6], Item::s_size, '\n');
    cout << "Введите требуемые ингредиенты:" << endl; //8
    cin.getline(str[7], Item::s_size, '\n');
    cout << "Введите инструкцию по приготовлению:" << endl; //9
    cin.getline(str[8], Item::s_size, '\n');
    for (int i = 0; i < 9; i++) {
        try {
            t[c_count].insert(i + 1, str[i]);
        }
        catch (std::logic_error &e) {
            cout << e.what() << endl;
            return nullptr;
        }
    }
    c_count++;
    t1 = t;
    return t1;
}

Table* delete_recipe(Table *t, int &c_count, int &t_count, const int &k) {
    if (c_count < 0 || t_count < 0)
        throw std::logic_error("Size less 0\n");
    if (c_count == 0 || !t)
        throw std::logic_error("List of recipes is empty\n");
    if (k <= 0)
        throw std::logic_error("Recipe number can't be less than 1\n");
    if (k > c_count)
        throw std::logic_error("Recipe number can't be more than count of recipes\n");
    for (int i = k - 1; i < c_count - 1; i++) {
        t[i] = t[i+1];
    }
    t[c_count-1].clear();
    c_count--;
    if (c_count == 0) {
        delete [] t;
        t_count = 0;
        return nullptr;
    }
    if (t_count - c_count >= 10) {
        t_count = c_count;
        Table *t1 = nullptr;
        try {
            t1 = new Table[t_count];
        } catch (std::bad_alloc &g) {
            cout << g.what() << endl;
            return nullptr;
        }
        for (int i = 0; i < c_count; i++) {
            t1[i] = t[i];
        }
        delete [] t;
        t = t1;
    }
    return t;
}

Table* change_recipe(Table *t, int &c_count, int &t_count, const int &k) {
    if (c_count < 0 || t_count < 0)
        throw std::logic_error("Size less 0\n");
    if (c_count == 0 || !t)
        throw std::logic_error("List of recipes is empty\n");
    if (k <= 0)
        throw std::logic_error("Recipe number can't be less than 1\n");
    if (k > c_count)
        throw std::logic_error("Recipe number can't be more than count of recipes\n");
    cin.ignore();
    char str[9][Item::s_size];
    cout << "Введите название блюда:" << endl; //1
    cin.getline(str[0], Item::s_size, '\n');
    cout << "Введите описание:" << endl; //2
    cin.getline(str[1], Item::s_size, '\n');
    cout << "Введите калорийность:" << endl; //3
    cin.getline(str[2], Item::s_size, '\n');
    cout << "Введите белки:" << endl; //4
    cin.getline(str[3], Item::s_size, '\n');
    cout << "Введите жиры:" << endl; //5
    cin.getline(str[4], Item::s_size, '\n');
    cout << "Введите углеводы:" << endl; //6
    cin.getline(str[5], Item::s_size, '\n');
    cout << "Введите время, необходимое для готовки:" << endl; //7
    cin.getline(str[6], Item::s_size, '\n');
    cout << "Введите требуемые ингредиенты:" << endl; //8
    cin.getline(str[7], Item::s_size, '\n');
    cout << "Введите инструкцию по приготовлению:" << endl; //9
    cin.getline(str[8], Item::s_size, '\n');
    for (int i = 0; i < 9; i++) {
        try {
            t[k-1].info_change(i+1, str[i]);
        }
        catch (std::logic_error &e) {
            cout << e.what() << endl;
            return t;
        }
    }
    return t;
}

void show_one_recipe(const Table *t, const int &c_count, const int &k) {
    if (c_count < 0)
        throw std::logic_error("Size less 0\n");
    if (!t || c_count == 0) {
        cout << "Список рецептов пуст" << endl;
        return;
    }
    if (k <= 0)
        throw std::logic_error("Recipe number can't be less than 1\n");
    if (k > c_count)
        throw std::logic_error("Recipe number can't be more than count of recipes\n");
    std::string str[9];
    cout << endl;
    cout << "Блюдо №" << k << endl;
    for (int j = 0; j < 9; j++) {
        str[j] = t[k-1].get_info(j+1);
    }
    cout << "Название блюда:" << endl; //1
    cout << str[0] << endl;
    cout << "Описание:" << endl; //2
    cout << str[1] << endl;
    cout << "Калорийность:" << endl; //3
    cout << str[2] << endl;
    cout << "Белки:" << endl; //4
    cout << str[3] << endl;
    cout << "Жиры:" << endl; //5
    cout << str[4] << endl;
    cout << "Углеводы:" << endl; //6
    cout << str[5] << endl;
    cout << "Время, необходимое для готовки:" << endl; //7
    cout << str[6] << endl;
    cout << "Требуемые ингредиенты:" << endl; //8
    cout << str[7] << endl;
    cout << "Инструкцию по приготовлению:" << endl;
    cout << str[8] << endl;
}

void show_list_recipes(const Table *t, const int &c_count) {
    if (c_count < 0)
        throw std::logic_error("Size less 0\n");
    if (!t || c_count == 0) {
        cout << "Список рецептов пуст" << endl;
        return;
    }
    std::string str[9];
    for (int i = 0; i < c_count; i++) {
        cout << endl;
        cout << "Блюдо №" << i+1 << endl;
        for (int j = 0; j < 9; j++) {
            str[j] = t[i].get_info(j+1);
        }
        cout << "Название блюда:" << endl; //1
        cout << str[0] << endl;
        cout << "Описание:" << endl; //2
        cout << str[1] << endl;
        cout << "Калорийность:" << endl; //3
        cout << str[2] << endl;
        cout << "Белки:" << endl; //4
        cout << str[3] << endl;
        cout << "Жиры:" << endl; //5
        cout << str[4] << endl;
        cout << "Углеводы:" << endl; //6
        cout << str[5] << endl;
        cout << "Время, необходимое для готовки:" << endl; //7
        cout << str[6] << endl;
        cout << "Требуемые ингредиенты:" << endl; //8
        cout << str[7] << endl;
        cout << "Инструкцию по приготовлению:" << endl;
        cout << str[8] << endl;
    }
}

void output_file(const Table *t, const int &c_count) {
    if (c_count < 0)
        throw std::logic_error("Size less 0\n");
    if (!t || c_count == 0) {
        cout << "Список рецептов пуст" << endl;
        return;
    }
    std::ofstream fout;
    char name[30];
    cout << "Введите название файла для записи информации:" << endl;
    cin >> name;
    fout.open(name); //, std::ios_base::trunc
    if (!fout.is_open())
        throw std::logic_error("File can't be opened\n");

    std::string str;
    for (int i = 0; i < c_count; i++) {
        for (int j = 0; j < 9; j++) {
            str = t[i].get_info(j + 1);
            fout << str << endl;
        }
    }
    cout << "Информация была записана в файл " << name << endl;
    fout.close();
}

Table* input_file(Table *t1, int &c_count, int &t_count) {
    if (c_count < 0 || t_count < 0)
        throw std::logic_error("Size less 0\n");
    std::ifstream fin;
    char name[30];
    cout << "Введите название файла для считывания информации:" << endl;
    cin >> name;
    fin.open(name); //, std::ios_base::trunc
    if (!fin.is_open())
        throw std::logic_error("File can't be opened\n");
    Table *t;
    char str[9][Item::s_size];
    while (fin) {
        for (int i = 0; i < 9; i++) {
            fin.getline(str[i], Item::s_size, '\n');
        }
        if (str[0][0] == '\0') break;
        t = nullptr;
        if (c_count >= t_count || !t1) {
            t_count += 10;
            try {
                t = new Table[t_count];
            } catch (std::bad_alloc &g) {
                cout << g.what() << endl;
                return nullptr;
            }
            for (int i = 0; i < c_count; i++) {
                t[i] = t1[i];
            }
            delete[] t1;
        } else {
            t = t1;
        }


        for (int i = 0; i < 9; i++) {
            try {
                t[c_count].insert(i + 1, str[i]);
            }
            catch (std::logic_error &e) {
                cout << e.what() << endl;
                return nullptr;
            }
        }
        c_count++;
        t1 = t;
    }
    cout << "Информация была считана из файла " << name << endl;
    fin.close();
    return t1;
}