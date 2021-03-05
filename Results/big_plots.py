import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import pylab


exact = pd.read_csv('exsolution_of_sod', delimiter=' ', names=['r', 'u', 'p'])
dg = pd.read_csv('test1.txt', delimiter = ' ', names = ['r', 'u', 'p'])


lax = pd.read_csv('res.txt', delimiter = ' ', names = ['r', 'u', 'p'])



fig = plt.figure(figsize=(20, 14))
pylab.figure(1)
plt.plot(exact.r, linewidth=3, label="Exact")
plt.plot(dg.r, linewidth=3, label = "100 Godunov")
plt.title("Density")
plt.grid(True)
plt.legend(loc='upper right', fontsize=10)
plt.show()
# plt.savefig('godunov_density.png')