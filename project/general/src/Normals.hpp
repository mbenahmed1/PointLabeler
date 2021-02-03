/**
 * Normals.hpp
 *
 *  @date 31.10.2020
 *  @author Tim Adam (tadam@uos)
 *  @author Martin ben Ahmed (mbenahmed@uos)
 */
#ifndef POINTLABELER_NORMALS_HPP
#define POINTLABELER_NORMALS_HPP

#include <vector>
#include <iostream>
#include "Point.hpp"
#include "GreedyAlgorithm.hpp"
#include <cmath>
#include <algorithm>
#include "Util.hpp"

namespace PointLabeler
{

    class Normals
    {

    public:
        explicit Normals(int radius);

        int solve(std::vector<PointLabeler::Point> &points);

    private:
        int radius;

        static float euclidean_distance(PointLabeler::Point point_a, PointLabeler::Point point_b);
    };
} // namespace PointLabeler
#endif //POINTLABELER_NORMALS_HPP