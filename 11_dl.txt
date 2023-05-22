import numpy as np
from keras.datasets import boston_housing
from keras.models import Sequential
from keras.layers import Dense

# Load the Boston housing price dataset
(train_data, train_targets), (test_data, test_targets) = boston_housing.load_data()

# Preprocess the data
mean = train_data.mean(axis=0)
std = train_data.std(axis=0)
train_data = (train_data - mean) / std
test_data = (test_data - mean) / std

# Build the model
model = Sequential()
model.add(Dense(1, input_shape=(train_data.shape[1],)))

# Compile the model
model.compile(optimizer='rmsprop', loss='mse', metrics=['mae'])

# Train the model
model.fit(train_data, train_targets, epochs=100, batch_size=1, verbose=1)

# Evaluate the model
test_loss, test_mae = model.evaluate(test_data, test_targets)
print(f"Test loss: {test_loss}")
print(f"Test MAE: {test_mae}")
