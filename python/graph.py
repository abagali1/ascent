#!/usr/bin/env python3
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('data/linaccel.txt', delimiter=' ', header=None, index_col=None)

x, y, z = data.T.values
print(np.std(x), np.std(z))

fig, ax = plt.subplots(figsize = (10, 6))

# Remove axis for what seems to be literally nothing
plt.axis("off")

# ROCKET ORBIT
orbit_plot = fig.add_subplot(121)
orbit_plot.grid()
scatter_rocket = orbit_plot.plot(x)
orbit_plot.title.set_text("X Acceleration")

# DISTANCE
dist_plot = fig.add_subplot(222)
dist_plot.grid()
dist_plot.plot(y)
dist_plot.title.set_text("Y Acceleration")

# SPEED
speed_plot = fig.add_subplot(224)
speed_plot.grid()
speed_plot.plot(z)
speed_plot.title.set_text("Z Acceleration")

fig.tight_layout(pad=2)

plt.savefig('plot.png')
plt.show()
