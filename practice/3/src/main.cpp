#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
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
int main(int argc, char **argv)
{
    int n = std::stoi(argv[1]);

    int size = std::pow(2, n) - 1;
    int random_samples = 10;
    int* random_keys = new int[random_samples];

    std::mt19937 gen(31); // seed the generator
    std::uniform_int_distribution<> distr(1, size); // define the range

    for (int i = 0; i < random_samples; i++) {
        random_keys[i] = distr(gen);
    }

    char l = argv[2][0];

    if (l == 's')
    {
        std::vector<int> res(size);
        sortedLayout layout(n);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < random_samples; i++)
        {
            res[i] = layout.find(random_keys[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << n << ", " << ((long double) duration)/1000000 << std::endl;
    }
    if (l == 'r')
    {
        std::vector<int> res(size);
        randomLayout layout(n);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < random_samples; i++)
        {
            res[i] = layout.find(random_keys[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << n << ", " << ((long double) duration)/1000000 << std::endl;
    }
    if (l == 'l')
    {
        std::vector<int> res(size);
        levelLayout layout(n);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < random_samples; i++)
        {
            res[i] = layout.find(random_keys[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << n << ", " << ((long double) duration)/1000000 << std::endl;
    }
    if (l == 'v')
    {
        std::vector<int> res(size);
        vanEmdeBoasLayout layout(n);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < random_samples; i++)
        {
            std::cout << random_keys[i] << std::endl;
            res[i] = layout.find(random_keys[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << n << ", " << ((long double) duration)/1000000 << std::endl;
    }

}





