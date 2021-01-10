//
// Created by tim on 03.01.21.
//

#include "Util.hpp"

Util::Util(std::vector<Point> &points) : m_points(points)
{
}

std::vector<Point> Util::getNeighbours(Point &p)
{
    std::vector<Point> v;
    return v;
}

int Util::o(int i, int a, int j, int b)
{
    m_points[i].set_label_pos(a + 1);
    m_points[j].set_label_pos(b + 1);

    if (m_points[i].is_overlapping(m_points[j]))
    {
        m_points[i].clear();
        m_points[j].clear();
        return 1;
    }
    m_points[i].clear();
    m_points[j].clear();
    return 0;
}

bool Util::rectangle_overlapping(int a1_x, int a1_y, int a2_x, int a2_y, int b1_x, int b1_y, int b2_x, int b2_y)
{

    // If one rectangle is on left side of other
    if (a2_x <= b1_x || b2_x <= a1_x)
    {
        return false;
    }

    // If one rectangle is above other
    if (a2_y >= b1_y || b2_y >= a1_y)
    {
        return false;
    }
    return true;
}

std::vector<std::vector<Point>> Util::createDataStructure(std::vector<Point> &points)
{
    std::vector<std::vector<Point>> map(points.size());

    for (int i = 0; i < points.size() - 1; i++)
    {
        Point &a = points[i];

        for (int j = i + 1; j < points.size(); j++)
        {
            Point &b = points[j];
            if (a.is_bounding_box_overlapping(b))
            {
                map[i].push_back(b);
                map[j].push_back(a);
            }
        }
    }
    return map;
}

void Util::evaluateDataStructure(const std::vector<std::vector<Point>>& map)
{
    int avg = 0;
    int min = map.size();
    int max = 0;

    for (auto & i : map)
    {
        int size = i.size();
        avg += size;
        if (size < min)
        {
            min = size;
        }
        if (size > max)
        {
            max = size;
        }
    }

    avg /= map.size();

    std::cout << "AVG: " << avg << " MAX: " << max << " MIN: " << min << std::endl;
}

void Util::printDataStructure(const std::vector<std::vector<Point>> &vec, std::vector<Point> &points)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << "(" << points[i].get_x() << ", " << points[i].get_y() <<"): ";
        for (int j = 0; j < vec[i].size(); j++)
        {
            std::cout << "(" << vec[i][j].get_x() << ", " << vec[i][j].get_y() << "), ";
        }
        std::cout << std::endl;
    }
}
