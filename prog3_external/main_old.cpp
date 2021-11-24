#include"table.h"

void D_Insert(Table &t) {
    int key;
    char arr[Item::s_size];
    getNum(key);
    cout << "Enter string no more " << Item::s_size << " symbols\n";
    cin.ignore();
    cin.getline(arr, Item::s_size, '\n');
    try {
        t.insert(key, arr);
    }
    catch (std::logic_error &e) {
        cout << e.what() << endl;
    }
}

void D_Delete(Table &t) {
    int key;
    getNum(key);
    try {
        t.item_delete(key);
    }
    catch (std::logic_error &e) {
        cout << e.what() << endl;
    }
}

void D_Change(Table &t) {
    int key;
    char arr[Item::s_size];
    getNum(key);
    cout << "Enter new string no more " << Item::s_size << " symbols\n";
    cin.ignore();
    cin.getline(arr, Item::s_size, '\n');
    try {
        t.info_change(key, arr);
    }
    catch (std::logic_error &e) {
        cout << e.what() << endl;
    }
}

void D_GetInfo(Table &t) {
    int key;
    std::string str;
    getNum(key);
    try {
        str = t.get_info(key);
    }
    catch (std::logic_error &e) {
        cout << e.what() << endl;
    }
    cout << str << endl;
}




static const char *info = "\n1 - insert\n2 - delete\n3 - get_info\n4 - change\
 info\n5 - print\n(-1) - EXIT\n";
void dialog(Table &t) {
    int cs;
    while (1) {
        cout << info;
        getNum(cs, "Make choice\n");
        switch (cs) {
            case 1: //insert
                D_Insert(t);
                break;
            case 2: //delete
                D_Delete(t);
                break;
            case 3: //get information about item from key
                D_GetInfo(t);
                break;
            case 4: //change info
                D_Change(t);
                break;
            case 5: //print
                t.print(cout);
                break;
            case -1:
                return;
            default:
                cout << "Misha molodets\n";
                break;
        }
    }
}

int main() {
    Table table; 
    dialog(table);
    Table t;
    t = table;
    t.print(std::cout);
    return 0;
}
