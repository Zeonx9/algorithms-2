//
// Created by musht on 19.11.2022.
//
#include <iostream>
#include "include/BSTree.hpp"
#include "include/AVLTree.h"
#include "include/RBTree.h"

int main() {
    auto *tree = new RBTree<int>(31);
    for (int i = 30; i >= 1; --i) {
        insert(tree, i);
        std::cout << "=============================================================\n";
        print(tree, 0);
    }
//    std::cout << "=============================================================\n";
//    print(tree, 0);
//    for (int i = 0; i < 30; ++i) {
//        tree = remove(tree, tree->key);
//        std::cout << "=============================================================\n";
//        print(tree, 0);
//    }
//    tree = remove(tree, tree->key);
//    std::cout << tree;
}