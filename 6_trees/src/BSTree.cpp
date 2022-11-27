//
// Created by musht on 19.11.2022.
//

#include <iostream>
#include "../include/BSTree.hpp"

template struct BSTree<int>;
template BSTree<int> *insert<int>(BSTree<int> *, const int &);
template BSTree<int> *remove<int>(BSTree<int> *, const int &);
template void print<int>(BSTree<int> *, int);

template<class T>
BSTree<T>::BSTree(const T &k, BSTree<T> *l, BSTree<T> *r, BSTree<T> *p) :
        key(k), left(l), right(r), parent(p) {}

template <class T>
BSTree<T> *insert(BSTree<T> *root, const T &k) {
    if (not root)
        return new BSTree<T>(k, nullptr, nullptr, nullptr);

    if (k <= root->key) {
        root->left = insert(root->left, k);
        root->left->parent = root;
    } else {
        root->right = insert(root->right, k);
        root->right->parent = root;
    }
    return root;
}

template<class T>
void print(BSTree<T> *root, int level) {
    if (root->right) {
        print(root->right, level + 1);
    }
    for (int i = level; i > 0; --i)
        std::cout << "\t";
    std::cout << root->key << "\n";
    if (root->left) {
        print(root->left, level + 1);
    }
}

template<class T>
BSTree<T> *remove(BSTree<T> *root, const T &k) {
    if (not root) {
        return nullptr;
    }
    if (k < root->key) {
        root->left = remove(root->left, k);
        return root;
    }
    if (k > root->key) {
        root->right = remove(root->right, k);
        return root;
    }

    if (not root->right and not root->left) { // removing leaf
        delete root;
        return nullptr;
    }
    if (not root->left or not root->right) {
        auto child = root->left ? root->left : root->right;
        child->parent = root->parent;
        delete root;
        return child;
    }
    auto cur = root->right;
    while (cur->left)
        cur = cur->left;
    root->key = cur->key;
//    if (cur->parent->left == cur) {
//        cur->parent->left = remove(cur, cur->key);
//    } else {
//        cur->parent->right = remove(cur, cur->key);
//    }
    root->right = remove(root->right, cur->key);
    return root;
}
