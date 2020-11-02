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
    Point::is_labeled = 0;
    Point::label_x = 0;
    Point::label_y = 0;

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

void Point::set_label_x(int x)
{
    Point::label_x = x;
}

int Point::get_label_x()
{
    return Point::label_x;
}

void Point::set_label_y(int y)
{
    Point::label_y = y;
}


int Point::get_label_y()
{
    return Point::label_y;
}


void Point::set_is_labeled(int is_labeled)
{
    Point::is_labeled = is_labeled;
}

int Point::get_is_labeled()
{
    return Point::is_labeled;
}

}