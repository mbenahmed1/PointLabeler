#ifndef POINTLABELER_SIMULATEDANNEALING_HPP
#define POINTLABELER_SIMULATEDANNEALING_HPP

#include <vector>
#include <iostream>
#include "Point.hpp"
#include <cmath>

namespace PointLabeler
{

class SimulatedAnnealing
{

public:
    explicit SimulatedAnnealing(int steps);

    void solve(std::vector<PointLabeler::Point> &points);

private:
    int steps;
};
}
#endif //POINTLABELER_SIMULATEDANNEALING_HPP