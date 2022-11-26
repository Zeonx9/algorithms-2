//
// Created by musht on 26.11.2022.
//

#include "../include/Heap.h"
template class Heap<int>;

template<class T>
void swap(std::vector<T> &a, int i, int j) {
    auto tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

template<class T>
void down(std::vector<T> &a, int i, bool (*f)(const T &, const T &)) {
    int j = 2 * i + 1, k = j + 1;
    if (k == a.size()) {
        if (not f(a[i], a[j]))
            swap(a, i, j);
        return;
    }
    if (j >= a.size())
        return;

    auto w = f(a[j], a[k]) ? j : k;
    if (not f(a[i], a[w]))
        swap(a, i, w);
    down(a, w, f);
}

template<class T>
Heap<T> Heap<T>::heapify(std::vector<T> &a, bool (*func)(const T &, const T &)) {
    auto e = 1;
    while ((e << 1) - 1 < a.size())
        e <<= 1;
    e -= 1;
    auto s = e >> 1;
    while (s < e) {
        for (int i = s; i < e; ++i)
            down(a, i, func);
        e = s;
        s >>= 1;
    }
    return Heap<T>(a, func);
}

template <class T>
void up(std::vector<T> &a, int i, bool (*f)(const T &, const T &)) {
    int p = (i - 1) / 2;
    if (i > 0) {
        if (not f(a[p], a[i])) {
            swap(a, i, p);
            up(a, p, f);
        }
    }
}

template<class T>
Heap<T> &Heap<T>::add(const T &elem) {
    arr.push_back(elem);
    up(arr, arr.size() - 1, comp);
    return *this;
}

template<class T>
T Heap<T>::pop() {
    auto elem = arr[0];
    swap(arr, 0, arr.size() - 1);
    arr.pop_back();
    down(arr, 0, comp);
    return elem;
}

template<class T>
std::vector<T> Heap<T>::as_array() {
    return arr;
}
