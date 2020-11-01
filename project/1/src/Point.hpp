#include <stdio.h>
#include <string>
namespace PointLabeler{


class Point{

public:

    Point(int x, int y, int label_length, int label_height, std::string label_text);

private:
    int x;
    int y;
    int label_length;
    int label_height;
    std::string label_text;
};

}