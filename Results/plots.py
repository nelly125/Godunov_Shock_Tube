import math
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import os
import pylab

##  read model file
#fname = 'model_spectrum_090412.dat'
#print('Model filename = ', fname)
#f = open(fname, 'r')
#model = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
#f.close()
#print(model)

##   read data file
fname = 'pointsU.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataU = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = 'pointsR.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataR = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = 'pointsP.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataP = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = 'sound.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataM = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = 'entropy.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataS = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()
#print(data)

##  plot figure

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
pylab.figure (1)
plt.plot(dataU[:,0], dataU[:,1], '-', markersize=3.0, linewidth=2.0, label="")
plt.title('velocity')
plt.savefig('velocity.png')

pylab.figure (2)
plt.plot(dataR[:,0], dataR[:,1], '-', markersize=3.0, linewidth=2.0, label="")
plt.title('density')
plt.savefig('density.png')

pylab.figure (3)
plt.plot(dataP[:,0], dataP[:,1], '-', markersize=3.0, linewidth=2.0, label="")
plt.title('pressure')
plt.savefig('pressure.png')

pylab.figure (4)
plt.plot(dataM[:,0], dataM[:,1], '-', markersize=3.0, linewidth=2.0, label="")
plt.title('sound')
plt.savefig('sound.png')
"""

plt.plot(dataP[:,0], dataP[:,1], 'ro-', color='yellow', markersize=0.5, linewidth=0.5, label="Pressure")
plt.plot(dataU[:,0], dataU[:,1], 'ro-', color='blue', markersize=0.5, linewidth=0.5, label="Velocity")
plt.plot(dataR[:,0], dataR[:,1], 'ro-', color='grey', markersize=1.5, linewidth=1.5, label="Density")
plt.plot(dataM[:,0], dataM[:,1], 'ro-', color='black', markersize=1.5, linewidth=1.5, label="Mach number")
plt.plot(dataS[:,0], dataS[:,1], 'ro-', color='orange', markersize=1.5, linewidth=1.5, label="Entropy")


plt.savefig('general.png')
"""

#plt.xlim(0, 1.5)
#plt.ylim(10, 1000000)
#plt.xscale('log')
#plt.yscale('log')
#plt.xlabel('Wavelength, [Angstrom]')
#plt.ylabel('Normalized intensity')
plt.grid(True)
plt.legend(loc='upper right', fontsize=10)

#plt.subplots_adjust(
#top=0.954,
#bottom=0.059,
#left=0.041,
#right=0.986,
#hspace=0.2,
#wspace=0.159
#)
#plt.subplots_adjust(left=0.1, bottom=0.1, right=0.95, top=0.95, wspace=0.3, hspace=0.45)

#plt.savefig('result.png')
plt.show()
