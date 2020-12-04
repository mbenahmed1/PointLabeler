#include "SimulatedAnnealing.hpp"

namespace PointLabeler
{

SimulatedAnnealing::SimulatedAnnealing(int steps, double alpha, double t_i) : steps(steps), alpha(alpha), t_i(t_i)
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


    // init random devices
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    // random distribution for point which will be randomly altered
    std::uniform_int_distribution<> index_distr(0, points.size());
    // random distribution for switching label positions
    std::uniform_int_distribution<> pos_distr(Point::Position::top_left, Point::Position::bottom_right);
    // random distribution for annealing descision
    std::uniform_real_distribution<> annealing_distr(0, 1);


    std::vector<Point> s;
    std::vector<Point> s_dash;
    s = copy(points);
    int c_s_dash;
    

    //******** i = 0;
    
    int step_count = 1;
    int i = 1;

    //******** Generiere eine initiale Lösung s E S;

    GreedyAlgorithm greedy = GreedyAlgorithm(s);

    //******* c* = c(s);
    int c_s = greedy.solve();

    //****** s_opt = s;
    std::vector<Point> s_opt = copy(s);

    //******** c* = c(s)
    int c_opt = c_s;


    int index;
    int pos;
    Point::Position label;
    float progress = 0.0;
    int solution_size = s.size();

    while(step_count <= steps)
    {
        
        
        // copying old solution to s_dash
        s_dash = copy(s);
        // copying old c value to c_s_dash
        c_s_dash = c_s;

        // generate random index to be changed
        index = index_distr(gen);

        // generate random label pos
        pos = pos_distr(gen);

        // while it is the same as before generate new one
        while(pos == s_dash[index].get_label_enum())
        {
            pos = pos_distr(gen);
        }

        // setting changed label and returning c delta
        // counting of labeled points does not seem to work properly
        // though results don't take negative effect

        c_s_dash += set_labels(s_dash, s_dash[index], static_cast<Point::Position>(pos));
       
        c_s_dash = c(s_dash);

        //std::cout << c_s_dash << std::endl;
        //std::cout << euler(c_s_dash, c_s, t(i)) << std::endl;
        //std::cout << t(i) << std::endl;
        //std::cout << c_s_dash << ">=" << c_s << std::endl;
        //std::cout << annealing_distr(gen) << "<" << euler(c_s_dash, c_s, t(i)) << std::endl;
        //std::cout << annealing_distr(gen) << std::endl;
        //std::cout << c_s_dash - c_s << std::endl;

        //if(c_s_dash >= c_s || annealing_distr(gen) < euler(c_s_dash, c_s, t(i)))
        
        if(c_s_dash >= c_s || annealing_distr(gen) < t(i))
        {
            s = SimulatedAnnealing::copy(s_dash);
            c_s = c_s_dash;

            if(c_s_dash > c_opt)
            {
                s_opt = SimulatedAnnealing::copy(s_dash);
                c_opt = c_s_dash;
            }
        }
        step_count++;
       
       
        // reheating after some time
        if(t(i) < 0.0001)
        {
            i = 1;
        }
        


        i++;
        
        
        progress = c_opt / (float)solution_size;
        int barWidth = 50;

        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) 
            {
            if (i < pos)
            {
                std::cout << "=";
            }
            else if (i == pos)
            {
                std::cout << ">";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "] " << float(progress * 100.0) << " %\r";
        std::cout << "Step " << step_count << " of " << steps << " t_i: " << t(i) << "  c_opt: ";
        std::cout.flush();

    }

    points = copy(s_opt);

}

float SimulatedAnnealing::euler(int c_s_dash, int c_s, int t_i)
{
    //std::cout << (double)(c_s_dash - c_s) << std::endl;
    //std::cout << (double)(c_s_dash - c_s) / (double)(t_i) << std::endl;
    if(t_i < 1)
    {
        return 0.0;
    }
    return std::exp(-( (double)(c_s_dash - c_s) / (double)(t_i) ) );
}

double SimulatedAnnealing::t(int i)
{
    return SimulatedAnnealing::get_t_i() * std::pow(SimulatedAnnealing::get_alpha(), i);
}

std::vector<PointLabeler::Point> SimulatedAnnealing::copy(std::vector<PointLabeler::Point> vector)
{
    std::vector<PointLabeler::Point> vector_copy;

    for(int i = 0; i < vector.size(); i++)
    {
        vector_copy.push_back(Point(vector[i].get_x(), vector[i].get_y(), 
                                    vector[i].get_label_length(), 
                                    vector[i].get_label_height(), 
                                    vector[i].get_label_text(),
                                    vector[i].get_is_labeled(),
                                    vector[i].get_label_x(),
                                    vector[i].get_label_y(),
                                    vector[i].get_neighborhood_count(),
                                    vector[i].get_label_enum()));
    }

    return vector_copy;
}

float SimulatedAnnealing::get_alpha()
{
    return SimulatedAnnealing::alpha;
}


double SimulatedAnnealing::get_t_i()
{
    return SimulatedAnnealing::t_i;
}
int SimulatedAnnealing::c(std::vector<PointLabeler::Point> &points)
{
    
    int c = 0;
    for(int i = 0; i < points.size(); i++)
    {
        //std::cout << points[i].get_is_labeled() << std::endl;
        if(points[i].get_is_labeled() == 1)
        {
            c++;
        }
    }
    return c;
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