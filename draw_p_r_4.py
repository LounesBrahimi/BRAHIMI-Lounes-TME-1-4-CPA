import matplotlib
import numpy as np
import matplotlib.pyplot as plt
import csv

with open('correlation4.txt') as f:
    csv_input = csv.reader(f, delimiter=' ', skipinitialspace=True)
    x = []
    y = []

    for cols in csv_input:
        x.append(float(cols[0]))
        y.append(float(cols[1]))

t = np.arange(2070486)

plt.title("Correlation 4")
plt.xlabel("PageRank 0.15")
plt.ylabel("PageRank 0.2")

plt.scatter(x, y, c=t)

plt.show()