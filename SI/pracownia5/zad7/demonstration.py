from tensorflow.keras.datasets import mnist
from tensorflow import keras
import matplotlib.pyplot as plt
import numpy as np

autoEncoder = keras.models.load_model('modelV0.keras')

(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train = x_train.astype('float32') / 255
x_test = x_test.astype('float32') / 255

randomized = x_test[np.random.choice(x_test.shape[0], 10, replace=False)]

decoded = autoEncoder.predict(randomized.reshape(-1, 784)).reshape(-1, 28, 28) * 255

randomized = randomized.reshape(-1, 28, 28) * 255

plt.figure(figsize=(20, 4))
for i in range(10):
    ax = plt.subplot(2, 10, i + 1)
    plt.imshow(randomized[i], cmap='gray')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)

    ax = plt.subplot(2, 10, i + 11)
    plt.imshow(decoded[i], cmap='gray')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)


