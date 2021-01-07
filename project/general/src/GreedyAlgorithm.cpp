//
// Created by tim on 02.11.20.
//

#include "GreedyAlgorithm.hpp"
#include "Util.hpp"

namespace PointLabeler
{

GreedyAlgorithm::GreedyAlgorithm(std::vector<PointLabeler::Point> &points) : points(points)
{
    //auto vec = Util::createDataStructure(points);

    //Util::printDataStructure(vec, points);

    //Util::evaluateDataStructure(vec);
}

int GreedyAlgorithm::solve()
{

    int labeled_count = points.size();
    //std::vector<PointLabeler::Point> labeled_points = std::vector<PointLabeler::Point>();
    for (auto &point : points)
    {
        point.set_label_pos(Point::top_left);
        if (!check_overlap(points, point))
        {
            continue;
        }
        point.set_label_pos(Point::top_right);
        if (!check_overlap(points, point))
        {
            continue;
        }
        point.set_label_pos(Point::bottom_left);
        if (!check_overlap(points, point))
        {
            continue;
        }
        point.set_label_pos(Point::bottom_right);
        if (!check_overlap(points, point))
        {
            continue;
        }
        labeled_count--;
        point.clear();
    }
    return labeled_count;
}

bool GreedyAlgorithm::check_overlap(std::vector<PointLabeler::Point> &labeled, PointLabeler::Point &point)
{
    for (auto &label : labeled)
    {
        if (label.get_x() == point.get_x() && label.get_y() == point.get_y()) {
            continue;
        }
        if (label.is_overlapping(point))
        {
            return true;
        }
    }
    return false;
}

}
