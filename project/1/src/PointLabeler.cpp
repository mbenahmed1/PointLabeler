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
     time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
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
    std::cout << "" << std::endl;
    std::cout << "usage:" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "$ ./PointLabeler --in [INPUT_FILENAME].txt --out OUTPUT_FILENAME].txt" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "or" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "$ ./PointLabeler --random-gen [OUTPUT_FILENAME].txt" << std::endl;
    std::cout << "or" << std::endl;
    std::cout << "" << std::endl;
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
 * main
 * 
 *@param you know...
 */

int main(int argc, char** argv)
{   

    std::string read_filename = "";
    std::string write_filename = "";
    PointLabeler::Map map = PointLabeler::Map(read_filename);
    std::string arg1 = "";
    std::string arg2 = "";
    std::string arg3 = "";
    std::string arg4 = "";
    


    // greeting the user
    std::cout << " " << std::endl;
    std::cout << "***************************************" << std::endl;
    std::cout << "******* Welcome to PointLabeler *******" << std::endl;
    std::cout << "***************************************" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " ~ Algorithm Engineering WS 2020/21 ~" << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;

    
    
    // if 3 args are given (generate random with filepath)
    if(argc == 3)
    {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];
        
        
        if(arg1 == "--cluster-gen" && has_suffix(argv[2], ".txt"))
        {
            write_filename = arg2;
            print_message("Generate cluster instance.");
            std::vector<PointLabeler::Point> *points = map.cluster_generate_points(100, -100, 100, -100, 10, 6, 2000, 10, 1000, 10);
            print_message("Write to file \"" + write_filename + "\".");
            map.write_to_file(points, write_filename);
            return 1;
        }
        
        
        if(arg1 == "--random-gen" && has_suffix(argv[2], ".txt"))
        {
            write_filename = arg2;
            print_message("Generate random instance.");
            std::vector<PointLabeler::Point> *points = map.random_generate_points(100, -100, 100, -100, 10, 6, 25);
            print_message("Write to file \"" + write_filename + "\".");
            map.write_to_file(points, write_filename);
            return 1;
        } else
        {
            print_usage();
            return -1;
        }
    } 

    // if 5 args are given (read from file, calculate solution, write to file)
    if(argc == 5)
    {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];
        std::string arg3 = argv[3];
        std::string arg4 = argv[4];
        
        if(arg1 == "--in" && arg3 == "--out" && has_suffix(argv[2], ".txt") && has_suffix(argv[4], ".txt"))
        {
            write_filename = arg4;
            read_filename = arg2;
            print_message("Read from file: \"" + read_filename + "\".");
            std::vector<PointLabeler::Point> *points = map.load_from_file(read_filename);

            for(int i = 1; i < points->size(); i++)
            {
                points->at(i).set_is_labeled(1);
                points->at(1).set_label_x(50);
                points->at(1).set_label_y(50);
            }

            print_message("Write to file: \"" + write_filename + "\".");
            map.write_to_file(points, write_filename);

            return 1;
        } else
        {
            print_usage();
            return -1;
        }

    } else
    {
        print_usage();
        return -1;
    }
    return 1;
}
