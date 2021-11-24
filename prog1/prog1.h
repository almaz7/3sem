#ifndef PROG1_H
#define PROG1_H
namespace Prog1 {
    int* realloc_mem(const int k, int* mas);
    int input(int &m, int &n, int* &x, int* &y, int* &a);
    void output(const char* msg, const int k, const int &m, const int &n, const int* x, const int* y, const int* a);
    int find_max_line(const int k, const int* y, const int* a);
    void sort_increase(int* &vec, const int n);
    void sort_decrease(int* &vec, const int n);
    int sort_max_line(const int max_index, const int k, int* x, const int* y, int* a, const int n);
}
#endif
