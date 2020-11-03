#ifndef POINT_HPP
#define POINT_HPP

#include <stdio.h>
#include <string>

namespace PointLabeler
{

class Point
{

public:

    enum Position {top_left, top_right, bottom_left, bottom_right};

    void set_label_pos(Position pos);

    bool is_overlapping(Point &point) const;

    Point(int x, int y, int label_length, int label_height, std::string label_text);

    int get_x() const;

    int get_y() const;

    int get_label_length() const;

    int get_label_height() const;

    int get_is_labeled() const;

    void set_is_labeled(int is_labeled);

    int get_label_x() const;

    void set_label_x(int x);

    int get_label_y() const;

    void set_label_y(int y);

    std::string get_label_text() const;

private:
    int x;
    int y;
    int label_length;
    int label_height;
    std::string label_text;
    int is_labeled;
    int label_x;
    int label_y;


};

}

#endif