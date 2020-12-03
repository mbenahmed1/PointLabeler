#ifndef POINTLABELER_SIMULATEDANNEALING_HPP
#define POINTLABELER_SIMULATEDANNEALING_HPP

#include <vector>
#include <iostream>
#include "Point.hpp"
#include "GreedyAlgorithm.hpp"
#include <cmath>
#include <random>

namespace PointLabeler
{

class SimulatedAnnealing
{

public:
    explicit SimulatedAnnealing(int steps, float alpha);

    int solve(std::vector<PointLabeler::Point> &points);

    float get_alpha();

private:

    int set_labels(std::vector<Point> &points, Point &point, Point::Position pos);
    float euler(int c_temp, int c_current, int t_i);
    std::vector<PointLabeler::Point> copy(std::vector<PointLabeler::Point> vector);
    int steps;
    float alpha;
};
}
#endif //POINTLABELER_SIMULATEDANNEALING_HPP