//
// Created by tim on 29.11.20.
//

#include <iostream>
#include "sortedLayout.hpp"

sortedLayout::sortedLayout(int *keys, int size) : sorted_keys(keys), size(size), depth(0)
{
}

int sortedLayout::find(int key)
{
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




