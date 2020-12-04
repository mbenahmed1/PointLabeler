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
    explicit SimulatedAnnealing(int steps, double alpha, double t_i);

    int solve(std::vector<PointLabeler::Point> &points);

    float get_alpha();

    double get_t_i();

    double t(int i);

private:

    int set_labels(std::vector<Point> &points, Point &point, Point::Position pos);
    float euler(int c_temp, int c_current, int t_i);
    std::vector<PointLabeler::Point> copy(std::vector<PointLabeler::Point> vector);
    int c(std::vector<PointLabeler::Point> &points);
    int steps;
    float alpha;
    double t_i;
};
}
#endif //POINTLABELER_SIMULATEDANNEALING_HPP