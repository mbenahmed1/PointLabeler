//
// Created by tim on 03.01.21.
//

#ifndef POINTLABELER_UTIL_HPP
#define POINTLABELER_UTIL_HPP

#include "Point.hpp"
#include <vector>
#include <iostream>

using namespace PointLabeler;

class Util
{
private:

    std::vector<Point> &m_points;

public:

    explicit Util(std::vector<Point> &points);

    static bool rectangle_overlapping(int a1_x, int a1_y, int a2_x, int a2_y, int b1_x, int b1_y, int b2_x, int b2_y);

    static std::vector<std::vector<Point>> createDataStructure(std::vector<Point> &points);

    static std::vector<std::vector<int>> createDataStructure2(std::vector<Point> &points);

    static void evaluateDataStructure(const std::vector<std::vector<Point>>& map);

    static void evaluateDataStructure(const std::vector<std::vector<int>>& map);

    static void printDataStructure(const std::vector<std::vector<Point>>& vec, std::vector<Point>& points);

    static void printDataStructure(const std::vector<std::vector<int>>& vec, std::vector<Point>& points);

    static bool hasConflict(std::vector<std::vector<int>>& map, std::vector<Point> &points, int index);

    int o(int i, int a, int j, int b);

};

#endif //POINTLABELER_UTIL_HPP
