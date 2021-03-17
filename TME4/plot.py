import numpy as np
import matplotlib.pyplot as plt

with open('google_scholar.txt') as f:
    lines = f.readlines()
    x = [int(line.split()[0]) for line in lines]
    y = [int(line.split()[1]) for line in lines]

t = np.arange(287426)
plt.title("Google Scholar")
plt.xlabel("Degree")
plt.ylabel("Coreness")

plt.scatter(x, y, c=t)

plt.colorbar()

plt.show()