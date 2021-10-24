from numpy import *
import math
import matplotlib.pyplot as plt

data = genfromtxt('serial_data.csv', delimiter=',')

t = linspace(0, 58.22, 2912)
right_sensor = data[:, 0]
left_sensor = data[:, 1]
right_wheel = data[:, 2]
left_wheel = data[:, 3]


fig, ax1 = plt.subplots()

color = 'tab:red'
ax1.set_xlabel('time (s)')
ax1.set_ylabel('sensor', color=color)
ax1.plot(t, right_sensor, 'r', label="Right Sensor Readings")
ax1.plot(t, left_sensor, 'b', label="Left Sensor Readings")
ax1.tick_params(axis='y', labelcolor=color)

# plt.legend()

ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax2.set_ylabel('wheel', color=color)  # we already handled the x-label with ax1
ax2.plot(t, right_wheel, 'g', label="Right Wheel Readings")
ax2.plot(t, left_wheel, 'y', label="Left Wheel Readings")
ax2.tick_params(axis='y', labelcolor=color)
# plt.legend()
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')
fig.tight_layout()  # otherwise the right y-label is slightly clipped
plt.show()
#
# plt.plot(t, right_sensor, 'r') # plotting t, a separately
# plt.plot(t, left_sensor, 'b') # plotting t, b separately
# plt.plot(t, right_wheel, 'g') # plotting t, c separately
# plt.plot(t, left_wheel, 'y') # plotting t, c separately
# plt.show()
