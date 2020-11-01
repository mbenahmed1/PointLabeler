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

int Point::get_x()
{
    return Point::x;
}


int Point::get_y()
{
    return Point::y;
}


int Point::get_label_height()
{
    return Point::label_height;
}


int Point::get_label_length()
{
    return Point::label_length;
}


std::string Point::get_label_text()
{
    return Point::label_text;
}

}