import matplotlib
import numpy as np
import matplotlib.pyplot as plt
import csv

with open('magnus.txt') as f:
    csv_input = csv.reader(f, delimiter=' ', skipinitialspace=True)
    x = []
    y = []

    for cols in csv_input:
        x.append(int(cols[0]))
        y.append(float(cols[1]))

t = np.arange(2070486)

plt.title("proximity ti magnus")

plt.scatter(x, y, c=t)

plt.show()