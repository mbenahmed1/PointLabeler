#include <iostream>
#include <cmath>
#include "sortedLayout.hpp"
#include "randomLayout.hpp"
#include "levelLayout.hpp"

/* Example perfectly balanced binary search tree
               4
            /    \
           2      6
         /  \    /  \
        1    3  5    7
 */
int main()
{
    int n = 6;

    sortedLayout layout(n);
    //randomLayout layout(n);
    //levelLayout layout(n);

    layout.find(63);
}



