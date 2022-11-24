//
// Created by musht on 19.11.2022.
//

#ifndef ALGORITHMS2_AVLTREE_H
#define ALGORITHMS2_AVLTREE_H

template <class T>
struct AVLTree {
public:
    T key;
    int height;
    AVLTree<T> *left, *right, *parent;

    AVLTree(const T &k, AVLTree<T> *l, AVLTree<T> *r, AVLTree<T> *p, int h);
};

template <class T>
AVLTree<T> *insert(AVLTree<T> *root, const T &k);


template <class T>
AVLTree<T> *remove(AVLTree<T> *root, const T &k);

template <class T>
void print(AVLTree<T> *root, int level);


#endif //ALGORITHMS2_AVLTREE_H
