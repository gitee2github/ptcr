import pygal
import string
import os
import sys
from sys import argv

if len(sys.argv) < 2:
    print ('usage python3 draw.py + file.txt')
    sys.exit(1)

file = open(argv[1])
dataMat = []
for line in file.readlines():
    line = line.rstrip("\n").rstrip().lstrip()
    dataMat.append(line)

radar_chart = pygal.Radar()
radar_chart.title=dataMat[0]
radar_chart.x_labels=dataMat[1].split(" ")

for item in dataMat[2:]:
    key = item.split(" ", 1)[0]
    value = item.split(" ", 1)[1].split(" ")
    array = list(map(int, value))
    radar_chart.add(key, list(map(int, value)))

radar_chart.render_to_file(argv[1].split(".", 1)[0] +'.svg')
