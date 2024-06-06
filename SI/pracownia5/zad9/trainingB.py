from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import Conv2D
from tensorflow.keras.layers import Conv2DTranspose
from tensorflow.keras import Input, layers
import cv2
import tensorflow.keras as keras
import tensorflow
import os

import matplotlib.pyplot as plt
import numpy as np

(x_train, y_train), (x_test, y_test) = mnist.load_data()

pictures = []
pictures.append(cv2.imread('./Obrazki/buzka.pgm', cv2.IMREAD_GRAYSCALE))
pictures.append(cv2.imread('./Obrazki/domek.pgm', cv2.IMREAD_GRAYSCALE))
pictures.append(cv2.imread('./Obrazki/grzybek.pgm', cv2.IMREAD_GRAYSCALE))
pictures.append(cv2.imread('./Obrazki/kolka.pgm', cv2.IMREAD_GRAYSCALE))
pictures.append(cv2.imread('./Obrazki/kreska.pgm', cv2.IMREAD_GRAYSCALE))
pictures.append(cv2.imread('./Obrazki/r.pgm', cv2.IMREAD_GRAYSCALE))
pictures.append(cv2.imread('./Obrazki/samolocik.pgm', cv2.IMREAD_GRAYSCALE))

for i in range(len(pictures)):
    pictures[i] = cv2.resize(pictures[i], (28, 28))

x_train = np.concatenate((x_train, np.array(pictures)))
x_test = np.concatenate((x_test, np.array(pictures)))

x_train = x_train.astype('float32') / 255
x_test = x_test.astype('float32') / 255



y_train = x_train.copy()
y_test = x_test.copy()

model = Sequential()
model.add(Input(shape=(28, 28, 1)))
model.add(Conv2D(16, (3, 3), activation='relu', padding='same', strides=2))
model.add(Conv2D(8, (3, 3), activation='relu', padding='same', strides=2))
model.add(Conv2DTranspose(8, kernel_size=3, strides=2, activation='relu', padding='same'))
model.add(Conv2DTranspose(16, kernel_size=3, strides=2, activation='relu', padding='same'))
model.add(Conv2D(1, kernel_size=(3, 3), activation='sigmoid', padding='same'))

model.compile(optimizer='adam', loss='mse')

model.fit(y_train, y_train, epochs=10, batch_size=256, shuffle=True, validation_data=(y_test, y_test))
# model.fit(y_train.reshape(-1, 784), y_train.reshape(-1, 784), epochs=50, batch_size=256, shuffle=True, validation_data=(y_test.reshape(-1, 784), y_test.reshape(-1, 784)))

fileName = 'modelBV'
i = 0
while os.path.exists(f'{fileName}{i}.tf'):
    i += 1

model.save(f'{fileName}{i}.tf')