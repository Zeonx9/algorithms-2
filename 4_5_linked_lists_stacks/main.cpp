//
// Created by musht on 07.11.2022.
//

#include "classes.h"
#include <iostream>
#include <vector>

using array = std::vector<int>;

bool isSymmetric2(Node2 *head) {
    auto end = head;
    while (end->next != nullptr) end = end->next;

    while (head < end) {
        if (head->val != end->val)
            return false;
        head = head->next;
        end = end->prev;
    }
    return head == end;
}

bool isSymmetric1(Node1 *head) {
    int n = 1;
    auto cur = head;
    while (cur->next) {
        ++n;
        cur = cur->next;
    }
    auto tail = cur;
    cur = head;
    for (int i = 0; i < (n - 1) / 2; ++i) {
        cur = cur->next;
    }
    auto next = cur->next;
    while (next) {
        auto tmp = next->next;
        next->next = cur;
        cur = next;
        next = tmp;
    }
    while (not (head->next == tail and tail->next == head) and head != tail) {
        if (head->val != tail->val)
            return false;
        head = head->next;
        tail = tail->next;
    }
    return head->val == tail->val;
}

void deleteRepeats(Node1 *head) {
    auto cur = head;
    while (cur->next) {
        auto t = cur;
        while(t->next) {
            if (t->next->val == cur->val) {
                auto cpy = t->next;
                t->next = t->next->next;
                delete cpy;
            } else
                t = t->next;
        }
        cur = cur->next;
    }
}

int findLenOfCycledSomewhereList(Node1 *head) {
    return 0;
}

array findClosestDayForEveryDay(array &a);

int findLenOfCycledTrainWithLamps(Node2 *head);

bool areStringsWithBackSpacesEqual(const std::string &s1, const std::string &s2) {
    return false;
}

Node1 *reverse(Node1 *head) {
    Node1 *cur = head;
    Node1 *prv = nullptr;
    while (cur) {
        Node1 *nxt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nxt;
    }
    return prv;
}


int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    auto head = makeFromVector1(v);
    print(head);
    std::cout << "\n";
    auto rev_head = reverse(head);
    print(rev_head);
//    std::cout << "\n" << (isSymmetric1(head) ? "yes" : "no") << "\n";
}