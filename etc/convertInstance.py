import sys
import os

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("usage: $python convertInstance.py path/to/file.txt")
        exit()



    filename = str(sys.argv[1])
    linecount = 0

    with open(filename, "r") as fin:
        for line in fin:
            if line.startswith("%") or line == "\n":
                continue
            
            split = line.split(" ")
            
            if len(split) < 3:
                continue

            linecount += 1
    
    with open(filename, "r") as fin:
        
        fout = open("output.txt", "w")
        fout.write(f"{linecount}\n")

        for line in fin:
            if line.startswith("%") or line == "\n":
                continue

            split = line.split(" ")
            
            if len(split) < 3:
                continue

            name = split[2].replace(" ", "_").strip('\n').strip('"')
            x = round(float(split[0]))
            y = round(float(split[1]))
            w = len(name) + 2
            h = 8

            print(name, x, y, w, h)
            
            l1 = 0
            l2 = 0
            l3 = 0
        
            newline = f"{x} {y} {w} {h} {name} {l1} {l2} {l3}\n"
            
            fout.write(newline)
 
