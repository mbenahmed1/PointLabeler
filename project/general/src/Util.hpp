//
// Created by tim on 03.01.21.
//

#ifndef POINTLABELER_UTIL_HPP
#define POINTLABELER_UTIL_HPP

#include "Point.hpp"
#include <vector>
#include <unordered_map>

using namespace PointLabeler;

class Util
{
private:

    std::vector<Point> &m_points;
    std::unordered_map<int, std::vector<Point>> m_map;

public:

    Util(std::vector<Point> &points);

    int o(int i, int a, int j, int b);

    std::vector<Point> getNeighbours(Point &p);

};

#endif //POINTLABELER_UTIL_HPP
