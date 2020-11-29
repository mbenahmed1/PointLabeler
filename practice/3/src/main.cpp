#include <iostream>
#include <cmath>
#include "sortedLayout.hpp"
#include "randomLayout.hpp"

/* Example perfectly balanced binary search tree
               4
            /    \
           2      6
         /  \    /  \
        1    3  5    7
 */
int* generate_keys(int n) {

    int size = std::pow(2, n) - 1;
    //std::cout << size << std::endl;
    int* keys = new int[size];

    for (int i = 0; i < size; i++) {
        keys[i] = i+1;
        //std::cout << i + 1 << std::endl;
    }

    return keys;
}

int main()
{
    //int keys[] = {1,2,3,4,5,6,7};
    int n = 10;
    int *keys = generate_keys(n);

    sortedLayout layout(keys, std::pow(2, n) - 1);
    //randomLayout layout(keys, std::pow(2, n) - 1);

    layout.find(1023);
}



