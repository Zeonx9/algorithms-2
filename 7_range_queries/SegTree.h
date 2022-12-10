//
// Created by musht on 10.12.2022.
//

#ifndef ALGORITHMS2_SEGTREE_H
#define ALGORITHMS2_SEGTREE_H

#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

template<class T>
class SegTree {
private:
    const T &neutral;
    std::vector<T> tree;
    std::function<T (const T&, const T&)> func;

    void build(int cur, int l, int r, const std::vector<T> &values) {
        if (l == r) {
            tree[cur] = values[l];
            return;
        }
        int mid = (l + r) / 2, lch = cur * 2, rch = lch + 1;
        build(lch, l, mid, values);
        build(rch, mid + 1, r, values);
        tree[cur] = func(tree[lch], tree[rch]);
    }

    T calc(int cur, int a, int b, int l, int r) {
        if (b < l or r < a)
            return neutral;
        if (a <= l and r <= b)
            return tree[cur];
        int mid = (l + r + 1) / 2, lch = cur * 2, rch = lch + 1;
        auto x = calc(lch, a, b, l, mid),
             y = calc(rch, a, b, mid + 1, r);
        return func(x, y);
    }

    void print(int depth, int cur) {
        if (cur * 2 < tree.size())
            print(depth + 1, cur * 2 + 1);
        for (int i = 0; i < depth; ++i)
            std::cout << "\t";
        std::cout << tree[cur] << "\n";
        if (cur * 2  + 1 < tree.size())
            print(depth + 1, cur * 2);
    }
public:
    SegTree(const std::vector<T> &values, std::function<T (const T&, const T&)> f, const T &n) :
        neutral(n), func(f) {
        auto v2 = values;
        int h = 1;
        while (h < v2.size())
            h <<= 1;
        for (int i = v2.size(); i < h; ++i)
            v2.push_back(neutral);

        tree = std::vector<T>(2 * h, neutral);
        build(1, 0, h - 1, v2);
    }

    T query(int i, int j) {
        return calc(1, i, j, 0, tree.size() / 2 - 1);
    }

    void print() {
        print(0, 1);
    }
};

#endif //ALGORITHMS2_SEGTREE_H
