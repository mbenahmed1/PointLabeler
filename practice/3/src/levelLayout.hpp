//
// Created by tim on 30.11.20.
//

#ifndef SEARCHTREELAYOUT_LEVELLAYOUT_HPP
#define SEARCHTREELAYOUT_LEVELLAYOUT_HPP

#include <vector>

class levelLayout
{
public:

    explicit levelLayout(int n, bool fast);

    int find(int key);

    int find_fast(int key);

    ~levelLayout();

    int* level_keys;

    std::vector<int> get_bfs();

private:

    typedef struct{
        int value;
        int left;
        int right;
    }element;

    element* level_nodes;

    int find_rec(int key, int current_node);

    int find_fast_rec(int key, int current_node);

    void create_levels();

    void create_level_nodes();

    void create_levels_rec(int key, int pos, int decrement);

    void print_keys();

    int depth;

    int size;
};

#endif //SEARCHTREELAYOUT_LEVELLAYOUT_HPP
