//
// Created by musht on 21.12.2022.
//
#include <iostream>
#include "structures.h"

int main() {
//    PerStack s;
//    for (int i = 0; i < 5; ++i) {
//        s.push(i);
//    }
//    s.backTo(2);
//    s.pop();
//    s.push(5);
//    s.backTo(3);
//    while(s.has_elements())
//        std::cout << s.pop() << "\n";
//    std::vector<int> v;
//    for (int i = 0; i < 50; ++i)
//        v.push_back(i);
//    ListNode *ll = fromVector(v, 10);
//    auto *rr = reverse(ll);

    Queue q;
    for (int i = 0; i < 5; ++i)
        q.push(i);
    while (q.has_elements())
        std::cout << q.pop() << "\n";
}
