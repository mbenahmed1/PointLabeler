#include "Map.hpp"

namespace PointLabeler{


std::vector<std::string> cities = { "Berlin", 
                                    "Hamburg", 
                                    "Munic", 
                                    "Cologne", 
                                    "Frankfurt",
                                    "Stuttgart",
                                    "Düsseldorf",
                                    "Dortmund",
                                    "Essen",
                                    "Leipzig",
                                    "Bremen",
                                    "Dresden",
                                    "Hanover",
                                    "Nuremberg",
                                    "Duisburg",
                                    "Bochum",
                                    "Wuppertal",
                                    "Bielefeld",
                                    "Bonn",
                                    "Münster",
                                    "Karlsruhe",
                                    "Mannheim",
                                    "Augsburg",
                                    "Wiesbaden",
                                    "Gelsenkirchen",
                                    "Mönchengladbach",
                                    "Braunschweig",
                                    "Chemnitz",
                                    "Kiel",
                                    "Aachen",
                                    "Halle",
                                    "Magdeburg",
                                    "Freiburg",
                                    "Krefeld",
                                    "Lübeck",
                                    "Oberhausen",
                                    "Erfurt",
                                    "Mainz",
                                    "Rostock",
                                    "Kassel",
                                    "Hagen",
                                    "Hamm",
                                    "Saarbrücken",
                                    "Mülheim",
                                    "Potsdam",
                                    "Ludwigshafen",
                                    "Oldenburg",
                                    "Leverkusen",
                                    "Osnabrück",
                                    "Solingen",
                                    "Heidelberg",
                                    "Herne",
                                    "Neuss",
                                    "Darmstadt",
                                    "Paderborn",
                                    "Regensburg",
                                    "Ingolstadt",
                                    "Würzburg",
                                    "Fürth",
                                    "Wolfsburg",
                                    "Führt",
                                    "Wolfsburg",
                                    "Offenbach",
                                    "Ulm",
                                    "Heilbronn",
                                    "Pforzheim",
                                    "Göttingen",
                                    "Bottrop",
                                    "Trier",
                                    "Recklingshausen",
                                    "Bremerhaven",
                                    "Koblenz", 
                                    "BergischGladbach",
                                    "Jena",
                                    "Remscheid",
                                    "Erlangen",
                                    "Moers",
                                    "Siegen",
                                    "Hildesheim",
                                    "Salzgitter"};


Map::Map(std::string filename)
{
    Map::filename = filename;
    Map::x_size = 0;
    Map::y_size = 0;
    Map::number_of_points = 0;
}

int Map::get_x_size()
{
    return Map::x_size;
}

int Map::get_y_size()
{
    return Map::y_size;
}

std::string Map::get_filename()
{
    return Map::filename;
}

int Map::load_from_file(std::string filename)
{
    // opening input filestream
    std::ifstream file(filename);
    if (!file.good())
    {
        std::cerr << "Cannot open file." <<std::endl;
        return -1;
    }

    // number of points = number of lines + 1
    file >> Map::number_of_points;
    
    // variables to fill points in
    int x_pos = 0;
    int y_pos = 0;
    int length = 0;
    int height = 0;
    std::string label_text = "";
    int is_labeled = 0;
    int label_x = 0;
    int label_y = 0;

    // reading values line by line
    for(int i = 0; i < number_of_points; i++)
    {
        file >> x_pos;
        file >> y_pos;
        file >> length;
        file >> height;
        file >> label_text;
        file >> is_labeled;
        file >> label_x;
        file >> label_y;
    }

    // TODO: parse points

    // debug
    std::cout << x_pos << std::endl;
    std::cout << y_pos << std::endl;
    std::cout << length << std::endl;
    std::cout << height << std::endl;

    return 1;
}

std::vector<Point>* Map::random_generate_points(int max_x_pos, int min_x_pos, int max_y_pos, int min_y_pos, int max_label_length, int max_label_height, int number_of_points)
{
    // check if max_x_pos is true greater than min_x_pos
    if(!(max_x_pos > min_x_pos))
    {
        std::cerr << "max_x_pos has to be greater than min_x_pos" << std::endl;
    }

    // check if max_y_pos is true greater than min_y_pos
    if(!(max_y_pos > min_y_pos))
    {
        std::cerr << "max_y_pos has to be greater than min_y_pos" << std::endl;
    }   

    // check if both label lenght and heigth are greater than 1
    if(!(max_label_height > 1 && max_label_length >1))
    {
        std::cerr << "max_label_height and max_label_length have to be greater than 1" << std::endl;
    }

    // check if number of points is greater than 1
    if(!(number_of_points > 1))
    {
        std::cerr << "number of points has to be greater than 1" << std::endl;
    }

    
    // setting up random number generator
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> x_distr(min_x_pos, max_x_pos);
    std::uniform_int_distribution<> y_distr(min_y_pos, max_y_pos);
    std::uniform_int_distribution<> label_length_distr(1, max_label_length);
    std::uniform_int_distribution<> label_height_distr(1, max_label_height);
    std::uniform_int_distribution<> label_distr(100000, 999999);

    int x_pos = 0;
    int y_pos = 0;
    int label_length = 0;
    int label_height = 0;
    std::string label_text = "";

    std::vector<PointLabeler::Point> *points = new std::vector<Point>;

    for(int n=0; n < number_of_points; ++n)
    {

        x_pos = x_distr(gen);
        y_pos = y_distr(gen);
        label_length = label_length_distr(gen);
        label_height = label_height_distr(gen);
        label_text = std::to_string(label_distr(gen));

        //std::cout << "x: " << x_pos << " y: " << y_pos << " label: " << label_text << std::endl;
        
        
        points->push_back(Point(x_pos, y_pos, label_length, label_height, label_text));
    }

    return points;

}


std::vector<Point>* Map::cluster_generate_points(int max_x_pos, int min_x_pos, 
                                                int max_y_pos, int min_y_pos, 
                                                int max_label_length, int max_label_height, 
                                                int number_of_points, int number_of_clusters,
                                                int max_cluster_size, int max_cluster_radius)
{
    // check if max_x_pos is true greater than min_x_pos
    if(!(max_x_pos > min_x_pos))
    {
        std::cerr << "max_x_pos has to be greater than min_x_pos" << std::endl;
    }

    // check if max_y_pos is true greater than min_y_pos
    if(!(max_y_pos > min_y_pos))
    {
        std::cerr << "max_y_pos has to be greater than min_y_pos" << std::endl;
    }   

    // check if both label lenght and heigth are greater than 1
    if(!(max_label_height > 1 && max_label_length >1))
    {
        std::cerr << "max_label_height and max_label_length have to be greater than 1" << std::endl;
    }

    // check if number of points is greater than 1
    if(!(number_of_points > 1))
    {
        std::cerr << "number of points has to be greater than 1" << std::endl;
    }

    if(!(number_of_clusters > 1))
    {
        std::cerr << "number of clusters has to be greater than 1" << std::endl;
    }

    if(!(max_cluster_size < number_of_points))
    {
        std::cerr << "max cluster size has to be smaller than number of points" << std::endl;
    }
    

    // setting up random number generator
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> x_distr(min_x_pos, max_x_pos);
    std::uniform_int_distribution<> y_distr(min_y_pos, max_y_pos);
    std::uniform_int_distribution<> label_length_distr(1, max_label_length);
    std::uniform_int_distribution<> label_height_distr(1, max_label_height);
    std::uniform_int_distribution<> label_distr(100000, 999999);
    std::uniform_int_distribution<> cluster_size_distr(1, max_cluster_size);
    std::uniform_int_distribution<> cluster_radius_distr(-(max_cluster_radius/2), (max_cluster_radius/2));

    int x_pos = 0;
    int y_pos = 0;
    int label_length = 0;
    int label_height = 0;
    std::string label_text = "";

    std::vector<PointLabeler::Point> *points = new std::vector<Point>;

    for(int i = 0; i < number_of_clusters; i++)
    {
    
        if(points->size() == number_of_points)
        {
            break;
        }       
        
        // generating cluster center point
        x_pos = x_distr(gen);
        y_pos = y_distr(gen);
        label_length = label_length_distr(gen);
        label_height = label_height_distr(gen);
        label_text = std::to_string(label_distr(gen));

        points->push_back(Point(x_pos, y_pos, label_length, label_height, label_text));

        for(int j = 0; j < cluster_size_distr(gen); j++)
        {
            
            if(points->size() == number_of_points)
            {
                break;
            }

            x_pos += cluster_radius_distr(gen);
            y_pos += cluster_radius_distr(gen);
            label_length = label_length_distr(gen);
            label_height = label_height_distr(gen);
            label_text = std::to_string(label_distr(gen));

            points->push_back(Point(x_pos, y_pos, label_length, label_height, label_text));

        }
    }

    
    return points;
}

int Map::write_to_file(std::vector<Point> *points, std::string filename)
{
    std::ofstream file;
    file.open(filename);

    int number_of_points = points->size();
    
    file << number_of_points;
    file << "\n";

    std::vector<Point>::iterator it;
    
    
    int i = 0;

    for(it = points->begin(); it != points->end(); it++, i++)    
    {
        file << it->get_x();
        file << " ";
        file << it->get_y();
        file << " ";
        file << it->get_label_length();
        file << " ";
        file << it->get_label_height();
        file << " ";
        file << it->get_label_text();
        file << " ";
        file << "0";
        file << " ";
        file << "0";
        file << " ";
        file << "0";
        file << "\n";
    }

    file.close();

    return 1;
    
}

}
