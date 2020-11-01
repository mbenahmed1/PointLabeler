#include "Point.hpp"

namespace PointLabeler
{
    Point::Point(int x, int y, int label_length, int label_height, std::string label_text)
    {
        Point::x = x;
        Point::y = y;
        Point::label_height = label_height;
        Point::label_length = label_length;
        Point::label_text = label_text;

    }
}