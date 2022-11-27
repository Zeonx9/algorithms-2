//
// Created by musht on 19.11.2022.
//
#include <iostream>
#include "include/BSTree.hpp"
#include "include/AVLTree.h"
#include "include/RBTree.h"
#include "include/Heap.h"

using array = std::vector<int>;

int getMinTimeLaundry(array &times, int k) {
    array sums(k, 0);
    for(auto t : times) {
        auto min_ind = 0;
        for (int i = 1; i < k; ++i) {
            if (sums[min_ind] > sums[i])
                min_ind = i;
        }
        sums[min_ind] += t;
    }
    auto max_t = sums[0];
    for (auto t : sums)
        if (t > max_t)
            max_t = t;
    return max_t;
}
bool func(const int &a, const int &b) {
    return a < b;
}

int getMimTimeLaundryHeap(array &times, int k) {
    Heap<int> heap(&func);
    for (int i = 0; i < times.size(); ++i) {
        if (i < k)
            heap.add(times[i]);
        else {
            auto min_t = heap.pop();
            heap.add(min_t + times[i]);
        }
    }
    auto v = heap.as_array();
    auto max_t = v[0];
    for (auto t : v)
        max_t = std::max(max_t, t);
    return max_t;
}
int getMinFromTree(AVLTree<int> *tree) {
    while (tree->left) {
        tree = tree->left;
    }
    return tree->key;
}
int getMaxFromTree(AVLTree<int> *tree) {
    while (tree->right) {
        tree = tree->right;
    }
    return tree->key;
}

int getMimTimeLaundryAVLTree(array &times, int k) {
    AVLTree<int> *tree = nullptr;
    for (int i = 0; i < times.size(); ++i) {
        if (i < k)
            tree = insert(tree, times[i]);
        else {
            auto min_t = getMinFromTree(tree);
            tree = remove(tree, min_t);
            tree = insert(tree, min_t + times[i]);
        }
    }
    return getMaxFromTree(tree);
}


int main() {
    std::vector<int> a{5, 2, 2, 3, 1};
    std::cout << getMinTimeLaundry(a, 2) << "\n";
    std::cout << getMimTimeLaundryHeap(a, 2) << "\n";
    std::cout << getMimTimeLaundryAVLTree(a, 2) << "\n";
}


#ifdef RBTREE_TEST
int main() {
    auto *tree = new RBTree<int>(1);
    for (int i = 2; i < 32; ++i) {
        insert(tree, i);
    }
    print(tree, 0);
    for (int i = 0; i < 31; ++i) {
        remove(tree, tree->key);
        std::cout << "=============================================================\n";
        print(tree, 0);
    }
}
#endif