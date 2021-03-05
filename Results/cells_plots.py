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
fname = '1000pointsU.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataU1000 = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = '1000pointsR.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataR1000 = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = '1000pointsP.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataP1000 = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = '100pointsU.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataU100 = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = '100pointsR.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataR100 = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

fname = '100pointsP.txt'
print('Data filename = ', fname)
f = open(fname, 'r')
dataP100 = np.array([[float(l.split()[0]), float(l.split()[1])] for l in f])
f.close()

#print(data)

##  plot figure
"""
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

""""""
"""
plt.figure(1)
plt.plot(dataP1000[:,0], dataP1000[:,1], 'ro-', color='grey', markersize=1.5, linewidth=0.5, label="Pressure 1000 cells")
plt.plot(dataP100[:,0], dataP100[:,1], 'ro-', color='purple', markersize=1.5, linewidth=0.5, label="Pressure 100 cells")
plt.xlabel("x")
plt.ylabel("Pressure")
plt.grid()
plt.legend()
plt.savefig('pressure.png')

plt.figure(2)
plt.plot(dataU1000[:,0], dataU1000[:,1], 'ro-', color='red', markersize=2, linewidth=0.5, label="Velocity 1000")
plt.plot(dataU100[:,0], dataU100[:,1], 'ro-', color='green', markersize=2, linewidth=0.5, label="Velocity 100")
plt.xlabel("x")
plt.ylabel("Velocity")
plt.grid()
plt.legend()
plt.savefig('velocity.png')

pylab.figure(3)
plt.plot(dataR1000[:,0], dataR1000[:,1], 'ro-', color='black', markersize=1.5, linewidth=1.5, label="Density 1000")
plt.plot(dataR100[:,0], dataR100[:,1], 'ro-', color='blue', markersize=1.5, linewidth=1.5, label="Density 100")
plt.xlabel("x")
plt.ylabel("Density")
plt.grid()
plt.legend()
plt.savefig('density.png')




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