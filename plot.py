import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

X_SIZE = 50
Y_SIZE = 50

data = np.loadtxt(fname = "out", delimiter="; ")

x = np.arange(0, X_SIZE, 1)
y = np.arange(0, Y_SIZE, 1)
X, Y = np.meshgrid(x, y)

result=np.zeros((X_SIZE,Y_SIZE))

count = 0
for j in range(X_SIZE):
    for i in range(Y_SIZE):
        result[i][j] = data[count][4]
        count = count + 1

fig, ax = plt.subplots()
cs = ax.contourf(X, Y, result, cmap=cm.gist_rainbow)
cbar = fig.colorbar(cs)

plt.show()
