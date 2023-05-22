from tensorflow.keras.datasets import imdb
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.preprocessing import sequence

# Load the IMDB dataset
(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words=10000)

# Preprocess the data
max_words = 10000
train_data = sequence.pad_sequences(train_data, maxlen=max_words)
test_data = sequence.pad_sequences(test_data, maxlen=max_words)

# Build the model
model = Sequential()
model.add(Dense(16,input_shape=(10000,), activation='relu')  )
model.add(Dense(16, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

# Compile the model
model.compile(optimizer='adam', loss='mse', metrics=['accuracy'])

model.summary()

# Train the model
model.fit(train_data, train_labels, epochs=20, batch_size=32, verbose=1,validation_split=0.2)
w
# Evaluate the model
loss, accuracy = model.evaluate(test_data, test_labels)
print(f"Test loss: {loss}")
print(f"Test accuracy: {accuracy}")
