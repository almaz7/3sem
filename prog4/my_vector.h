#ifndef MY_VECTOR
#define MY_VECTOR
#include <iostream>
#include <stdexcept>
template <class T>
class Iterator;
template <class T>
class Const_Iterator;
template <class T>
class vector {
    private:
    int n;
    int SIZE;
    T *arr;

    public:
    vector(): n(0), SIZE(0), arr(nullptr) {}
    ~vector() {
        delete [] arr;
        arr = nullptr;
        n = 0;
        SIZE = 0;
    }
    vector(const vector<T>& vec): n(vec.n), SIZE(vec.SIZE), arr(new T[vec.n]) {
        for (int i = 0; i < n; i++) {
            arr[i] = vec.arr[i];
        }
    }
    vector(vector<T> &&vec): n(vec.n), SIZE(vec.SIZE), arr(vec.arr) {
        vec.arr = nullptr;
    }
    vector<T>& operator =(const vector<T> &vec);
    vector<T>& operator =(vector<T> &&vec) noexcept;
    void push_back(const T& value);

    int size() const noexcept {return n;}
    void clear() noexcept {delete [] arr; arr = nullptr; n = 0; SIZE = 0;}
    T& get_elem(const int& ind) {
        if (ind < 0 || ind >= n) throw std::logic_error("Invalid index");
        return arr[ind];
    }
    typedef Iterator<T> It;
    typedef Const_Iterator<T> Const_It;

    It begin() {
        return It(arr);
    }
    It end() {
        if (!arr) {
            return It(arr);
        } else return It(arr+n);
    }
    Const_It begin() const {
        return Const_It(arr);
    }
    Const_It end() const {
        if (!arr) {
            return Const_It(arr);
        } else return Const_It(arr+n);
    }
    It erase(It &it);
};

template <class T>
Iterator<T> vector<T>::erase(Iterator<T> &it) {
    if (!(it - begin() >= 0 && end() - it > 0)) throw std::logic_error("Invalid iterator position");
    Iterator<T> it1;
    int k;
    for (it1 = it; end() - it1 > 1; it1++) {
        k = it1-begin();
        arr[k] = arr[k+1];
    }
    n--;
    if (SIZE - n >= 10) {
        SIZE = n;
        T *buf = new T[SIZE];
        for (int i = 0; i < n; i++) {
            buf[i] = arr[i];
        }
        delete [] arr;
        arr = buf;
    }
    return begin();
}


template <class T>
vector<T>& vector<T>::operator =(const vector<T> &vec) {
    if(this != &vec){
        delete [] arr;
        n = vec.n;
        SIZE = vec.size;
        try {
            arr = new T[SIZE];
        } catch (std::bad_alloc &ba) {
            throw ba;
        }
        for(int i = 0; i < n; ++i)
            arr[i] = vec.arr[i];
    }
    return *this;
}


template <class T>
vector<T> &vector<T>::operator=(vector<T> &&vec) noexcept{
    if (this != &vec) {
        delete[] arr;
        n = vec.n;
        SIZE = vec.SIZE;
        arr = vec.arr;
        vec.arr = nullptr;
    }
    return *this;
}


template <class T>
void vector<T>::push_back(const T &value) {
    if (n >= SIZE) {
        T *buf = nullptr;
        try {
            buf = new T[SIZE += 10];
        } catch (std::bad_alloc &ba) {
            throw ba;
        }
        for (int i = 0; i < n; i++) {
            buf[i] = arr[i];
        }
        delete[] arr;
        arr = buf;
    }
    arr[n++] = value;
}



template <class T>
class Iterator {
    typedef Iterator<T> It;
    friend Const_Iterator<T>;
    private:
    T *ptr;
    public:
    Iterator(T *p = nullptr): ptr(p) {}
    Iterator(const It& it): ptr(it.ptr) {}
    bool operator ==(const It &it) const {
        return ptr == it.ptr;
    }
    bool operator !=(const It &it) const {
        return ptr != it.ptr;
    }
    T& operator *() {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        return *ptr;
    }
    T* operator ->() {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        return ptr;
    }
    It& operator++() {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        ptr++;
        return *this;
    }
    It operator ++(int) {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        It buf(*this);
        ++*this;
        return buf;
    }
    int friend operator-(const It& it1, const It &it2) {
        if (!it1.ptr || !it2.ptr) throw std::logic_error("Pointer is nullptr");
        return it1.ptr - it2.ptr;
    }
};


template <class T>
class Const_Iterator {
    typedef Const_Iterator<T> Const_It;
private:
    T *ptr;
public:
    Const_Iterator(T *p = nullptr): ptr(p) {}
    Const_Iterator(const Const_It& it): ptr(it.ptr) {}
    Const_Iterator(const Iterator<T>& it): ptr(it.ptr) {}
    bool operator ==(const Const_It &it) const {
        return ptr == it.ptr;
    }
    bool operator !=(const Const_It &it) const {
        return ptr != it.ptr;
    }
    const T& operator *() {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        return *ptr;
    }
    const T* operator ->() {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        return ptr;
    }
    Const_It& operator++() {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        ptr++;
        return *this;
    }
    Const_It operator ++(int) {
        if (!ptr) throw std::logic_error("Pointer is nullptr");
        Const_It buf(*this);
        ++*this;
        return buf;
    }
    int friend operator-(const Const_It& it1, const Const_It &it2) {
        if (!it1.ptr || !it2.ptr) throw std::logic_error("Pointer is nullptr");
        return it1.ptr - it2.ptr;
    }
};
#endif