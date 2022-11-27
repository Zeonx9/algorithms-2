//
// Created by musht on 26.11.2022.
//

#ifndef ALGORITHMS2_HEAP_H
#define ALGORITHMS2_HEAP_H

#include <vector>

template<class T>
class Heap {
private:
    std::vector<T> arr;
    bool (*comp)(const T &, const T &);
public:
    Heap(std::vector<T> &a, bool (*func)(const T &, const T &)) : arr(a), comp(func) {}
    explicit Heap(bool (*func)(const T &, const T &)) : comp(func){}
    static Heap<T> heapify(std::vector<T> &a, bool (*func)(const T &, const T &));

    Heap<T> &add(const T &elem);

    T pop();

    std::vector<T> as_array();
};

#endif //ALGORITHMS2_HEAP_H
