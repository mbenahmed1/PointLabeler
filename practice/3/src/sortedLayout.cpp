//
// Created by tim on 29.11.20.
//

#include <iostream>
#include <cmath>
#include "sortedLayout.hpp"

sortedLayout::sortedLayout(int n) : size(std::pow(2, n) - 1), depth(0)
{
    sorted_keys = new int[size];

    for (int i = 0; i < size; i++) {
        sorted_keys[i] = i+1;
    }
}

int sortedLayout::find(int key)
{
    depth = 0;
    return find_rec(key, 0, size - 1);
}

int sortedLayout::find_rec(int key, int a, int b) {

    int root_index = (a + b) / 2;
    int current_key = sorted_keys[root_index];

    if (current_key == key) {
        std::cout << "found key " << key << " at depth: " << depth << std::endl;
        return current_key;
    }
    if (a == b) {
        std::cout << "key does not exist" << std::endl;
        return -1;
    }
    depth++;
    if (key < current_key) {
        return find_rec(key, a, root_index - 1);
    }
    if (key > current_key) {
        return find_rec(key, root_index + 1, b);
    }
}

sortedLayout::~sortedLayout()
{
    delete[] sorted_keys;
}




