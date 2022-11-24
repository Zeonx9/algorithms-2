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
    return false;
}

void deleteRepeats(Node1 *head) {

}

int findLenOfCycledSomewhereList(Node1 *head) {
    return 0;
}

array findClosestDayForEveryDay(array &a);

int findLenOfCycledTrainWithLamps(Node2 *head);

bool areStringsWithBackSpacesEqual();


int main() {
    Node2 *head = nullptr;
    head = add(head, 5);
    add(head, 6);
    add(head, 18);
    print(head);
}