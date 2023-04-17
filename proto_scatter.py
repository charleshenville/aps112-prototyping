import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
import math

times = [24.7, 26.3, 25, 24.9, 24.1, 25.6, 22.1, 23.4, 27.7, 21.7, 25.9, 27.1, 25.2, 26.6, 24.4]
trialNums = [i for i in range(1, len(times)+1)]
labels = [str(trial) for trial in trialNums]

maxTime = max(times)
minTime = min(times)
timeRange = maxTime-minTime

heat = []
average = 0

for time in times:
    heat.append((time-minTime)/timeRange)
    average += time

average /= len(times)

#plt.rcParams['font.family'] = 'Galvji'
plt.rcParams['font.family'] = 'Arial'
plt.rcParams['font.size'] = 11
figure, axis = plt.subplots()

axis.set_axisbelow(True)
axis.grid(True)

min_color = (63/255, 2/255, 186/255)
max_color = (255/255, 158/255, 29/255)
custom_cmap = LinearSegmentedColormap.from_list('custom_cmap', [min_color, max_color])

mainplot = axis.scatter(trialNums, times, c=heat, edgecolors='black', cmap=custom_cmap, zorder=2)

error=0.5
for i in range(len(times)):
    axis.errorbar(trialNums[i], times[i], yerr=error, fmt='none', ecolor=custom_cmap(heat[i]), capsize=2, zorder=1)
    axis.annotate(labels[i], (trialNums[i]+0.2, times[i]-0.12))

axis.set_xlim(0, len(times)+1)
axis.set_ylim(math.floor(minTime-1), math.ceil(maxTime+1))

axis.set_xlabel('Trial Number')
axis.set_ylabel('Time (seconds)')
axis.set_title('Time to Completely Navigate Phoebe\'s UI\n', weight='bold')

average_heat = (average - minTime) / timeRange
average_color = custom_cmap(average_heat)

# Add a horizontal line at the average value
axis.annotate(' Mean ', (16, average-0.12), color=average_color, weight='bold')
axis.axhline(y=average, color=average_color, linewidth=1, linestyle='--')

plt.show()
