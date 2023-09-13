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

def find_crossings(ulim, llim):

    up_crossings, down_crossings, cycles = [], [], []

    up_cnt, down_cnt = 0, 0

    is_up = data[0] >= ulim
    for i, s in enumerate(data):
        if i == 0: continue  # first already checked

        if is_up:
            if s <= llim:
                down_cnt += 1
                if down_cnt >= 3:
                    is_up = False
                    down_cnt = 0
                    down_crossings.append(i)
        else:
            if s >= ulim:
                up_cnt += 1
                if up_cnt >= 3:
                    is_up = True
                    up_cnt = 0
                    up_crossings.append(i)
                    cycles.append(i)
        
    return up_crossings, down_crossings, cycles


ULIM, LLIM = 4050, 3800
up_crossings, down_crossings, cycles = find_crossings(ULIM, LLIM)

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

plt.axhline(y=ULIM, color='k', label=i)
plt.axhline(y=LLIM, color='k', label=i)

plt.xlim(0, len(data))
plt.grid()

plt.subplot(2, 1, 2)
plt.plot(cycles, [1 / (3 * p * MEAS_PERIOD) for p in periods])
plt.xlim(0, len(data))
plt.grid()

plt.show()
