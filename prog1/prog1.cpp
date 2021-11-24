#include <iostream>
#include <climits>
#include "prog1.h"
namespace Prog1 {
    int* realloc_mem(const int k, int* mas) {
        if (k <= 0) return nullptr;

        if (!mas) {
            try {
                mas =  new int[k];
            } catch (std::bad_alloc& ba) {
                std::cout << "Not enough memory to reallocate it" << ba.what() << std::endl;
                return nullptr;
            }
            return mas;
        }

        int *mas1;
        try {
            mas1 =  new int[k];
        } catch (std::bad_alloc& ba) {
            std::cout << "Not enough memory to reallocate it" << ba.what() << std::endl;
            delete [] mas;
            return nullptr;
        }
        for (int i = 0; i < k; i++) {
            mas1[i] = mas[i];
        }
        delete[] mas;
        return mas1;
    }

    int input(int &m, int &n, int* &x, int* &y, int* &a) {
        int i, j, num, k = 0;
        const char *pr = "";
        std::cout << "Enter the number of lines:" << std::endl;
        do {
            std::cout << pr << std::endl;
            pr = "You are wrong. Repeat please";
            if (!(std::cin >> m))
                return -1;
        } while (m < 1);

        pr = "";
        std::cout << "Enter the number of columns:" << std::endl;
        do {
            std::cout << pr << std::endl;
            pr = "You are wrong. Repeat please";
            if (!(std::cin >> n))
                return -1;
        } while (n < 1);

        x = realloc_mem(m*n, x);
        y = realloc_mem(m*n, y);
        a = realloc_mem(m*n, a);

        std::cout << "Enter matrix:" << std::endl;
        for (i = 0; i < m; i++) {
            std::cout << "line #" << i + 1 << std::endl;
            for (j = 0; j < n; j++) {
                if (!(std::cin >> num)) {
                    delete[] x;
                    delete[] y;
                    delete[] a;
                    return -1;
                }

                if (num != 0) {
                    y[k] = i;
                    x[k] = j;
                    a[k] = num;
                    k++;
                }
            }
        }

        if (k == 0) {       //matrix consists of 0
            delete[] x;
            delete[] y;
            delete[] a;
            x = nullptr; y = nullptr; a = nullptr;
            return 0;
        }

        x = realloc_mem(k, x);
        y = realloc_mem(k, y);
        a = realloc_mem(k, a);

        if (!x || !y || !a) {
            if (x) delete[] x;
            if (y) delete[] y;
            if (a) delete[] a;
            return -1;      //problem with memory
        }
        return k;
    }

    void output(const char* msg, const int k, const int &m, const int &n, const int* x, const int* y, const int* a) {
        int i, j, num = 0;
        std::cout << msg << ":" << std::endl;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (num < k && y[num] == i && x[num] == j) {
                    std::cout << a[num] << " ";
                    num++;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int find_max_line(const int k, const int* y, const int* a) {
        if (k == 0) return 0;
        int max_sum = INT_MIN, sum = 0, max_index, index = 0, num = 0;
        while (num < k) {
            while (num < k && index == y[num]) {
                sum += a[num];
                num++;
            }
            if (sum > max_sum) {
                max_sum = sum;
                max_index = index;
            }
            sum = 0;
            index++;
        }
        return max_index;
    }

    void sort_increase(int* &vec, const int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (vec[i] > vec[j]) {
                    int c = vec[i];
                    vec[i] = vec[j];
                    vec[j] = c;
                }
            }
        }
    }

    void sort_decrease(int* &vec, const int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (vec[i] < vec[j]) {
                    int c = vec[i];
                    vec[i] = vec[j];
                    vec[j] = c;
                }
            }
        }
    }

    int sort_max_line(const int max_index, const int k, int* x, const int* y, int* a, const int n) {
        int num = 0, i, start_index;
        if (k == 0) return 0;
        int *vec;
        try {
            vec = new int [n];
        } catch (std::bad_alloc& ba) {
            std::cout << "Too many columns in matrix" << ba.what() << std::endl;
            delete [] a;
            delete [] x;
            delete [] y;
            return 1;
        }

        while (num < k && y[num] < max_index) num++;

        if (num == k || y[num] > max_index) {
            /*for (i = 0; i < n; i++) {
                vec[i] = 0;         //line consists of 0
            }*/
            delete[] vec;
            return 0;
        } else if (num < k && y[num] == max_index) {
            start_index = num;
            for (i = 0; i < n; i++) {
                if (x[num] == i) {
                    vec[i] = a[num];
                    num++;
                } else {
                    vec[i] = 0;
                }
            }
        }

        if (vec[0] > 0) {
            sort_increase(vec, n);
        } else {
            sort_decrease(vec, n);
        }
        int index = start_index;
        for (i = 0; i < n; i++) {
            if (vec[i] != 0) {
                x[index] = i;
                a[index] = vec[i];
                index++;
            }
        }
        delete[] vec;
        return 0;
    }
}
