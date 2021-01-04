//
// Created by tim on 03.01.21.
//

#include "Util.hpp"

Util::Util(std::vector<Point> &points) : m_points(points), m_map()
{
    for (int i = 0; i < m_points.size(); i++)
    {
        m_map.insert({1, m_points}); // TODO fill correctly
    }
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
