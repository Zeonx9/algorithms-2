//
// Created by musht on 19.11.2022.
//

#ifndef ALGORITHMS2_BSTREE_HPP
#define ALGORITHMS2_BSTREE_HPP

template <class T>
struct BSTree {
public:
    BSTree<T> *left, *right, *parent;
    T key;

    BSTree(const T &k, BSTree<T> *l, BSTree<T> *r, BSTree<T> *p);
};

template <class T>
BSTree<T> *insert(BSTree<T> *root, const T &k);

template <class T>
BSTree<T> *remove(BSTree<T> *root, const T &k);

template <class T>
void print(BSTree<T> *root, int level);

#endif //ALGORITHMS2_BSTREE_HPP
