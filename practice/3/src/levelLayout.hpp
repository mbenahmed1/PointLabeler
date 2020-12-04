//
// Created by tim on 30.11.20.
//

#ifndef SEARCHTREELAYOUT_LEVELLAYOUT_HPP
#define SEARCHTREELAYOUT_LEVELLAYOUT_HPP

#include <vector>

class levelLayout
{
public:

    explicit levelLayout(int n);

    int find(int key);

    ~levelLayout();

    int* level_keys;

private:

    int find_rec(int key, int current_node);

    void create_levels();

    void create_levels_rec(int key, int pos, int decrement);

    void print_keys();

    int depth;

    int size;
};

#endif //SEARCHTREELAYOUT_LEVELLAYOUT_HPP
