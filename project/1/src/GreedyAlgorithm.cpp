//
// Created by tim on 02.11.20.
//

#include "GreedyAlgorithm.hpp"

namespace PointLabeler
{

GreedyAlgorithm::GreedyAlgorithm(std::vector<PointLabeler::Point> &points) : points(points)
{}

void GreedyAlgorithm::solve()
{
    std::vector<PointLabeler::Point> labeled_points = std::vector<PointLabeler::Point>();
    for (auto &point : points)
    {
        point.set_label_pos(Point::top_left);
        if (!check_overlap(labeled_points, point))
        {
            labeled_points.push_back(point);
        }
        point.set_label_pos(Point::top_right);
        if (!check_overlap(labeled_points, point))
        {
            labeled_points.push_back(point);
        }
        point.set_label_pos(Point::bottom_left);
        if (!check_overlap(labeled_points, point))
        {
            labeled_points.push_back(point);
        }
        point.set_label_pos(Point::bottom_right);
        if (!check_overlap(labeled_points, point))
        {
            labeled_points.push_back(point);
        }
    }


}

bool GreedyAlgorithm::check_overlap(std::vector<PointLabeler::Point> &labeled, PointLabeler::Point &point)
{
    for (auto &label : labeled)
    {
        if (label.is_overlapping(point))
        {
            return true;
        }
    }
    return false;
}

}
