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

        double get_alpha() const;

        double get_t_i() const;

    private:
        int set_labels(std::vector<Point> &points, Point::Position pos, int pointIndex, std::vector<std::vector<int>> &map);

        int set_labels2(std::vector<Point> &points, int pointIndex, std::vector<std::vector<int>> &map);

        int set_labels3(std::vector<Point> &points, int pointIndex, std::vector<std::vector<int>> &map);

        int set_labels4(std::vector<Point> &points, std::vector<std::vector<int>> &map);

        int random_set_labels(std::vector<Point> &points, int pointIndex, std::vector<std::vector<int>> &map);

        double next_temp(int iteration);

        static double euler(int c_temp, int c_current, double t_i);

        void print_progress(int, int, int, double) const;

        int steps;
        double alpha;
        double t_i;

        std::mt19937 gen;
        // random distribution for point which will be randomly altered
        std::uniform_int_distribution<> index_distr;
        // random distribution for switching label positions
        std::uniform_int_distribution<> pos_distr;
    };
} // namespace PointLabeler
#endif //POINTLABELER_SIMULATEDANNEALING_HPP