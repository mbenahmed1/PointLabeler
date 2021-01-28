//
// Created by tim on 02.11.20.
//

#ifndef POINTLABELER_GREEDYALGORITHM_HPP
#define POINTLABELER_GREEDYALGORITHM_HPP

#include <vector>
#include <iostream>
#include "Point.hpp"
#include "Util.hpp"

namespace PointLabeler
{

    class GreedyAlgorithm
    {

    public:
        explicit GreedyAlgorithm(std::vector<PointLabeler::Point> &points);

        int solve();

        static bool check_overlap(std::vector<PointLabeler::Point> &labeled, PointLabeler::Point &point, std::vector<std::vector<int>> &map, int pointIndex, std::vector<Point> &points);

        std::vector<std::vector<int>> m_conflicts;

    private:
        std::vector<PointLabeler::Point> &points;
    };

} // namespace PointLabeler

#endif //POINTLABELER_GREEDYALGORITHM_HPP
