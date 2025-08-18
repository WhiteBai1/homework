import matplotlib.pyplot as plt

import numpy as np
#plot 1:
xpoints = np.array([0,10,100,1000,10000,50000,100000,500000,1000000])
randommerge = np.array([0,0.004,0.005,0.005,0.010,0.031,0.072,0.551,0.812])
randomheap = np.array([0,0.005,0.005,0.005,0.010,0.032,0.157,0.374,1.017])
randomquick = np.array([0,0.005,0.005,0.005,0.010,0.055,0.138,0.504,1.314])
plt.subplot(1,3,1)
plt.title("random")
plt.plot(xpoints,randommerge,'-r',label= "mergesort")
plt.plot(xpoints,randomheap,'-b',label = "heapsort")
plt.plot(xpoints,randomquick,'-y',label = "qiucksort")
plt.legend(loc = 'upper right')

#plot2
xpoints1 = np.array([0,10,100,1000,10000,50000,100000,500000])
ordermerge = np.array([0,0.005,0.004,0.005,0.009,0.049,0.115,0.424,0.758])
orderheap = np.array([0,0.005,0.004,0.005,0.009,0.043,0.101,0.437,0.943])
orderquick = np.array([0,0.005,0.004,0.006,0.031,0.347,1.21,24.5])
plt.subplot(1,3,2)
plt.title("order")
plt.plot(xpoints,ordermerge,'-r',label= "mergesort")
plt.plot(xpoints,orderheap,'-b',label = "heapsort")
plt.plot(xpoints1,orderquick,'-y',label = "qiucksort")
plt.legend(loc = 'upper right')

#plot3
xpoints2 = np.array([0,10,100,1000,10000,50000,100000])
revmerge = np.array([0,0.004,0.005,0.005,0.008,0.056,0.094,0.431,0.842])
revheap = np.array([0,0.005,0.004,0.005,0.009,0.065,0.082,0.449,0.816])
revquick = np.array([0,0.004,0.005,0.006,0.055,1.042,3.908])
plt.subplot(1,3,3)
plt.title("reverse")
plt.plot(xpoints,revmerge,'-r',label= "mergesort")
plt.plot(xpoints,revheap,'-b',label = "heapsort")
plt.plot(xpoints2,revquick,'-y',label = "qiucksort")
plt.legend(loc = 'upper right')

plt.xlabel("N")
plt.ylabel("Time")

plt.show()