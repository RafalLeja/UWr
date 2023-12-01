# Rafał Leja 340879
# lista 10 zadanie 4
# 01-12-2023

from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

def happier(image):
  img = np.copy(image)
  for x in range(len(img)):
    for y in range(len(img[x])):
      if grayness(img[x][y]):
        img[x][y] = further(img[x][y])
  return img

def sadder(image):
  img = np.copy(image)
  for x in range(len(img)):
    for y in range(len(img[x])):
      if grayness(img[x][y]):
        img[x][y] = closer(img[x][y])
  return img

def grayness(px):
  max = np.argmax(px)
  min = np.argmin(px)
  if px[max] == 0:
    return True
  diff = px[min] / px[max]
  if diff > 0.7:
    return True
  return False

def closer(px):
  coeff = 1.5
  max_i = np.argmax(px)
  min_i = np.argmin(px)
  mid_i = (3 - max_i - min_i) % 3
  px[max_i] = max(min(px[max_i] - (px[max_i] - px[mid_i] + 5)*coeff, 255), 0)
  px[min_i] = max(min(px[min_i] + (px[mid_i] - px[min_i] + 5)*coeff, 255), 0)
  return px

def further(px):
  coeff = 1.5
  max_i = np.argmax(px)
  min_i = np.argmin(px)
  mid_i = (3 - max_i - min_i) % 3
  px[max_i] = max(min(px[max_i] + (px[max_i] - px[mid_i] + 5)*coeff, 255), 0)
  px[min_i] = max(min(px[min_i] - (px[mid_i] - px[min_i] + 5)*coeff, 255), 0)
  return px


def main():
  img = np.array(Image.open('source.jpg'))
  im_h = happier(img)
  im_s = sadder(img)

  fig, ax = plt.subplots()
  
  ims=[]
  for f in range(100):
    add_img = (im_s * (1 - f/100)).astype(int) + (im_h * (f/100)).astype(int)
    ims.append([ax.imshow(add_img)])

  ani = animation.ArtistAnimation(fig, ims, interval=20, blit=True, repeat=True)

  ax.set(xticks=[], yticks=[])
  
  ani.save("animacja.mp4")

  plt.show()

main()