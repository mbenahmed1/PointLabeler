import sys
import os

if __name__ == "__main__":

    if len(sys.argv) != 2 and len(sys.argv) != 3:
        print("usage: $python convertInstance.py path/to/file.txt [scalefactor]")
        exit()



    filename = str(sys.argv[1])
    scalefactor = 1
    if len (sys.argv) == 3:
        scalefactor = int(sys.argv[2])
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
            x = round(float(split[0]) * scalefactor)
            y = round(float(split[1]) * scalefactor)
            w = (len(name) + 4) * scalefactor
            h = 6 * scalefactor

            print(name, x, y, w, h)
            
            l1 = 0
            l2 = 0
            l3 = 0
        
            newline = f"{x} {y} {w} {h} {name} {l1} {l2} {l3}\n"
            
            fout.write(newline)
 
