#include "Normals.hpp"

namespace PointLabeler
{

Normals::Normals(int radius) : radius(radius)
{}

std::vector<PointLabeler::Point> Normals::solve(std::vector<PointLabeler::Point> &points)
{
    

    // declaring 2d vector
    std::vector<std::vector<float>> distances(points.size(), std::vector<float>(points.size()));

    // calculating distances vector
    // interating over NxN vector
    for(int i = 0; i < points.size(); i++)
    {
        for(int j = 0; j < points.size(); j++)
        {
            // if indices are the same distance is zero
            if(i == j)
            {
                distances[i][j] = 0.0;
                continue;
            }
            distances[i][j] = Normals::euclidean_distance(points[i], points[j]);
        }
    }

    // vector saving prefered label position for each point
    std::vector<Point::Position> prefered_label_pos(points.size());

    
    // compute centroids of epsilon neighborhood of each point
    // and determine which label position will probably interfer with least other points
    int neighbor_count = 0;
    
    int x_sum = 0;
    int y_sum = 0;

    float x_mean = 0.0;
    float y_mean = 0.0;
    
    for(int i = 0; i < points.size(); i++)
    {
        for(int j = 0; j < points.size(); j++)
        {
            // do nothing if indices are the same
            if(i == j)
            {
                continue;
            }
                        
            // if point lays within distance, sum up x and y coordinates
            // and compute centroid of those point
            
            //std::cout << i << " " << j << ": " << distances[i][j] << std::endl;
            if(distances[i][j] <= Normals::radius)
            {
                
                x_sum += points[j].get_x();
                y_sum += points[j].get_y();

                neighbor_count++;

               
            }
        }

        // no neightbors within reach
        if(neighbor_count == 0)
        {
            // set default pos
            // maybe figure out someting smarter later
            prefered_label_pos[i] = Point::bottom_left;
        }
        else
        {
            x_mean = x_sum / neighbor_count;
            y_mean = y_sum / neighbor_count;
        }
        
        
        /*        
        // this should never be the case other than symmetrical constructed instances
        if(points[i].get_x() == x_mean or points[i].get_y() == y_mean)
        {
            std::cout << "Error: Centroid same as point itself. Something went terribly wrong" << std::endl;
            break;
        }
        */



        // centroid lies right of point i
        if(points[i].get_x() - x_mean < 0)
        {
            // centroid lies upper right of point i
            if(points[i].get_y() - y_mean < 0)
            {
                // setting opposite direction as prefered
                prefered_label_pos[i] = Point::bottom_left;
            }
            // centroid lower right of point i
            else
            {
                prefered_label_pos[i] = Point::top_left;
            }           
        } 
        // centroid lies left of point i
        else
        {
            // centroid lies upper left of point i
            if(points[i].get_y() - y_mean < 0)
            {
                // setting opposite direction as prefered
                prefered_label_pos[i] = Point::bottom_right;
            }
            // centroid lies lower left of point i
            else
            {
                prefered_label_pos[i] = Point::top_right;
            }
        }

        x_mean = 0;
        y_mean = 0;
        neighbor_count = 0;
    }

    // setting labels according to prefered direction    
    for(int i = 0; i < points.size(); i++)
    {
        // case top left is prefered
        if(prefered_label_pos[i] == Point::top_left)
        {
            points[i].set_label_pos(Point::top_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
        }

        // case top right is prefered
        if(prefered_label_pos[i] == Point::top_right)
        {
            points[i].set_label_pos(Point::top_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
        }
        
        // case bottom left is prefered
        if(prefered_label_pos[i] == Point::bottom_left)
        {
            points[i].set_label_pos(Point::bottom_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
        }

        // case bottom right is prefered
        if(prefered_label_pos[i] == Point::bottom_right)
        {
            points[i].set_label_pos(Point::bottom_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::bottom_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_right);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
            points[i].set_label_pos(Point::top_left);    
            if(!GreedyAlgorithm::check_overlap(points, points[i]))
            {
                continue;
            }
        }
        // resetting label information if label was overlapping
        points[i].clear();
    }
    

    return points;
}

float Normals::euclidean_distance(PointLabeler::Point point_a, PointLabeler::Point point_b)
{
    return std::sqrt((point_a.get_x() - point_b.get_x()) * (point_a.get_x() - point_b.get_x())
         + (point_a.get_y() - point_b.get_y()) * (point_a.get_y() - point_b.get_y()));
}


}