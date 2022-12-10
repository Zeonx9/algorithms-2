//
// Created by musht on 10.12.2022.
//

#include "SegTree.h"
#include <string>
#include <iostream>

using str = std::string;

int main() {
    auto str_segtr = SegTree<str>(
            (std::vector<str>){"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"},
            [](const std::string &a, const std::string &b) {return  a + b;},
            "");
    auto int_st = SegTree<int>(
            (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            [](const int &a, const int &b) {return a + b;},
            0);
    auto st_int_min = SegTree<int>(
            (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            [](const int &a, const int &b) {return a < b ? a : b;},
            10);

    std::cout << int_st.query(0, 2) << "\n";
    std::cout << str_segtr.query(3, 7) << "\n";
    std::cout << st_int_min.query(3, 7) << "\n";

    int_st.print();
    return 0;
}
