/**
 * GreedyAlgorithm.cpp
 *
 *  @date 31.10.2020
 *  @author Tim Adam (tadam@uos)
 *  @author Martin ben Ahmed (mbenahmed@uos)
 */
#include "GreedyAlgorithm.hpp"
#include "Util.hpp"

namespace PointLabeler
{

    GreedyAlgorithm::GreedyAlgorithm(std::vector<PointLabeler::Point> &points) : points(points)
    {
    }

    int GreedyAlgorithm::solve()
    {
        m_conflicts = Util::createDataStructure2(points);

        int labeled_count = points.size();

        int pointIndex = 0;
        for (int i = 0; i < points.size(); i++)
        {
            points[i].set_label_pos(Point::top_left);
            if (!check_overlap(points, points[i], m_conflicts, i, points))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_right);
            if (!check_overlap(points, points[i], m_conflicts, i, points))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_left);
            if (!check_overlap(points, points[i], m_conflicts, i, points))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_right);
            if (!check_overlap(points, points[i], m_conflicts, i, points))
            {
                continue;
            }
            labeled_count--;
            points[i].clear();
        }
        return labeled_count;
    }

    bool GreedyAlgorithm::check_overlap(std::vector<PointLabeler::Point> &labeled, PointLabeler::Point &point, std::vector<std::vector<int>> &map, int pointIndex, std::vector<Point> &points)
    {
        for (auto &label : labeled)
        {
            if (label.get_x() == point.get_x() && label.get_y() == point.get_y())
            {
                continue;
            }
            if (label.is_overlapping(point))
            {
                return true;
            }
        }
        return false;
    }

} // namespace PointLabeler
