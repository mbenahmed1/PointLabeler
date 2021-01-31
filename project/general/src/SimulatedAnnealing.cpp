#include "SimulatedAnnealing.hpp"

namespace PointLabeler
{

    SimulatedAnnealing::SimulatedAnnealing(int steps, double alpha, double t_i) : steps(steps), alpha(alpha), t_i(t_i)
    {
    }

    int SimulatedAnnealing::solve(std::vector<PointLabeler::Point> &points)
    {
        // creating confilct vectors
        static std::vector<std::vector<int>> map = Util::createDataStructure2(points);

        // checking inputs
        if (SimulatedAnnealing::steps <= 0)
        {
            std::cerr << "Error: Steps can not be <= 0." << std::endl;
            return -1;
        }

        if (SimulatedAnnealing::alpha > 1 || SimulatedAnnealing::alpha < 0)
        {
            std::cerr << "Error: Alpha has to be in the interval [0, 1]." << std::endl;
            return -1;
        }

        // init random devices
        std::random_device rd;
        gen = std::mt19937(rd());
        // random distribution for point which will be randomly altered
        index_distr = std::uniform_int_distribution<>(0, points.size() - 1);
        // random distribution for switching label positions
        pos_distr = std::uniform_int_distribution<> (Point::Position::top_left, Point::Position::bottom_right);
        // random distribution for annealing descision
        std::uniform_real_distribution<> annealing_distr(0, 1);

        std::vector<Point> s;
        std::vector<Point> s_dash;
        s = points;
        int c_s_dash;

        //******** i = 0;

        int step_count = 1;
        int i = 1;

        //******** Generiere eine initiale Lösung s E S;

        GreedyAlgorithm greedy = GreedyAlgorithm(s);

        //******* c* = c(s);
        int c_s = greedy.solve();

        //****** s_opt = s;
        std::vector<Point> s_opt = s;

        //******** c* = c(s)
        int c_opt = c_s;

        int index;
        int pos;
        int solution_size = s.size();
        double temperature = t_i;

        while (step_count <= steps)
        {
            // copying old solution to s_dash
            s_dash = s;
            // copying old c value to c_s_dash
            c_s_dash = c_s;

            // generate random index to be changed
            index = index_distr(gen);

            // generate random label pos
            pos = pos_distr(gen);

            // while it is the same as before generate new one
            while (pos == s_dash[index].get_label_enum())
            {
                pos = pos_distr(gen);
            }

            // setting changed label and returning c delta
            //c_s_dash += set_labels(s_dash, static_cast<Point::Position>(pos), index, map);
            c_s_dash += set_labels2(s_dash, index, map);
            //c_s_dash += random_set_labels(s_dash, index, map);
            std::cout << euler(c_s_dash, c_s, temperature) << std::endl;
            // accept worse solutions with a certain probability
            if (c_s_dash >= c_s || annealing_distr(gen) < euler(c_s_dash, c_s, temperature))
            {
                s = s_dash;
                c_s = c_s_dash;

                if (c_s_dash > c_opt)
                {
                    s_opt = s_dash;
                    c_opt = c_s_dash;
                }
            }
            // decrease temperature
            temperature *= alpha;

            step_count++;

            // reheating after some time
            temperature = reanealing_temperature_bound(temperature);
            i++;

            //print_progress(c_opt, solution_size, step_count, temperature);
        }

        points = s_opt;
        return c_opt;
    }

    double SimulatedAnnealing::euler(int c_s_dash, int c_s, double t)
    {
        //std::cout << (double)(c_s_dash - c_s) << std::endl;
        //std::cout << (double)(c_s_dash - c_s) / (double)(t_i) << std::endl;
        return std::exp((c_s_dash - c_s) / t);
    }

    double SimulatedAnnealing::get_alpha() const
    {
        return SimulatedAnnealing::alpha;
    }

    double SimulatedAnnealing::get_t_i() const
    {
        return SimulatedAnnealing::t_i;
    }

    int SimulatedAnnealing::set_labels(std::vector<Point> &points, Point::Position pos, int pointIndex, std::vector<std::vector<int>> &map)
    {
        Point &point = points[pointIndex];

        int labeled = point.get_is_labeled();

        point.set_label_pos(pos);

        if (Util::hasConflict(map, points, pointIndex))
        {
            point.clear();
            return 0 - labeled;
        }
        else
        {
            return 1 - labeled;
        }
    }

    int SimulatedAnnealing::set_labels2(std::vector<Point> &points, int pointIndex, std::vector<std::vector<int>> &map)
    {
        Point &point = points[pointIndex];
        int delta = point.get_is_labeled()? -1 : 0;
        point.clear();

        std::vector<int> neighbours = map[pointIndex];
        int pos = pos_distr(gen);
        for (int index : neighbours)
        {
            delta += set_labels(points, static_cast<Point::Position>(pos), index, map);
            pos = pos_distr(gen);
        }
        delta += set_labels(points, static_cast<Point::Position>(pos), pointIndex, map);
        return delta;
    }

    int SimulatedAnnealing::set_labels3(std::vector<Point> &points, int pointIndex, std::vector<std::vector<int>> &map)
    {
        return 0;
    }


    int SimulatedAnnealing::random_set_labels(std::vector<Point> &points, int pointIndex,
                                              std::vector<std::vector<int>> &map)
    {
        int delta;
        int rand_int = pos_distr(gen);
        int pos = pos_distr(gen);
        if (rand_int == 1)
        {
            delta = set_labels(points, static_cast<Point::Position>(pos), pointIndex, map);
        }
        else
        {
            delta = set_labels2(points, pointIndex, map);
        }

        return delta;
    }

    void SimulatedAnnealing::print_progress(int c_opt, int solution_size, int step_count, double temp) const
    {
        double progress = (double) c_opt / (double) solution_size;
        int barWidth = 50;

        std::cout << "[";
        int pos = (int) (barWidth * progress);
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

        std::cout << "] " << double(progress * 100.0) << " %\r";
        std::cout << "Step " << step_count << " of " << steps << " t_i: " << temp << "  c_opt: ";
        std::cout.flush();
    }

    double SimulatedAnnealing::reanealing_temperature_bound(double current_temp)
    {
        if(current_temp < 0.0001)
        {
            current_temp = t_i;
            return current_temp;
        }
        return current_temp;
    }



} // namespace PointLabeler