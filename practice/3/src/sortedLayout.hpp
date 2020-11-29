//
// Created by tim on 29.11.20.
//

#ifndef SEARCHTREELAYOUT_SORTEDLAYOUT_HPP
#define SEARCHTREELAYOUT_SORTEDLAYOUT_HPP


class sortedLayout
{
public:

    explicit sortedLayout(int keys[], int size);

    int find(int key);

private:

    int find_rec(int key, int a, int b);

    int depth;
    int* sorted_keys;
    int size;
};


#endif //SEARCHTREELAYOUT_SORTEDLAYOUT_HPP
