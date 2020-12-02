#include "SimulatedAnnealing.hpp"

namespace PointLabeler
{

SimulatedAnnealing::SimulatedAnnealing(int steps, float alpha) : steps(steps), alpha(alpha)
{}

int SimulatedAnnealing::solve(std::vector<PointLabeler::Point> &points)
{
    
     // checking inputs
    if(SimulatedAnnealing::steps <= 0)
    {
        std::cerr << "Error: Steps can not be <= 0." << std::endl;
        return -1;
    }

    if(SimulatedAnnealing::alpha > 1 || SimulatedAnnealing::alpha < 0)
    {
        std::cerr << "Error: Alpha has to be in the interval [0, 1]." << std::endl;
        return -1;
    }

    // copying original vector
    std::vector<PointLabeler::Point> s_opt;
    std::vector<PointLabeler::Point> s;

    for(int i = 0; i < points.size(); i++)
    {
        s_opt.push_back(Point(points[i].get_x(), points[i].get_y(), points[i].get_label_length(), points[i].get_label_height(), points[i].get_label_text()));
    }


    // init random devices
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    // random distribution for point which will be randomly altered
    std::uniform_int_distribution<> index_distr(0, points.size());
    // random distribution for switching label positions
    std::uniform_int_distribution<> pos_distr(Point::Position::top_left, Point::Position::bottom_right);
    // random distribution for annealing descision
    std::uniform_real_distribution<> annealing_distr(0, 1);
    
    // initializing greedy solver
    PointLabeler::GreedyAlgorithm greedyAlgorithm = PointLabeler::GreedyAlgorithm(points);

    


    // start SA

    // step counter
    int i = 0;

    // generating initial solution 
    int c_opt = greedyAlgorithm.solve();
    
    // c(s')
    int c_temp = c_opt;
    // c(s)
    int c_current;

    int temp = c_opt;

    // t_i
    float t_i = 100.0;

    

    // varibales for loop
    // declare outside for better performance
    int index;
    Point::Position current_label_pos;
    int pos;
    
    


    while(i < SimulatedAnnealing::steps)
    {   
        // generate random index to be changed
        index = index_distr(gen);
        // get label pos of index to be changed
        Point::Position current_label_pos = points[index].get_label_enum();
        
        // generate new position different from original position
        pos = pos_distr(gen);
        while(pos == current_label_pos)
        {
            pos = pos_distr(gen);
        }
        
        // Generate random solution (c(s'))
        temp = SimulatedAnnealing::set_labels(points, points[index], static_cast<Point::Position>(pos_distr(gen)));
        
        //std::cout << std::to_string(temp) << std::endl;
        
        c_current += temp;

        //std::cout << std::to_string(c_current) << std::endl;

        std::cout << std::to_string(euler(c_temp, c_current, t_i)) << std::endl;
        
        //std::cout << std::to_string(annealing_distr(gen)) << std::endl;
        
        //std::cout << std::to_string(c_current <= c_temp) << std::endl;

        std::cout << std::to_string(annealing_distr(gen) < euler(c_temp, c_current, t_i)) << std::endl;

        // if c(s') <= c(s) or Rand(0,1) < e⁻⁽⁾ then
        if(c_current >= c_temp || annealing_distr(gen) < euler(c_temp, c_current, t_i))
        {

            // s:=s'
            for(int i = 0; i < points.size(); i++)
            {
                //s[i] = points[i];
            }
            
            // if c(s') < c* then
            if(c_current > c_opt)
            {
                s_opt = s;
                c_opt = c_current;
                c_temp = c_current;
            }
        }
        //std::cout << std::to_string(c_current / (float)points.size()) << std::endl;
        i++;
        t_i = get_alpha()*t_i;
        //std::cout << std::to_string(t_i) << std::endl;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                   
    


}

float SimulatedAnnealing::euler(int c_temp, int c_current, int t_i)
{
    return std::exp(-( (c_temp - c_current) / (float)(t_i) ) );
}

float SimulatedAnnealing::get_alpha()
{
    return SimulatedAnnealing::alpha;
}

int SimulatedAnnealing::set_labels(std::vector<Point> &points, Point &point, Point::Position pos)
{

    int labeled = point.get_is_labeled(); 

    point.set_label_pos(pos);

    if(GreedyAlgorithm::check_overlap(points, point))
    {
        point.clear();
        return 0 - labeled;
    }
    else
    {
        return 1 - labeled;
    }
}

}