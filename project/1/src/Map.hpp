#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "Point.hpp"



namespace PointLabeler{

class Map
{
public:

    Map(std::string filename);

    std::string get_filename();
    
    int get_x_size();
    
    int get_y_size();

    int load_from_file(std::string filename);

    int write_to_file(std::vector<Point> *points, std::string filename);

    std::vector<Point>* random_generate_points(int max_x_pos, int min_x_pos, int max_y_pos, int min_y_pos, int max_label_length, int max_label_height, int number_of_points);

private:
    std::vector<Point*> points;
    std::string filename;
    int number_of_points;
    int x_size;
    int y_size;

};
}