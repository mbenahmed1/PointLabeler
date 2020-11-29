//
// Created by tim on 30.11.20.
//

#include "levelLayout.hpp"

levelLayout::levelLayout(int *keys, int size) : sorted_keys(keys) , size(size)
{
    level_keys = new int[size];
}

int levelLayout::find(int key)
{
    return 0;
}

int levelLayout::find_rec(int key, int a, int b)
{
    return 0;
}

void levelLayout::create_levels()
{

}
