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
    std::vector<int> keys;
    for (int i = 0; i < size; i++) {
        keys.push_back(i+1);
    }
    // shuffle keys
    random_keys = new int[size];


    std::shuffle(keys.begin(), keys.end(), std::default_random_engine(314));

    for (int i = 0; i < size; i++) {
        random_keys[i] = keys[i];
    }
}

int randomLayout::find(int key)
{
    for (int i = 0; i < size; i++)
    {
        if (random_keys[i] == key) {
            //std::cout << "found key: " << key  << " at pos: " << i << std::endl;
            return random_keys[i];
        }
    }
    std::cout << "key does not exist" << std::endl;
    return -1;
}

int randomLayout::find_rec(int key, int a, int b)
{
    return 0;
}

randomLayout::~randomLayout()
{
    delete[] random_keys;
}

void randomLayout::print_keys()
{
    for (int i = 0; i < size; i++) {
        std::cout << random_keys[i] << ", ";
    }
    std::cout << std::endl;
}
