#ifndef POINT_HPP
#define POINT_HPP

#include <stdio.h>
#include <string>

namespace PointLabeler
{

class Point
{

public:

    Point(int x, int y, int label_length, int label_height, std::string label_text);

    int get_x();

    int get_y();

    int get_label_length();

    int get_label_height();

    int get_is_labeled();

    void set_is_labeled(int is_labeled);

    int get_label_x();

    void set_label_x(int x);

    int get_label_y();

    void set_label_y(int y);

    std::string get_label_text();

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