#include <iostream>
#include <cmath>
#include "sortedLayout.hpp"
#include "randomLayout.hpp"
#include "levelLayout.hpp"
#include "vanEmdeBoasLayout.hpp"

/* Example perfectly balanced binary search tree
               4
            /    \
           2      6
         /  \    /  \
        1    3  5    7
 */
int main()
{
    int n = 4;

    //sortedLayout layout(n);
    //randomLayout layout(n);
    //levelLayout layout(n);
    vanEmdeBoasLayout layout(8);

    layout.find(9);
}



