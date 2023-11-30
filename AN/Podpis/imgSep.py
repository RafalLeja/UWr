import cv2 as cv
import numpy as np

# gx = np.array([[-1, 0, 1], 
#                 [-2, 0, 2], 
#                 [-1, 0, 1]])

# gy = np.array([[-1, -2, -1], 
#                 [0, 0, 0], 
#                 [1, 2, 1]])

img = cv.imread('source.png', cv.IMREAD_GRAYSCALE)

thresh = 235
im_bw = cv.threshold(img, thresh, 255, cv.THRESH_BINARY)[1]

filtered = cv.Canny(im_bw, 150, 50)
thinned = cv.ximgproc.thinning(im_bw)
# filtered = cv.Sobel(src=img, ddepth=-1, dx=gx, dy=gy)
# filtered = cv.filter2D(src=img, ddepth=-1, kernel=kernel)
cv.imwrite('filtered.png', thinned)