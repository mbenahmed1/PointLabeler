#include "Point.hpp"
#include "Util.hpp"
#include "iostream"

namespace PointLabeler
{
    Point::Point(int x, int y, int label_length, int label_height, std::string label_text) : Point(x, y, label_length, label_height,
                                                                                                   label_text, 0, 0, 0, 0, Position::top_left) {}

    Point::Point(int x, int y, int label_length, int label_height, std::string label_text,
                 int is_labeled, int label_x, int label_y, int neighborhood_count,
                 Position label_enum) : x(x), y(y), label_length(label_length),
                                        label_height(label_height), label_text(label_text), is_labeled(is_labeled),
                                        label_x(label_x), label_y(label_y), neighborhood_count(neighborhood_count),
                                        label_enum(label_enum) {}

    Point::~Point()
    {
        // nothing to do here (?)
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
            PointLabeler::Point::set_label_enum(top_left);
            break;
        case top_right:
            set_label_x(x);
            set_label_y(y + h);
            PointLabeler::Point::set_label_enum(top_right);
            break;
        case bottom_left:
            set_label_x(x - w);
            set_label_y(y);
            PointLabeler::Point::set_label_enum(bottom_left);
            break;
        case bottom_right:
            set_label_x(x);
            set_label_y(y);
            PointLabeler::Point::set_label_enum(bottom_right);
            break;
        }
        set_is_labeled(1);
    }

    void Point::set_label_pos(int pos)
    {
        switch (pos)
        {
        case 1:
            set_label_pos(top_left);
            break;
        case 2:
            set_label_pos(top_right);
            break;
        case 3:
            set_label_pos(bottom_left);
            break;
        case 4:
            set_label_pos(bottom_right);
            break;
        default:
            clear();
        }
    }

    bool Point::is_overlapping(Point &point) const
    {
        int xPosA = get_label_x();
        int yPosA = get_label_y();
        int wA = get_label_length();
        int hA = get_label_height();
        int xPosB = point.get_label_x();
        int yPosB = point.get_label_y();
        int wB = point.get_label_length();
        int hB = point.get_label_height();

        if (get_is_labeled() == 0 && point.get_is_labeled() == 0)
        {
            return false;
        }
        if (get_is_labeled() == 0 && point.get_is_labeled() == 1)
        {
            return false;
            // xPosA = get_x();
            // yPosA = get_y();
            // return xPosA >= xPosB && xPosA <= xPosB + wB && yPosA <= yPosB && yPosA >= yPosB - hB;
        }
        if (get_is_labeled() == 1 && point.get_is_labeled() == 0)
        {
            return false;
            // xPosB = point.get_x();
            // yPosB = point.get_y();
            // return xPosB >= xPosA && xPosB <= xPosA + wA && yPosB <= yPosA && yPosB >= yPosA - hA;
        }
        if (get_is_labeled() == 1 && point.get_is_labeled() == 1)
        {
            if (xPosA >= xPosB + wB || xPosB >= xPosA + wA)
            {
                return false;
            }
            if (yPosA <= yPosB - hB || yPosB <= yPosA - hA)
            {
                return false;
            }
            return true;
        }
        return true;
    }

    void Point::clear()
    {
        is_labeled = 0;
        label_x = 0;
        label_y = 0;
    }

    int Point::get_neighborhood_count() const
    {
        return Point::neighborhood_count;
    }

    void Point::set_neighborhood_count(int number_of_neighbors)
    {
        Point::neighborhood_count = number_of_neighbors;
    }

    bool Point::compare(const PointLabeler::Point &first, const PointLabeler::Point &second)
    {
        return first.get_neighborhood_count() > second.get_neighborhood_count();
    }

    void Point::set_label_enum(Position label_enum)
    {
        Point::label_enum = label_enum;
    }

    Point::Position Point::get_label_enum()
    {
        return Point::label_enum;
    }

    bool Point::is_bounding_box_overlapping(Point &p) const
    {
        // top left corner (this)
        int a1_x = x - label_length;
        int a1_y = y + label_height;

        //std::cout << "corners of (" << x << ", " << y << "): (" << a1_x << ", " << a1_y << ") (";

        // bottom right corner (this)
        int a2_x = x + label_length;
        int a2_y = y - label_height;

        //std::cout << a2_x << ", " << a2_y << ") "<< std::endl;

        // top left corner (p)
        int b1_x = p.x - p.label_length;
        int b1_y = p.y + p.label_height;

        //std::cout << "corners of (" << p.x << ", " << p.y << "): (" << b1_x << ", " << b1_y << ") (";

        // bottom right corner (p)
        int b2_x = p.x + p.label_length;
        int b2_y = p.y - p.label_height;

        //std::cout << b2_x << ", " << b2_y << ") "<< std::endl;

        return Util::rectangle_overlapping(a1_x, a1_y, a2_x, a2_y, b1_x, b1_y, b2_x, b2_y);
    }

} // namespace PointLabeler