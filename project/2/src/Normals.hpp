#ifndef POINTLABELER_NORMALS_HPP
#define POINTLABELER_NORMALS_HPP

#include <vector>
#include <iostream>
#include "Point.hpp"
#include "GreedyAlgorithm.hpp"
#include <cmath>
#include <algorithm>



namespace PointLabeler
{



class Normals
{

public:
    explicit Normals(int radius);

    void solve(std::vector<PointLabeler::Point> &points);


private:
    int radius;

    static float euclidean_distance(PointLabeler::Point point_a, PointLabeler::Point point_b);
};
}
#endif //POINTLABELER_NORMALS_HPP