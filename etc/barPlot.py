import matplotlib.pyplot as plt
import numpy as np

""" 
EXAMPLE FORMAT

AVG über c_r_rc_100_50_50:

"avg val of ALNS:    454.16"
"avg val of GA_A:    457.74"
"avg val of GA_B:    460.66"
"avg val of GCH:     450.61"
"avg val of ILS_S1:  487.32"
"avg val of ILS_S5:  487.61"
"avg val of SA:      468.88"

"avg runtime of ALNS:   39.14"
"avg runtime of GA_A:    3.8"
"avg runtime of GA_B:    7.43"
"avg runtime of GCH:     0.02"
"avg runtime of ILS_S1:  2.53"
"avg runtime of ILS_S5:  4.52"
"avg runtime of SA:     11.66"
"""



datafile = open("realtest.txt", "r")

labelcount = [357, 366, 1158]

labeled = []
runtime = []

for line in datafile:
    split = line.split(" ")

    if len(split) < 2:
        continue

    labeled.append(int(split[0]))
    runtime.append(float(split[1]))


def convertToPercent(labels):
    labels = [i / j for i, j in zip(labels, labelcount)] 



print(labeled)
print(runtime)
    
sa = labeled[::3]
n = labeled[2::3]
g = labeled[1::3]

sap = [100*i / j for i, j in zip(sa, labelcount)]
pn = [100*i / j for i, j in zip(n, labelcount)]
gp = [100*i / j for i, j in zip(g, labelcount)]


r_sa = runtime[::3]
r_n = runtime[2::3]
r_g = runtime[1::3]


data = []
data.append(g)
data.append(n)
data.append(sa)

datap = []
datap.append(gp)
datap.append(pn)
datap.append(sap)

runtime = []
runtime.append(r_g)
runtime.append(r_n)
runtime.append(r_sa)

print(data)


X = np.arange(3) * 4
#xpositions = [1, 6, 11]
xpositions = np.arange(1, 11, 4)
colors = ["#C33149", "#D24B62", "#5783B2", "#7398BF", "#3EB68A", "#58C69D", "#473F78", "#574D93", "#FFC05C", "#FFD085"]
my_dpi = 150
plt.figure(figsize=(1920/my_dpi, 1080/my_dpi), dpi=my_dpi)
bars = [None] * 3
bars[0] = plt.bar(X + 0.0, datap[0], color = colors[0], width = .8, label = "Greedy")
bars[1] = plt.bar(X + 1.0, datap[1], color = colors[2], width = .8, label = "Normals")
bars[2] = plt.bar(X + 2.0, datap[2], color = colors[4], width = .8, label = "SA")


#plt.vlines(34, 0, 1800, colors="k")

plt.title("Anteil an gelabelter Punkte und Laufzeit pro Echtweltinstanz und Algorithmus")

for j in range(3):
    i = 0
    for bar in bars[j]:
        value = runtime[j][i]
        yval = bar.get_height()
        plt.text(bar.get_x()+ 0.1, yval + 0.5, str(value) + "s", rotation = "horizontal")
        i += 1


# use for POI count comparisons
#plt.xticks([3.5,13.5,23.5,33.5,43.5], ('10', '50', '100', '250', '500'))

xlocs, xlabs = plt.xticks(xpositions, ["Berlin Touristenshops (357)", "Deutschland Bahnhöfe (366)", "US Städte (1158)"])#, rotation="vertical")


plt.ylim(50,100)
#plt.xlabel("Instanz")
plt.ylabel("Anteil gelabelter Punkte [%]")
plt.legend(loc = "best")
plt.show()
#plt.savefig("AVGplotTOPTW.png", dpi=my_dpi)
