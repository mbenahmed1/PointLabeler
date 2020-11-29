//
// Created by tim on 30.11.20.
//

#ifndef SEARCHTREELAYOUT_LEVELLAYOUT_HPP
#define SEARCHTREELAYOUT_LEVELLAYOUT_HPP

class levelLayout
{
public:

    explicit levelLayout(int keys[], int size);

    int find(int key);

private:

    int find_rec(int key, int a, int b);

    void create_levels();

    int depth;
    int* sorted_keys;
    int* level_keys;
    int size;
};

#endif //SEARCHTREELAYOUT_LEVELLAYOUT_HPP
