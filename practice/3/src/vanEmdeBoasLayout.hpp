//
// Created by tim on 01.12.20.
//

#ifndef SEARCHTREELAYOUT_VANEMDEBOASLAYOUT_HPP
#define SEARCHTREELAYOUT_VANEMDEBOASLAYOUT_HPP


#include <vector>

class vanEmdeBoasLayout
{
public:

    explicit vanEmdeBoasLayout(int n, bool fast);

    int find(int key);

    int find_fast(int key);

    ~vanEmdeBoasLayout();

private:


    typedef struct{
        int value;
        int left;
        int right;
    }element;

    int find_rec(int key, int veb, int bfs);

    int find_fast_rec(int key, int index, int current_depth);

    void generate_keys(std::vector<int> &vec);

    void generate_keys_from_bfs();

    void generate_nodes_from_bfs();

    void generate_keys_rec(int index, int element, std::vector<int> &vec, int current_depth);

    void split(std::vector<int>& vec);

    std::vector<std::vector<int>> get_halves(std::vector<int> &vec);

    std::vector<int> extract_top(std::vector<int> &vec);

    void extract_top_rec(std::vector<int> &vec_in, std::vector<int> &vec_out, int current_level, int max_level);

    int get_height(const std::vector<int> &vec);

    void write_small_tree(std::vector<int> &vec);

    void print_keys();

    int bfs_to_veb(int index, int h);

    void create_levels();

    void create_levels_rec(int key, int pos, int decrement);

    int height(int index);

    void print_vector(const std::vector<int> &vec);

    int* tree;
    element* tree2;
    int h;
    int depth;
    int* bfs;
    int size;
};


#endif //SEARCHTREELAYOUT_VANEMDEBOASLAYOUT_HPP
