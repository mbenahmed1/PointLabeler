import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import sys
import pandas as pd
import seaborn as sns


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
    
    labeled = 0
    points = 0

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

            points += 1
            if int(item[5]) != 0:
                labeled += 1

    def drawRect(ax, x, y, w, h):
        ax.add_patch(patches.Rectangle((x,y), w, -h, facecolor="#ac0634", edgecolor="black", linewidth=1, linestyle='solid'))

    
    print(f"labeled {labeled}/{points} points ({100 * labeled/points}%)")

    fig1 = plt.figure()
    ax1 = fig1.add_subplot(111)

    pts = {'px':   pX,
           'py':   pY,
           'draw': draw}
    df = pd.DataFrame(pts, columns=['px', 'py', 'draw'])


    sns.scatterplot(data=df, x="px", y="py", s=25, color="0.25", marker="o")

    for px, py, rx, ry, rw, rh, drawable in zip(pX, pY, rX, rY, rW, rH, draw):
        if drawable == 1:
            drawRect(ax1, rx, ry, rw, rh)

    plt.show()
    #ticks = np.arange(minLim, maxLim, 1)
    #plt.xticks(ticks)
    #plt.yticks(ticks)

    #plt.grid()

    #plt.show()
