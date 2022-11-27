cmake_minimum_required(VERSION 3.23)
project(Algorithms2)

set(CMAKE_CXX_STANDARD 17)

add_executable(1_search 1_search/main.cpp)

add_executable(2_missed_number 2_missed_number/main.cpp)

add_executable(3_two_pointers 3_two_pointers/main.cpp)

add_executable(4_linked_lists_stacks 4_linked_lists_stacks/classes.h 4_linked_lists_stacks/main.cpp)

add_executable(6_trees 6_trees/src/AVLTree.cpp 6_trees/include/AVLTree.h 6_trees/include/BSTree.hpp 6_trees/src/BSTree.cpp 6_trees/main.cpp 6_trees/src/RBTree.cpp 6_trees/include/RBTree.h 6_trees/src/Heap.cpp 6_trees/include/Heap.h)