#ifndef TESTER_BINARY_SEARCH_TREE_NODEBT_H
#define TESTER_BINARY_SEARCH_TREE_NODEBT_H

#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>

template <typename T>
struct NodeBT {
    T data;
    NodeBT* left;
    NodeBT* right;
    NodeBT() : left(nullptr), right(nullptr) {}
    explicit NodeBT(T value) : data(value), left(nullptr), right(nullptr) {}

    void killSelf(){
        if(left) left->killSelf();
        if (right) right->killSelf();
    }
};

#endif //TESTER_BINARY_SEARCH_TREE_NODEBT_H
