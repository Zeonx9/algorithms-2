cmake_minimum_required(VERSION 3.23)
project(Algorithms2)

set(CMAKE_CXX_STANDARD 17)

add_executable(search search/main.cpp)

add_executable(2pointers 2pointers/main.cpp)

add_executable(linked_lists_stacks linked_lists_stacks/classes.h linked_lists_stacks/main.cpp)

add_executable(trees trees/src/AVLTree.cpp trees/include/AVLTree.h trees/include/BSTree.hpp trees/src/BSTree.cpp trees/main.cpp trees/src/RBTree.cpp trees/include/RBTree.h)