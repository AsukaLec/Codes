import math
radius = float(input())
volume = 4 * math.pi * radius ** 3 / 3
area = 4 * math.pi * radius ** 2 
print("{:.6f}".format(volume))
print("{:.6f}".format(area))