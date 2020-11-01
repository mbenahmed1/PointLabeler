#include <stdio.h>
#include <string>
namespace PointLabeler{


class Point{

public:

    Point(int x, int y, int label_length, int label_height, std::string label_text);

    int get_x();

    int get_y();

    int get_label_length();

    int get_label_height();

    std::string get_label_text();

private:
    int x;
    int y;
    int label_length;
    int label_height;
    std::string label_text;
};

}