from tensorflow.keras.datasets import mnist
from tensorflow import keras
import matplotlib.pyplot as plt
import numpy as np

autoEncoder = keras.models.load_model('modelV4.keras')

(x_train, y_train), (x_test, y_test) = mnist.load_data()
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

# plt.clear()
THRESHOLD = 0.6
anomalies = x_test[mse > THRESHOLD]
decoded = decoded[mse > THRESHOLD]
mse = mse[mse > THRESHOLD]

# Plot top 10 anomalies
plt.figure(figsize=(20, 4))
for i in range(10):
    ax = plt.subplot(2, 10, i + 1)
    plt.imshow(anomalies[i], cmap='gray')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
    plt.title(f'MSE: {mse[i]:.2f}')

    ax = plt.subplot(2, 10, i + 11)
    plt.imshow(decoded[i], cmap='gray')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)

plt.show()
