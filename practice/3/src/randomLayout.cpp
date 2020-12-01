//
// Created by tim on 29.11.20.
//

#include "randomLayout.hpp"
#include "algorithm"
#include <vector>
#include <random>
#include <iostream>
#include <cmath>

randomLayout::randomLayout(int n) : size(std::pow(2, n) - 1), depth(0)
{
    // generate keys
    int* keys = new int[size];
    for (int i = 0; i < size; i++) {
        keys[i] = i+1;
    }
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

    delete[] keys;
}

int randomLayout::find(int key)
{
    return 0;
}

int randomLayout::find_rec(int key, int a, int b)
{
    return 0;
}

randomLayout::~randomLayout()
{
    delete[] key_indices;
    delete[] random_keys;
}
