//
// Created by musht on 23.11.2022.
//

#include <iostream>
#include "../include/RBTree.h"

template struct RBTree<int>;
template void insert<int>(RBTree<int> *, const int &);
template void remove<int>(RBTree<int> *, const int &);
template void print<int>(RBTree<int> *, int);

template<class T>
RBTree<T>::RBTree(const T &k, RBTree<T> *l, RBTree<T> *r, RBTree<T> *p, Colors c) :
        key(k), left(l), right(r), parent(p), color(c) {}

template<class T>
RBTree<T>::RBTree(const T &k) : RBTree(k, nullptr, nullptr, nullptr, Colors::black) {}

template<class T>
RBTree<T> *grandpa(RBTree<T> *node) {
    if (node->parent)
        return node->parent->parent;
    return nullptr;
}

template<class T>
RBTree<T> *uncle(RBTree<T> *node) {
    auto granddad = grandpa(node);
    if (not granddad)
        return nullptr;
    if (granddad->left != node->parent)
        return granddad->left;
    else
        return granddad->right;
}

template<class T>
RBTree<T> *sibling(RBTree<T> *node) {
    if (not node->parent)
        return nullptr;
    if (node->parent->left == node)
        return node->parent->right;
    else
        return node->parent->left;
}

template<class T>
void rotate_left(RBTree<T> *root) {
    auto rr = root->right->right;
    root->right->right = root->right->left;
    root->right->left = root->left;
    if (root->left)
        root->left->parent = root->right;
    std::swap(root->key, root->right->key);
    root->left = root->right;
    root->right = rr;
    if (rr)
        rr->parent = root;
}

template<class T>
void rotate_right(RBTree<T> *root) {
    auto ll = root->left->left;
    root->left->left = root->left->right;
    root->left->right = root->right;
    if (root->right)
        root->right->parent = root->left;
    std::swap(root->key, root->left->key);
    root->right = root->left;
    root->left = ll;
    if (ll)
        ll->parent = root;
}

template<class T>
void balance_ins(RBTree<T> *n) {
    if (not n)
        return;

    if (not n->parent) {
        n->color = Colors::black;
        return;
    }

    if (n->parent->color == Colors::black) // if parent is black - everything is okay
        return;

    auto u = uncle(n);
    auto g = grandpa(n);

    if (u and u->color == Colors::red) { // red parent, red uncle
        g->color = Colors::red;
        n->parent->color = u->color = Colors::black;
        balance_ins(g); // swap colors, check grandpa
        return;
    }

    // red parent, black uncle
    if (n == n->parent->right and n->parent == g->left)
        rotate_left(g->left);
    else if (n == n->parent->left and n->parent == g->right)
        rotate_right(g->right);

    // colors wil be
    if (n == n->parent->left and n->parent == g->left)
        rotate_right(g);
    else
        rotate_left(g);

    balance_ins(g);
}

template<class T>
void insert(RBTree<T> *root, const T &k) {
    if (not root)
        return;

    auto cur = root;
    while (true) {
        if (k <= cur->key and cur->left)
            cur = cur->left;
        else if (k > cur->key and cur->right)
            cur = cur->right;
        else
            break;
    }

    auto node = new RBTree<T>(k, nullptr, nullptr, cur, Colors::red);
    if (k <= cur->key)
        cur->left = node;
    else
        cur->right = node;
    balance_ins(node);
}

template<class T>
bool is_black(RBTree<T> *n) {
    return not n or n->color == Colors::black;
}

template<class T>
void balance_rem(RBTree<T> *n) {
    // balance is only needed for black nodes
    if (not n->parent)
        return;

    auto s = sibling(n);
    // check for red sibling
    if (s->color == Colors::red) {
        if (n == n->parent->left)
            rotate_left(n->parent);
        else
            rotate_right(n->parent);
        s = sibling(n);
        if (not s)
            return;
    }
    // black sibling
    // both nephews are black
    if (is_black(s->left) and is_black(s->right)) {
        s->color = Colors::red;
        if (n->parent->color == Colors::red)
            n->parent->color = Colors::black;
        else
            balance_rem(n->parent);
        return;
    }
    // black outer nephew
    if (n == n->parent->left and is_black(s->right))
        rotate_right(s);
    else if (n == n->parent->right and is_black(s->left))
        rotate_left(s);

    // red outer nephew
    if (n == n->parent->left) {
        s->right->color = Colors::black;
        rotate_left(n->parent);
    } else {
        s->left->color = Colors::black;
        rotate_right(n->parent);
    }
}

template<class T>
void remove(RBTree<T> *root, const T &k) {
    if (not root)
        return;

    if (k < root->key) {
        remove(root->left, k);
        return;
    }
    if (k > root->key) {
        remove(root->right, k);
        return;
    }

    if (not root->left and not root->right) {
        if (not root->parent) // attempt to remove the last node
            return;
        if (root->color == Colors::black)
            balance_rem(root);
        if (root->parent->left == root)
            root->parent->left = nullptr;
        else
            root->parent->right = nullptr;
        delete root;
        return;
    }

    if (not root->left or not root->right) {
        if (root->left) {
            root->key = root->left->key;
            delete root->left;
            root->left = nullptr;
        } else {
            root->key = root->right->key;
            delete root->right;
            root->right = nullptr;
        }
        return;
    }

    auto cur = root->right;
    while (cur->left)
        cur = cur->left;
    root->key = cur->key;
    remove(cur, cur->key);
}

template<class T>
void print(RBTree<T> *root, int level) {
    if (root->right) {
        print(root->right, level + 1);
    }
    for (int i = level; i > 0; --i)
        std::cout << "\t";
    std::cout << root->key << (root->color == Colors::red ? "R" : " ") << "\n";
    if (root->left) {
        print(root->left, level + 1);
    }
}
