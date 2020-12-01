//
// Created by tim on 29.11.20.
//

#ifndef SEARCHTREELAYOUT_RANDOMLAYOUT_HPP
#define SEARCHTREELAYOUT_RANDOMLAYOUT_HPP


class randomLayout
{
public:

    explicit randomLayout(int n);

    int find(int key);

    ~randomLayout();

private:

    int find_rec(int key, int a, int b);

    int depth;
    int* random_keys;
    int* key_indices;
    int size;
};


#endif //SEARCHTREELAYOUT_RANDOMLAYOUT_HPP
