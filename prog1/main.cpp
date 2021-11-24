#include <iostream>
#include "prog1.h"
using namespace Prog1;

int main() {
    int *x = nullptr, *y = nullptr, *a = nullptr;
    int m = 0, n = 0, k = 0, status;
    k = input(m, n, x, y, a);
    if (k == -1) return 1;  //problem with memory or entering
    int max_index = find_max_line(k, y, a);
    output("Original matrix", k, m, n, x, y, a);
    status = sort_max_line(max_index, k, x, y, a, n);
    if (status) {           //problem with memory
        return 1;
    }
    output("New matrix", k, m, n, x, y, a);
    if (a) delete [] a;
    if (x) delete [] x;
    if (y) delete[] y;
    return 0;
}
