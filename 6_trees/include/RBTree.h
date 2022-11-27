//
// Created by musht on 23.11.2022.
//

#ifndef ALGORITHMS2_RBTREE_H
#define ALGORITHMS2_RBTREE_H

enum class Colors {black, red};

template<class T>
struct RBTree {
    T key;
    Colors color;
    RBTree<T> *left, *right, *parent;
    RBTree(const T &k, RBTree<T> *l, RBTree<T> *r, RBTree<T> *p, Colors c);
    explicit RBTree(const T &k);
};

template<class T>
void insert(RBTree<T> *root, const T &k);

template<class T>
void remove(RBTree<T> *root, const T &k);

template<class T>
void print(RBTree<T> *root, int level);

#endif //ALGORITHMS2_RBTREE_H
