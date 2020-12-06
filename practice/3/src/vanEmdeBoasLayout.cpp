//
// Created by tim on 01.12.20.
//

#include "vanEmdeBoasLayout.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <algorithm>

vanEmdeBoasLayout::vanEmdeBoasLayout(int n, bool fast) : size(std::pow(2, n) - 1), depth(0), h(n)
{
    tree2 = nullptr;
    bfs = new int[size];
    tree = nullptr;
    create_levels();
    if (fast)
    {
        generate_nodes_from_bfs();
    }
    else
    {
        generate_keys_from_bfs();
    }
    delete[] bfs;
    //std::vector<int> bfs = levell.get_bfs();

    //generate_keys_from_bfs(bfs);
    //print_vector(tree);

    /*
    //print_vector(extract_top(test));
    if (h % 2 == 0) {
        split(test);
    }
    else {
        int root_index = test.size() / 2;
        tree.push_back(test[root_index]);

        std::vector<int> left(test.begin(), test.begin() + root_index);
        std::vector<int> right(test.begin() + root_index + 1, test.end());
        split(left);
        split(right);
    }
    //split(test);
    print_vector(tree);
     */


    //for (int i = 0; i < size; i++) {
    //    std::cout << bfs_to_veb(i + 1, h) << std::endl;
    //}


}

int vanEmdeBoasLayout::find(int key)
{
    depth = 0;
    return find_rec(key, 1, 1);
}

int vanEmdeBoasLayout::find_rec(int key, int veb, int bfs)
{
    if (depth >= h) {
        std::cout << "key does not exist!" << std::endl;
        return -1;
    }
    int value = tree[veb - 1];
    if (value == key) {
        //std::cout << "found key " << key << " at depth: " << depth << std::endl;
        return value;
    }
    depth++;
    if (value < key) {
        int bfs_index = 2 * bfs + 1;
        int veb_index = bfs_to_veb(bfs_index, h);
        return find_rec(key, veb_index, bfs_index);
    }
    else {
        int bfs_index = 2 * bfs;
        int veb_index = bfs_to_veb(bfs_index, h);
        return find_rec(key, veb_index, bfs_index);
    }
}

void vanEmdeBoasLayout::print_keys()
{
    for (int i = 0; i < size; i++) {
        std::cout << bfs[i] << ", ";
    }
    std::cout << std::endl;
}
void vanEmdeBoasLayout::generate_keys_from_bfs()
{
    tree = new int[size];
    for (int i = 0; i < size; i++)
    {
        tree[bfs_to_veb(i + 1, h) - 1] = bfs[i];
    }
}


void vanEmdeBoasLayout::generate_keys(std::vector<int> &vec)
{
    generate_keys_rec(0, 0, vec, 0);
}

void vanEmdeBoasLayout::generate_keys_rec(int veb, int bfs, std::vector<int> &vec, int current_depth)
{
    if (current_depth == h) {
        return;
    }

    tree[veb] = vec[bfs];

    int left = bfs_to_veb(2*bfs+1,h);
    int right = bfs_to_veb(2*bfs+2,h);

    generate_keys_rec(left, 2*bfs+1, vec, current_depth + 1);
    generate_keys_rec(right, 2*bfs+2, vec, current_depth + 1);

}

void vanEmdeBoasLayout::create_levels()
{
    create_levels_rec((size + 1) /2, 0, (size + 1) / 2);
}

void vanEmdeBoasLayout::create_levels_rec(int key, int pos, int decrement) {
    // root
    bfs[pos] = key;
    if (decrement == 1) {
        return;
    }
    decrement /= 2;

    int left = key - decrement;
    int right = key + decrement;
    create_levels_rec(left, 2*pos + 1, decrement);
    create_levels_rec(right, 2*pos + 2, decrement);
}

