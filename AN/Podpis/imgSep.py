import cv2 as cv
import numpy as np

# gx = np.array([[-1, 0, 1], 
#                 [-2, 0, 2], 
#                 [-1, 0, 1]])

# gy = np.array([[-1, -2, -1], 
#                 [0, 0, 0], 
#                 [1, 2, 1]])

img = cv.imread('source2.png', cv.IMREAD_GRAYSCALE)

thresh = 215
im_dn = cv.fastNlMeansDenoising(img, None, 10, 7, 21)
im_bw = cv.threshold(im_dn, thresh, 255, cv.THRESH_BINARY)[1]
# kernel = np.array([[1,1,1], [1,0,1], [1,1,1]])
# im_sh = cv.filter2D(im_bw, -1, kernel)
im_blur = cv.blur(im_bw, (5,5))
im_bw2 = cv.threshold(im_blur, 140, 255, cv.THRESH_BINARY)[1]


# filtered = cv.Canny(im_bw, 150, 50)
# thinned = cv.ximgproc.thinning(img, thinningType=cv.ximgproc.THINNING_GUOHALL)
# filtered = cv.Sobel(src=img, ddepth=-1, dx=gx, dy=gy)
# filtered = cv.filter2D(src=img, ddepth=-1, kernel=kernel)
# cv.imshow('im_bw', im_bw)
# cv.imshow('filtered', filtered)
# cv.imshow('thinned', thinned)

cv.waitKey(0)
cv.destroyAllWindows()

cv.imwrite('filtered.png', im_bw2)