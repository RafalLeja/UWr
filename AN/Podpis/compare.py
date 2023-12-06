import cv2
import numpy as np

# read the image
image_bgr = cv2.imread('output.png')
original = cv2.imread("source.png")
# get the image dimensions (height, width and channels)
h, w, c = image_bgr.shape
# append Alpha channel -- required for BGRA (Blue, Green, Red, Alpha)
image_bgra = np.concatenate([image_bgr, np.full((h, w, 1), 255, dtype=np.uint8)], axis=-1)
original_a = np.concatenate([original, np.full((h, w, 1), 255, dtype=np.uint8)], axis=-1)
# create a mask where white pixels ([255, 255, 255]) are True
white = np.all(image_bgr == [255, 255, 255], axis=-1)
# change the values of Alpha to 0 for all the white pixels
image_bgra[white, -1] = 0
# save the image

# normalize alpha channels from 0-255 to 0-1
alpha_background = original_a[:,:,3] / 255.0
alpha_foreground = image_bgra[:,:,3] / 255.0

# set adjusted colors
for color in range(0, 3):
    original[:,:,color] = alpha_foreground * image_bgra[:,:,color] + \
        alpha_background * original_a[:,:,color] * (1 - alpha_foreground)

# set adjusted alpha and denormalize back to 0-255
original_a[:,:,3] = (1 - (1 - alpha_foreground) * (1 - alpha_background)) * 255

cv2.imwrite('combined.png', original)