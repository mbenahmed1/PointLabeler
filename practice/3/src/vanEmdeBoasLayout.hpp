//
// Created by tim on 01.12.20.
//

#ifndef SEARCHTREELAYOUT_VANEMDEBOASLAYOUT_HPP
#define SEARCHTREELAYOUT_VANEMDEBOASLAYOUT_HPP


#include <vector>

class vanEmdeBoasLayout
{
public:

    explicit vanEmdeBoasLayout(int n);

    int find(int key);

    ~vanEmdeBoasLayout();

private:

    int find_rec(int key, int current_node);

    void generate_keys();

    void split(std::vector<int>& vec);

    std::vector<std::vector<int>> get_halves(std::vector<int> &vec);

    std::vector<int> extract_top(std::vector<int> &vec);

    void extract_top_rec(std::vector<int> &vec_in, std::vector<int> &vec_out, int current_level, int max_level);

    int get_height(const std::vector<int> &vec);

    void write_small_tree(std::vector<int> &vec);

    void print_keys();

    void print_vector(const std::vector<int> &vec);

    std::vector<int> tree;
    int h;
    int depth;
    int* keys;
    int size;
};


#endif //SEARCHTREELAYOUT_VANEMDEBOASLAYOUT_HPP
