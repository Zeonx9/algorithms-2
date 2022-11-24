//
// Created by musht on 07.11.2022.
//

#ifndef ALGORITHMS2_CLASSES_H
#define ALGORITHMS2_CLASSES_H

#include <iostream>

struct Node2 {
   int val;
   Node2 *next, *prev;
   Node2(int v, Node2 *n, Node2 *p) : next(n), val(v), prev(p) {}
};

Node2 * add(Node2 *n, int v) {
    if (not n)
        return new Node2(v, nullptr, nullptr);
    else {
        n->next = add(n->next, v);
        n->next->prev = n;
        return n;
    }
}

void print(Node2 *n) {
    if (n) {
        std::cout << n->val << " ";
        print(n->next);
    }
}

struct Node1 {
    int val;
    Node1 *next;
    Node1(int v, Node1 *n) : next(n), val(v) {}
};

Node1 * add(Node1 *n, int v) {
    if (not n)
        return new Node1(v, nullptr);
    else {
        n->next = add(n->next, v);
        return n;
    }
}


#endif //ALGORITHMS2_CLASSES_H
