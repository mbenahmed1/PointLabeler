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
    std::cout << buf << " " << text << std::endl;
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
    std::cout << "PointLabeler [FILENAME].txt" << std::endl;
    std::cout << "" << std::endl;
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

    std::string filename;


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


    // if no additional args given print usage
    if(argc < 2)
    {
        print_usage();
        return -1;
    }
    
    
    // checks if file name has the right suffix (.txt)
    if(has_suffix(argv[1], ".txt"))
    {
        filename = argv[1];
    } else
    {
        print_usage();
        return -1;
    }
    
    
    
    PointLabeler::Map map = PointLabeler::Map(filename);
    //map.load_from_file(filename);
    std::vector<PointLabeler::Point> *points = map.random_generate_points(100, -100, 100, -100, 10, 6, 25);

    //map.write_to_file(points, "output.txt");

    

    
  

    

    std::cout << " " << std::endl;
    
    
    
    return 0;
}
