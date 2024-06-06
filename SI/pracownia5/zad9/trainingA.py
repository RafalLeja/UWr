from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import Conv2D
from tensorflow.keras.layers import Conv2DTranspose
from tensorflow.keras import Input, layers
import tensorflow.keras as keras
import tensorflow
import os

import matplotlib.pyplot as plt
import numpy as np

(x_train, y_train), (x_test, y_test) = mnist.load_data()
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

fileName = 'modelV'
i = 0
while os.path.exists(f'{fileName}{i}.keras'):
    i += 1

model.save(f'{fileName}{i}.keras')