/**
 * Point.hpp
 *
 *  @date 31.10.2020
 *  @author Tim Adam (tadam@uos)
 *  @author Martin ben Ahmed (mbenahmed@uos)
 */
#ifndef POINT_HPP
#define POINT_HPP

#include <stdio.h>
#include <string>

namespace PointLabeler
{

    class Point
    {

    public:
        enum Position
        {
            top_left = 1,
            top_right = 2,
            bottom_left = 3,
            bottom_right = 4
        };

        void set_label_pos(Position pos);

        void set_label_pos(int pos);

        bool is_overlapping(Point &point) const;

        void clear();

        Point(int x, int y, int label_length, int label_height, std::string label_text);

        Point(int x, int y, int label_length, int label_height, std::string label_text, int is_labeled, int label_x, int label_y, int neighborhood_count, Position label_enum);

        ~Point();

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

        int get_neighborhood_count() const;

        void set_neighborhood_count(int number_of_neighbors);

        static bool compare(const PointLabeler::Point &first, const PointLabeler::Point &second);

        void set_label_enum(Position label_enum);

        Position get_label_enum();

        bool is_bounding_box_overlapping(Point &p) const;

    private:
        int x;
        int y;
        int label_length;
        int label_height;
        std::string label_text;
        int is_labeled;
        int label_x;
        int label_y;
        int neighborhood_count;
        Position label_enum;
    };

} // namespace PointLabeler

#endif