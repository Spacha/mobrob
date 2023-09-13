import matplotlib.pyplot as plt
import numpy as np

LOG_FILE = './data/putty.log'

MEAS_PERIOD = 0.001

data = []

with open(LOG_FILE, 'r') as f:
    for line in f.readlines():
        if len(line) > 1 and len(line) < 6:
            try:
                data.append( int(line.strip()) )
            except:
                pass

def moving_average(x, w):
    return np.convolve(x, np.ones(w), 'valid') / w

################################################################################

def find_crossings(upper_limit, lower_limit):
    up_crossings = []
    down_crossings = []
    cycles = []
    #periods = [0]

    transitions = 0

    avg_data = moving_average(data, 2)

    is_down = avg_data[0] <= lower_limit
    print(f"Starting from {'DOWN' if is_down else 'UP'}\n")
    for i, v in enumerate(avg_data):
        if v <= lower_limit:
            if is_down == False:
                print(f"Crossing DOWN at {i} (from {v} to {avg_data[i - 1]})")
                transitions += 1
                if transitions >= 2:
                    transitions = 0
                    cycles.append(i)
                    #periods.append(i - periods[-1])
                down_crossings.append(i)
            is_down = True
        elif v >= upper_limit:
            if is_down == True:
                print(f"Crossing UP at {i} (from {v} to {avg_data[i - 1]})")
                transitions += 1
                if transitions >= 2:
                    transitions = 0
                    cycles.append(i)
                    #periods.append(i - periods[-1])
                up_crossings.append(i)
            is_down = False
    
    return up_crossings, down_crossings, cycles

up_crossings, down_crossings, cycles = find_crossings(4085, 3800)

periods = []
for i, c in enumerate([0] + cycles):
    if i == 0:
        continue
    periods.append(c - ([0] + cycles)[i - 1])
    print(c, cycles[i - 1])

print(cycles)

plt.figure(figsize=(18,9))
plt.subplot(2, 1, 1)

plt.plot(data, zorder=1)
#plt.plot(np.arange(0, len(data) * MEAS_PERIOD, MEAS_PERIOD), data)
plt.scatter(up_crossings, [data[i] for i in up_crossings], c='red', zorder=10)
plt.scatter(down_crossings, [data[i] for i in down_crossings], c='green', zorder=10)
#for i, x in enumerate(cycles):
#    plt.axvline(x=x, color='k', label=i)
plt.xlim(0, len(data))
plt.grid()

plt.subplot(2, 1, 2)
plt.plot(cycles, [1 / (3 * p * MEAS_PERIOD) for p in periods])
plt.xlim(0, len(data))
plt.grid()

plt.show()
