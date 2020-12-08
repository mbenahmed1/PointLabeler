/**
 * PointLabeler.cpp
 *
 *  @date 31.10.2020
 *  @author Tim Adam (tadam@uos)
 *  @author Martin ben Ahmed (mbenahmed@uos)
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "Map.hpp"
#include "GreedyAlgorithm.hpp"
#include "Normals.hpp"
#include "SimulatedAnnealing.hpp"

using namespace PointLabeler;
// default algorithm
const std::string DEFAULT_SOLVER = "SA";

// default parameters for Simulated Annealing
constexpr double DEFAULT_ALPHA = 0.9999;
constexpr int DEFAULT_STEPS = 100000;
constexpr int DEFAULT_T0 = 1;

// default paramters for Normals
constexpr int DEFAULT_NEIGHBORHOOD = 1000;


/**
 * Checks if string ends with .txt
 * 
 *@param str string to check
 *@param suffix suffix to check
 */
bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/**
 * Prints messages to the terminal with time
 * 
 *@param text to be printed on the console
 */
int print_message(std::string text)
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    std::cout << buf << ":" << " " << text << std::endl;
    return 1;
}

/**
 * Prints usage
 */
int print_usage()
{
    std::cout << "usage:" << std::endl;
    std::cout << "$ ./PointLabeler -in [INPUT_FILENAME].txt -out [OUTPUT_FILENAME].txt" << std::endl;
    std::cout << "or" << std::endl;
    std::cout << "$ ./PointLabeler --random-gen [OUTPUT_FILENAME].txt" << std::endl;
    std::cout << "or" << std::endl;
    std::cout << "$ ./PointLabeler --cluster-gen [OUTPUT_FILENAME].txt\n" << std::endl;

    std::cout << "The current default solver is: " << DEFAULT_SOLVER << std::endl;

    std::cout << "To change the solver append one of the following flags to the first command:\n" << std::endl;
    std::cout << "SIMULATED ANNEALING: -sa\n" << std::endl;
    std::cout << "    [-alpha] (=" << DEFAULT_ALPHA << ") \t The temperature multiplier after each iteration." << std::endl;
    std::cout << "    [-steps] (=" << DEFAULT_STEPS << ") \t Number of iterations before halting." << std::endl;
    std::cout << "    [-t]     (=" << DEFAULT_T0 << ") \t Starting temperature.\n" << std::endl;

    std::cout << "GREEDY ALGORITHM: -g\n" << std::endl;

    std::cout << "NORMAL ALGORITHM: -n [RADIUS]\n" << std::endl;

    return 1;
}

/**
 * Reads from file
 * 
 *@param filename name of the text file
 */
int read_file(std::string filename)
{

    std::string message = "Start reading file \"";
    message.append(filename);
    message.append("\".");
    print_message(message);

    std::ofstream file;
    file.open(filename);
    file << "Test\n";
    file.close();


    message = "Finished reading file \"";
    message.append(filename);
    message.append("\".");
    print_message(message);
    return 0;

}

/**
 * Checks if a given solution is valid.
 *
 * @param solution - vector containing points which represent the solution
 * @return true if valid, else false
 */
void evaluate_solution(std::vector<Point> &solution)
{
    std::string valid = "The given solution is valid.";
    // check overlap
    for (int i = 0; i < solution.size() - 1; i++)
    {
        if (solution[i].get_is_labeled() == 0)
        {
            continue;
        }
        for (int j = i + 1; j < solution.size(); j++)
        {
            if (solution[j].get_is_labeled() == 0)
            {
                continue;
            }
            if (solution[i].is_overlapping(solution[j]))
            {
                std::cout << "ERROR: point " << i << " (" << solution[i].get_label_text() << ") "
                          << "is overlapping point " << j << " (" << solution[j].get_label_text() << ") " << std::endl;
                return;
            }
        }
    }
    // check if labels are connected to points
    for (int i = 0; i < solution.size(); i++)
    {
        Point p = solution[i];
        if (p.get_is_labeled() == 0)
        {
            continue;
        }
        int lx = p.get_label_x();
        int ly = p.get_label_y();
        int x = p.get_x();
        int y = p.get_y();
        int w = p.get_label_length();
        int h = p.get_label_height();
        // bottom right
        if (lx == x && ly == y)
        {
            continue;
        }
        // top left
        if (lx + w == x && ly - h == y)
        {
            continue;
        }
        // bottom left
        if (lx == x && ly - h == y)
        {
            continue;
        }
        // top right
        if (lx + w == x && ly == y)
        {
            continue;
        }
        std::cout << "ERROR: label of point " << i << " ("<< p.get_label_text() << ") is not touching the point" << std::endl;
        return;
    }
    std::cout << valid << std::endl;
}

int get_labeled_count(std::vector<Point> &points)
{
    int count = 0;
    for (auto &p : points)
    {
        if (p.get_is_labeled() == 1)
        {
            count++;
        }
    }
    return count;
}

/**
 * main
 * 
 *@param you know...
 */
