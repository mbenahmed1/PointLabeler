import matplotlib.pyplot as plt
import sys


# ***** format ***** 
# #_[num_variables]
# t_[title]
# x_[x_axis_caption]
# y_[y_axis_caption]
# format_[x_min] [x_max] [y_min] [y_max]
# label_[labelname_1]
# ...
# label_[labelname_n]
# [y_1] [x_1] ... [y_n][x_n]
# ...

markers = ["h", "x", "o", "v", "^", "<", ">", "1", "2", "3", "4", "8", "s", "*", "X", "D"]

if __name__ == "__main__":

    scaled = 0
    x_max = 0
    x_min = 0
    y_max = 0
    y_min = 0

    # case no scaling is beeing used
    if len(sys.argv) == 2:
        print("Applying default scaling.")
        filename = str(sys.argv[1])
        # case scaling is beeing used
    elif len(sys.argv) == 6:
        print("Scaling axis.")
        scaled = 1
        filename = str(sys.argv[1])
        x_min = float(sys.argv[2])
        x_max = float(sys.argv[3])
        y_min = float(sys.argv[4])
        y_max = float(sys.argv[5])
        # case params did not match pattern
    else:
        print("usage: $python3 plotter.py path/to/file.txt or $python3 plotter.py path/to/file.txt [x_min] [x_max] [y_min] [y_max]")
        exit()
        
    print("reading \"" + filename + "\".")

    x_caption = ""
    y_caption = ""
    title = ""
    num_variables = 0

    with open(filename) as data:

        # finding number of variables
        for line in data:
            if line.startswith("#"):
                num_variables = int(line.replace("#_", ""))
                break
        
        # finding title
        for line in data:
            if line.startswith("t"):
                # removing backslash
                line = line.replace("\n", "")
                title = line.replace("t_", "")
                break
        
        # finding x_caption
        for line in data:
            if line.startswith("x"):
                # removing backslash
                line = line.replace("\n", "")
                x_caption = line.replace("x_", "")
                break
        
        # finding y_caption
        for line in data:
            if line.startswith("y"):
                # removing backslash
                line = line.replace("\n", "")
                y_caption = line.replace("y_", "")
                break
        
        if num_variables > 16:
            print("Too many variables. Max. num_variables = 16.")
            exit

        # creating list of num_varibles times list
        lst = [ [] for _ in range(num_variables) ]

        i = 0
        # writing label names at the beginning of each list
        for line in data:
            if line.startswith("label_"):
                # removing backslash
                line = line.replace("\n", "")
                lst[i].append(line.replace("label_", ""))
                i += 1
            else:
                continue
    
    with open(filename) as data:
        # writing coordinates into lists
        # counter
        k = 0
        for line in data:
            # if line is a head line
            if line.startswith("#_") or line.startswith("t_") or line.startswith("x_") or line.startswith("y_") or line.startswith("label_") or line.startswith("format_"):
                #print("here")
                k += 1
                continue
            # else it is a data line
            else:
                #print("there")
                k += 1
                # get coordinates between spaces
                # removing backslash
                line = line.replace("\n", "")
                item = line.split(" ")
                # if there are not enough coordinates print error
                #print(num_variables)
                #print(len(item))
                if len(item) != num_variables * 2:
                    
                    print("Wrong number of coordinates in row " + str(k))
                    exit()
                # for each variable
                #print(num_variables)
                k = 0
                for j in range(num_variables):
                    # append variable list with x and y coordinates
                    # x
                    #print(item[j])
                    #print(item[j+1])
                    lst[j].append(float(item[k]))
                    # y
                    lst[j].append(float(item[k+1]))
                    k += 2
     



    
    # create plots
    i = 0
    for variable in lst:
        x = variable[1:-1:2]
        y = variable[2:len(variable):2]
        plt.plot(y, x,  marker=markers[i], linestyle='-', label=variable[0])
        i += 1
    
    if scaled == 1:
        plt.xlim(x_min, x_max)
        plt.ylim(y_min, y_max)
        
    
    plt.title(title)
    plt.xlabel(x_caption)
    plt.ylabel(y_caption)

    
 
    plt.legend()
    plt.grid()
    plt.show()