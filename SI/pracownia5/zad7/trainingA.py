from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras import Input
import os

import matplotlib.pyplot as plt
import numpy as np

(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train = x_train.astype('float32') / 255
x_test = x_test.astype('float32') / 255

y_train = x_train.copy()
y_test = x_test.copy()


autoEncoder = Sequential()

autoEncoder.add(Input(shape=(784,)))
# autoEncoder.add(Dense(128, activation='relu', input_shape=(784,)))
autoEncoder.add(Dense(64, activation='relu'))
autoEncoder.add(Dense(32, activation='relu'))
autoEncoder.add(Dense(64, activation='relu'))
autoEncoder.add(Dense(128, activation='relu'))
autoEncoder.add(Dense(784, activation='relu'))
autoEncoder.compile(optimizer='adam', loss='mean_squared_error')

autoEncoder.fit(y_train.reshape(-1, 784), y_train.reshape(-1, 784), epochs=10, batch_size=256, shuffle=True, validation_data=(y_test.reshape(-1, 784), y_test.reshape(-1, 784)))

fileName = 'modelV'
i = 0
while os.path.exists(f'{fileName}{i}.keras'):
    i += 1

autoEncoder.save(f'{fileName}{i}.keras')