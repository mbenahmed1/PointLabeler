//
// Created by tim on 30.11.20.
//

#include <iostream>
#include "levelLayout.hpp"
#include <cmath>


levelLayout::levelLayout(int n) : size(std::pow(2, n) - 1), depth(0)
{
    //std::cout << size << std::endl;
    level_keys = new int[size];
    create_levels();
    //print_keys();
}

int levelLayout::find(int key)
{
    depth = 0;
    return find_rec(key, 0);
}

int levelLayout::find_rec(int key, int current_node)
{
    if (current_node >= size) {
        //std::cout << "key does not exist!" << std::endl;
        return -1;
    }
    int value = level_keys[current_node];
    if (value == key) {
        //std::cout << "found key " << value << " at depth: " << depth << std::endl;
        return value;
    }
    depth++;
    if (value < key) {
        return find_rec(key, 2 * current_node + 2);
    }
    else {
        return find_rec(key, 2 * current_node + 1);
    }
}

void levelLayout::create_levels()
{
    create_levels_rec((size + 1) /2, 0, (size + 1) / 2);
}

void levelLayout::create_levels_rec(int key, int pos, int decrement) {
    // root
    level_keys[pos] = key;
    if (decrement == 1) {
        return;
    }
    decrement /= 2;

    int left = key - decrement;
    int right = key + decrement;
    create_levels_rec(left, 2*pos + 1, decrement);
    create_levels_rec(right, 2*pos + 2, decrement);
}

void levelLayout:: print_keys() {
    for (int i = 0; i < size; i++) {
        std::cout << level_keys[i] << ", ";
    }
    std::cout << std::endl;
}

levelLayout::~levelLayout()
{
    delete[] level_keys;
}

std::vector<int> levelLayout::get_bfs()
{
    std::vector<int> bfs;
    for (int i = 0; i < size; i++)
    {
        bfs.push_back(level_keys[i]);
    }
    return bfs;
}