int main(int argc, char **argv)
{
    std::string read_filename;
    std::string write_filename;
    PointLabeler::Map map = PointLabeler::Map(read_filename);
    std::string arg1;
    std::string arg2;
    std::string arg3;
    std::string arg4;


    // if 3 args are given (generate random with filepath)
    if (argc == 3)
    {
        arg1 = argv[1];
        arg2 = argv[2];


        if (arg1 == "--cluster-gen")
        {
            int i = 1;
            std::vector<PointLabeler::Point> *points = map.cluster_generate_points(100*i, -100*i, 100*i, -100*i, 25*i, 12*i, 2000*i, 10*i, 1000*i, 25*i);
            for(int i = 1; i < 101; i++)
            {
            write_filename = arg2;
            print_message("Generate cluster instance.");
            points = map.cluster_generate_points(100*i, -100*i, 100*i, -100*i, 25*i, 12*i, 2000*i, 10*i, 1000*i, 25*i);
            
            
            print_message("Write to file \"" + std::to_string(i-1) + write_filename + "\".");
            map.write_to_file(points, std::to_string(i-1) + write_filename);
            
            }
            return 1;
        }
        if (arg1 == "--random-gen")
        {
            write_filename = arg2;
            print_message("Generate random instance.");
            std::vector<PointLabeler::Point> *points = map.random_generate_points(100, -100, 100, -100, 10, 6, 25);
            print_message("Write to file \"" + write_filename + "\".");
            map.write_to_file(points, write_filename);
            return 1;
        }
        if (arg1 == "-eval")
        {
            std::vector<Point> *points = map.load_from_file(arg2);
            evaluate_solution(*points);
            return 1;
        }
        else
        {
            print_usage();
            return -1;
        }
    }

    // if 5 or more args are given (read from file, calculate solution, write to file)
    if (argc >= 5)
    {
        arg1 = argv[1];
        arg2 = argv[2];
        arg3 = argv[3];
        arg4 = argv[4];

        if (arg1 == "-in" && arg3 == "-out" && has_suffix(argv[2], ".txt") && has_suffix(argv[4], ".txt"))
        {
            write_filename = arg4;
            read_filename = arg2;
            //print_message("Read from file: \"" + read_filename + "\".");
            std::vector<PointLabeler::Point> *points = map.load_from_file(read_filename);

            std::string current_solver = DEFAULT_SOLVER;
            double current_alpha = DEFAULT_ALPHA;
            int current_steps = DEFAULT_STEPS;
            int current_t0 = DEFAULT_T0;

            int current_neighborhood = DEFAULT_NEIGHBORHOOD;

            // parse algorithm args
            if (argc >= 6) {
                std::string algorithm = argv[5];

                if (algorithm == "-sa") {

                    current_solver = "SA";

                    for (int i = 6; i < argc; i += 2)
                    {
                        std::string param = argv[i];
                        std::string value = argv[i + 1];

                        if (param == "-alpha")
                        {
                            current_alpha = std::stod(value);
                        }
                        if (param == "-steps")
                        {
                            current_steps = std::stoi(value);
                        }
                        if (param == "-t")
                        {
                            current_t0 = std::stoi(value);
                        }
                    }
                }
                if (algorithm == "-n")
                {
                    current_solver = "N";
                    if (argc >= 7)
                    {
                        current_neighborhood = std::stoi(argv[6]);
                    }
                }
                if (algorithm == "-g")
                {
                    current_solver = "G";
                }
            }

            double current_duration = 0.0;

            // solve with greedy algorithm
            if (current_solver == "G")
            {
                print_message("running Greedy Algorithm");
                PointLabeler::GreedyAlgorithm greedyAlgorithm = PointLabeler::GreedyAlgorithm(*points);
                auto start = std::chrono::high_resolution_clock::now();
                greedyAlgorithm.solve();
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                current_duration = (double) duration;
            }
            // solve with normal algorithm
            if (current_solver == "N")
            {
                print_message("running Normals with neighborhoods: " +  std::to_string(current_neighborhood));
                PointLabeler::Normals normals = PointLabeler::Normals(current_neighborhood);
                auto start = std::chrono::high_resolution_clock::now();
                normals.solve(*points);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                current_duration = (double) duration;
            }
            // solve with simulated annealing
            if (current_solver == "SA")
            {
                // choose alpha close to 1, the closer the solver the decay
                print_message("running SA with steps: " + std::to_string(current_steps) + " alpha: " + std::to_string(current_alpha) +" t0: " + std::to_string(current_t0));
                PointLabeler::SimulatedAnnealing sa = PointLabeler::SimulatedAnnealing(current_steps, current_alpha, current_t0);
                auto start = std::chrono::high_resolution_clock::now();
                sa.solve(*points);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                current_duration = (double) duration;
            }

            // print how many % were labeled
            int labeled_count = get_labeled_count(*points);
            int label_count = points->size();
            float rate = 0.0;
            rate = labeled_count / (float)label_count;


            //print_message("Write to file: \"" + write_filename + "\".");
            print_message("Labeled Rate: " + std::to_string(rate * 100) + "%");
            std::cout << get_labeled_count(*points) << "\t" << current_duration/1000 << std::endl;
            map.write_to_file(points, write_filename);

            return 1;
        }
        else
        {
            print_usage();
            return -1;
        }
    }
    else
    {
        print_usage();
        return -1;
    }
}
