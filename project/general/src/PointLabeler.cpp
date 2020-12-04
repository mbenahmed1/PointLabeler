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
    std::cout << "$ ./PointLabeler --cluster-gen [OUTPUT_FILENAME].txt" << std::endl;
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

    // if 5 args are given (read from file, calculate solution, write to file)
    if (argc == 5)
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

           
           
            /*
            // solve with greedy Algorithm
            PointLabeler::GreedyAlgorithm greedyAlgorithm = PointLabeler::GreedyAlgorithm(*points);
            auto start = std::chrono::high_resolution_clock::now();
            greedyAlgorithm.solve();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            */

            /*
            // solve with normal algorithm
            PointLabeler::Normals normals = PointLabeler::Normals(3000);
            auto start = std::chrono::high_resolution_clock::now();
            normals.solve(*points);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            */

           
            // solve with simulated annealing algorithm
            // choose alpha close to 1, the closer the solver the decay
            
            PointLabeler::SimulatedAnnealing sa = PointLabeler::SimulatedAnnealing(200000, 0.9999, 1.0);
            auto start = std::chrono::high_resolution_clock::now();
            sa.solve(*points);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            



            // print how many % were labeled
            int labeled_count = get_labeled_count(*points);
            int label_count = points->size();
            float rate = 0.0;
            rate = labeled_count / (float)label_count;

            std::cout << get_labeled_count(*points) << "\t" << ((double) duration)/1000 << std::endl;
            //print_message("Write to file: \"" + write_filename + "\".");
            print_message("Labeled Rate: " + std::to_string(rate) + "%");
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
