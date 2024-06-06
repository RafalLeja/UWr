from tensorflow.keras.datasets import mnist
from tensorflow import keras
import matplotlib.pyplot as plt
import numpy as np
import cv2

autoEncoder = keras.models.load_model('modelBV0.tf')

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

print(x_test.shape)

decoded = autoEncoder.predict(x_test).reshape(-1, 28, 28) * 255

print(decoded.shape)

x_test = x_test * 255

# decoded = np.clip(decoded * 1.2, 0, 255)

mse = np.mean((x_test - decoded) ** 2, axis=(1, 2))
mse = mse / np.max(mse)


# Plot MSE
plt.figure(figsize=(10, 5))
plt.plot(mse)
plt.xlabel('Sample Index')
plt.ylabel('MSE')
plt.title('Mean Squared Error (MSE)')
plt.show()

# # plt.clear()
# THRESHOLD = 0.6
# anomalies = x_test[mse > THRESHOLD]
# decoded = decoded[mse > THRESHOLD]
# mse = mse[mse > THRESHOLD]


sorted_indices = np.argsort(mse)
sorted_indices = sorted_indices[::-1]
x_test_sorted = x_test[sorted_indices]
decoded_sorted = decoded[sorted_indices]
mse = mse[sorted_indices]

# Plot top 10 anomalies
plt.figure(figsize=(20, 4))
for i in range(10):
    ax = plt.subplot(2, 10, i + 1)
    plt.imshow(x_test_sorted[i], cmap='gray')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
    plt.title(f'MSE: {mse[i]:.2f}')

    ax = plt.subplot(2, 10, i + 11)
    plt.imshow(decoded_sorted[i], cmap='gray')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)

plt.show()
