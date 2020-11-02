import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import sys


if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("usage: $python visualizer.py path/to/file.txt")
        exit()

    filename = str(sys.argv[1])

    print("reading " + filename + " ...")

    pX = []
    pY = []
    rX = []
    rY = []
    rW = []
    rH = []
    draw = []
    

    with open(filename) as data:

        firstLine = True

        for line in data:
            if firstLine:
                firstLine = False
                continue

            item = line.split(" ")
    
            pX.append(int(item[0]))
            pY.append(int(item[1]))
            rW.append(int(item[2]))
            rH.append(int(item[3]))
            draw.append(int(item[5]))
            rX.append(int(item[6]))
            rY.append(int(item[7]))

    
    def plot_rect(ax, x, y, w, h):
        rect = plt.Rectangle((x,y), w, -h, edgecolor="k")
        ax.add_patch(rect)
        
    
    def plot_point(ax, x, y, color="k"):
        ax.scatter([x], [y], s=36, color=color, zorder=3)


    my_dpi = 150
    fig, ax = plt.subplots(figsize=(800/my_dpi, 800/my_dpi), dpi=my_dpi)
    ax.set_axisbelow(True)

    for px, py, rx, ry, rw, rh, drawable in zip(pX, pY, rX, rY, rW, rH, draw):
        if drawable == 0:
            plot_point(ax, px, py, "r")
        else:
            plot_point(ax, px, py)
            plot_rect(ax, rx, ry, rw, rh)


    minLim = min(min(pX) - max(rW), min(pY) - max(rH))
    maxLim = max(max(pX) + max(rW), max(pY) + max(rH))

    ax.set(xlim=(minLim, maxLim), ylim=(minLim, maxLim))
    
    #ticks = np.arange(minLim, maxLim, 1)
    #plt.xticks(ticks)
    #plt.yticks(ticks)

    #plt.grid()

    plt.show()