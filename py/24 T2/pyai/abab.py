import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

sf24 = Image.open('./py/pyai/sf24.jpg')
plt.subplot(131)
plt.imshow(sf24)


print(np.shape(sf24))

a = np.array(sf24)

b =a[0::100, 0::100,:]

plt.subplot(132)
plt.imshow(b)


print(np.shape(b))


gray_image = np.array([
    [[255, 0, 0], [0, 255, 0], [0, 0, 255]],
    [[255, 255, 0], [0, 255, 255], [255, 0, 255]],
    [[128, 128, 128], [255, 255, 255], [0, 0, 0]]
], dtype=np.uint8)
print(gray_image.shape)  


plt.subplot(133)
plt.imshow(gray_image)


plt.show()

# array = np.linspace(0, 1, 5, dtype = int )
# print (array)

# x = np.random.randint(10, size = (3, 4, 5))
# print (x)

# x = np.linspace(-10, 10, 1000)
# y = x ** 2

# plt.plot(x, y)
# plt.show()

# grid = np.array([[1, 2, 3],
#                  [4, 5, 6]])
# grid0 = np.concatenate([grid,grid], axis = 0)
# grid1 = np.concatenate([grid,grid], axis = 1)
# print (grid1)
# print (grid0)

# x = np.random.randint(10, size = (3, 4))
# x = np.array([[3, 3, 4, 2],
#  [2, 11, 2, 2],
#  [3, 1, 5, 2]])
# print (x)

# print(x.min())
# print(x.argmin())

# a = np.array([5, 5, 5])
# a = a + 5
# print(a)

