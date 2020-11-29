//
// Created by tim on 29.11.20.
//

#include "randomLayout.hpp"
#include "algorithm"
#include <vector>
#include <random>
#include <iostream>

randomLayout::randomLayout(int *keys, int size) : size(size), depth(0)
{
    // shuffle keys
    random_keys = new int[size];
    key_indices = new int[size];

    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = keys[i];
    }

    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(314));

    for (int i = 0; i < size; i++) {
        random_keys[i] = vec[i];
    }

    // save indices
    for (int i = 0; i < size; i++) {
        key_indices[random_keys[i]] = i;
    }
}

int randomLayout::find(int key)
{
    return 0;
}

int randomLayout::find_rec(int key, int a, int b)
{
    return 0;
}
