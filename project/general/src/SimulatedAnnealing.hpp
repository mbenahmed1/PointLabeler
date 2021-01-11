#ifndef POINTLABELER_SIMULATEDANNEALING_HPP
#define POINTLABELER_SIMULATEDANNEALING_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include "Point.hpp"
#include "GreedyAlgorithm.hpp"
#include "Util.hpp"

namespace PointLabeler
{

class SimulatedAnnealing
{

public:
    explicit SimulatedAnnealing(int steps, double alpha, double t_i);

    int solve(std::vector<PointLabeler::Point> &points);

    double get_alpha();

    double get_t_i();

    double t(int i);

private:

    int set_labels(std::vector<Point> &points, Point &point, Point::Position pos, int pointIndex, std::vector<std::vector<int>>& map);

    double euler(int c_temp, int c_current, double t_i);

    std::vector<PointLabeler::Point> copy(std::vector<PointLabeler::Point> vector);

    int c(std::vector<PointLabeler::Point> &points);

    int steps;
    double alpha;
    double t_i;
};
}
#endif //POINTLABELER_SIMULATEDANNEALING_HPP