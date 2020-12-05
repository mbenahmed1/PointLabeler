//
// Created by tim on 01.12.20.
//

#include "vanEmdeBoasLayout.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <algorithm>

vanEmdeBoasLayout::vanEmdeBoasLayout(int n) : size(std::pow(2, n) - 1), depth(0), h(n), tree()
{
    keys = new int[size];
    generate_keys();
    print_keys();

    // extract top test
    std::vector<int> test;
    for (int i = 0; i < size; i++) {
        test.push_back(i + 1);
    }

    print_vector(test);

    //print_vector(extract_top(test));
    split(test);
    print_vector(tree);

}

int vanEmdeBoasLayout::find(int key)
{
    return 0;
}

int vanEmdeBoasLayout::find_rec(int key, int current_node)
{
    return 0;
}

void vanEmdeBoasLayout::print_keys()
{
    for (int i = 0; i < size; i++) {
        std::cout << keys[i] << ", ";
    }
    std::cout << std::endl;
}

void vanEmdeBoasLayout::generate_keys()
{

}

void vanEmdeBoasLayout::split(std::vector<int>& vec)
{
    if (vec.size() == 3)
    {
        write_small_tree(vec);
        return;
    }
    if (vec.size() == 1) {
        tree.push_back(vec[0]);
        return;
    }
    // two halves a and b
    std::vector<std::vector<int>> all = get_halves(vec);
    std::vector<int> a = all[0];
    std::vector<int> b = all[1];

    // split a
    int subtree_count = a.size() + 1;
    int subtree_size = b.size() / subtree_count;
    split(a);

    // foreach tree c in b: split c
    for (int i = 0; i < b.size(); i+=subtree_size) {
        std::vector<int> c(b.begin() + i, b.begin() + i + subtree_size);
        split(c);
    }

}


vanEmdeBoasLayout::~vanEmdeBoasLayout()
{
    delete[] keys;
}



std::vector<std::vector<int>> vanEmdeBoasLayout::get_halves(std::vector<int> &vec)
{
    std::vector<std::vector<int>> all;

    std::vector<int> a;

    std::vector<int> top = extract_top(vec);

    std::vector<int> rest;

    std::set<int> top_set(top.begin(), top.end());
    std::set<int> vec_set(vec.begin(), vec.end());

    std::set_difference(vec_set.begin(), vec_set.end(), top_set.begin(), top_set.end(), std::back_inserter(rest));

    all.push_back(top);
    all.push_back(rest);

    return all;
}

std::vector<int> vanEmdeBoasLayout::extract_top(std::vector<int> &a)
{
    std::vector<int> b;
    extract_top_rec(a, b, 0, get_height(a) / 2);
    std::sort(b.begin(), b.end());
    return b;
}

void vanEmdeBoasLayout::extract_top_rec(std::vector<int> &vec_in, std::vector<int> &vec_out, int current_level, int max_level)
{
    if (current_level == max_level) {
        return;
    }

    current_level++;

    int root_index = vec_in.size() / 2;

    int root = vec_in[root_index];
    vec_out.push_back(root);

    std::vector<int> left(vec_in.begin(), vec_in.begin() + root_index);
    std::vector<int> right(vec_in.begin() + root_index + 1, vec_in.end());


    extract_top_rec(left, vec_out, current_level, max_level);
    extract_top_rec(right, vec_out, current_level, max_level);
}

int vanEmdeBoasLayout::get_height(const std::vector<int> &vec)
{
    return std::log2(vec.size() + 1);
}

void vanEmdeBoasLayout::print_vector(const std::vector<int> & vec)
{
    for (int i : vec)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

void vanEmdeBoasLayout::write_small_tree(std::vector<int> &vec)
{
    std::sort(vec.begin(), vec.end());
    tree.push_back(vec[1]);
    tree.push_back(vec[0]);
    tree.push_back(vec[2]);
}












