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
    for (auto &point : points)
    {
        std::cout << point.get_label_text() << std::endl;
    }
}

}