void vanEmdeBoasLayout::split(std::vector<int>& vec)
{
    if (vec.size() == 3)
    {
        write_small_tree(vec);
        return;
    }
    if (vec.size() == 1) {
        //tree.push_back(vec[0]);
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
    //delete[] bfs;
    delete[] tree;
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
    //tree.push_back(vec[1]);
    //tree.push_back(vec[0]);
    //tree.push_back(vec[2]);
}

static inline int fls(int f)
{
    int order;
    for (order = 0; f; f >>= 1, order++) ;

    return order;
}

static inline int ilog2(int f)
{
    return fls(f) - 1;
}

static inline int hyperceil(int f)
{
    return 1 << fls(f-1);
}

// BFS Index to vEB index conversion algorithm
int vanEmdeBoasLayout::bfs_to_veb(int bfs_number, int height)
{
    int split;
    int top_height, bottom_height;
    int depth;
    int subtree_depth, subtree_root, num_subtrees;
    int toptree_size, subtree_size;
    unsigned int mask;
    int prior_length;

    /* if this is a size-3 tree, bfs number is sufficient */
    if (height <= 2)
        return bfs_number;

    /* depth is level of the specific node */
    depth = ilog2(bfs_number);

    /* the vEB layout recursively splits the tree in half */
    split = hyperceil((height + 1) / 2);
    bottom_height = split;
    top_height = height - bottom_height;

    /* node is located in top half - recurse */
    if (depth < top_height)
        return bfs_to_veb(bfs_number, top_height);

    /*
     * Each level adds another bit to the BFS number in the least
     * position.  Thus we can find the subtree root by shifting off
     * depth - top_height rightmost bits.
     */
    subtree_depth = depth - top_height;
    subtree_root = bfs_number >> subtree_depth;

    /*
     * Similarly, the new bfs_number relative to subtree root has
     * the bit pattern representing the subtree root replaced with
     * 1 since it is the new root.  This is equivalent to
     * bfs' = bfs / sr + bfs % sr.
     */

    /* mask off common bits */
    num_subtrees = 1 << top_height;
    bfs_number &= (1 << subtree_depth) - 1;

    /* replace it with one */
    bfs_number |= 1 << subtree_depth;

    /*
     * Now we need to count all the nodes before this one, then the
     * position within this subtree.  The number of siblings before
     * this subtree root in the layout is the bottom k-1 bits of the
     * subtree root.
     */
    subtree_size = (1 << bottom_height) - 1;
    toptree_size = (1 << top_height) - 1;

    prior_length = toptree_size +
                   (subtree_root & (num_subtrees - 1)) * subtree_size;

    return prior_length + bfs_to_veb(bfs_number, bottom_height);
}



int vanEmdeBoasLayout::height(int index)
{
    return std::log2(index);
}

int vanEmdeBoasLayout::find_fast(int key)
{
    depth = 0;
    return find_fast_rec(key,0, 0);
}

int vanEmdeBoasLayout::find_fast_rec(int key, int index, int current_depth)
{
    if (current_depth == h) {
        std::cout << "key not found"  << std::endl;
        return -1;
    }

    int value = tree2[index].value;

    if (value == key) {
        //std::cout << "key found"  << std::endl;
        return key;
    }
    if (key > value) {
        return find_fast_rec(key, tree2[index].right, current_depth + 1);
    }
    else {
        return find_fast_rec(key, tree2[index].left, current_depth + 1);
    }
}

void vanEmdeBoasLayout::generate_nodes_from_bfs()
{
    tree2 = new element[size];

    for (int i = 0; i < size; i++)
    {
        int value = bfs[i];
        int bfs_index = i + 1;
        int bfs_veb = bfs_to_veb(bfs_index, h) - 1;
        tree2[bfs_veb].value = value;
        int left_index = bfs_to_veb(2 * bfs_index, h) - 1;
        int right_index = bfs_to_veb(2 * bfs_index + 1, h) - 1;
        tree2[bfs_veb].left = left_index;
        tree2[bfs_veb].right = right_index;
    }

    /*
     *     if (value < key) {
        int bfs_index = 2 * bfs + 1;
        int veb_index = bfs_to_veb(bfs_index, h);
        return find_rec(key, veb_index, bfs_index);
    }
    else {
        int bfs_index = 2 * bfs;
        int veb_index = bfs_to_veb(bfs_index, h);
        return find_rec(key, veb_index, bfs_index);
    }
     */
}

















