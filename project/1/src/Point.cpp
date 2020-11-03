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

int Point::get_x() const
{
    return Point::x;
}


int Point::get_y() const
{
    return Point::y;
}


int Point::get_label_height() const
{
    return Point::label_height;
}


int Point::get_label_length() const
{
    return Point::label_length;
}


std::string Point::get_label_text() const
{
    return Point::label_text;
}

void Point::set_label_x(int x)
{
    Point::label_x = x;
}

int Point::get_label_x() const
{
    return Point::label_x;
}

void Point::set_label_y(int y)
{
    Point::label_y = y;
}


int Point::get_label_y() const
{
    return Point::label_y;
}


void Point::set_is_labeled(int is_labeled)
{
    Point::is_labeled = is_labeled;
}

int Point::get_is_labeled() const
{
    return Point::is_labeled;
}

void Point::set_label_pos(Point::Position pos)
{
    int w = get_label_length();
    int h = get_label_height();
    switch (pos)
    {
        case top_left:
            set_label_x(x - w);
            set_label_y(y + h);
            break;
        case top_right:
            set_label_x(x);
            set_label_y(y + h);
            break;
        case bottom_left:
            set_label_x(x - w);
            set_label_y(y);
            break;
        case bottom_right:
            set_label_x(x);
            set_label_y(y);
            break;
    }
    set_is_labeled(1);
}

bool Point::is_overlapping(Point &point) const
{
    int xPosA = get_x();
    int yPosA = get_y();
    int wA = get_label_length();
    int hA = get_label_height();
    int xPosB = point.get_x();
    int yPosB = point.get_y();
    int wB = point.get_label_length();
    int hB = point.get_label_height();

    if (get_is_labeled() == 0 && point.get_is_labeled() == 0) {
        return false;
    }
    if (get_is_labeled() == 0 && point.get_is_labeled() == 1) {
        return xPosA >= xPosB && xPosA <= xPosB + wB && yPosA <= yPosB && yPosA >= yPosB - hB;
    }
    if (get_is_labeled() == 1 && point.get_is_labeled() == 0) {
        return xPosB >= xPosA && xPosB <= xPosA + wA && yPosB <= yPosA && yPosB >= yPosA - hA;
    }
    if (get_is_labeled() == 1 && point.get_is_labeled() == 1) {
        if (xPosA > xPosB + wB || xPosB > xPosA + wA) {
            return false;
        }
        if (yPosA > yPosB + hB || yPosB > yPosA + hA) {
            return false;
        }
        return true;
    }
    return true;
}

}