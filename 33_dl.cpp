from keras.datasets import fashion_mnist

(train_x,train_y),(test_x,test_y) = fashion_mnist.load_data()

from keras.models import Sequential
from keras.layers import Dense,Flatten

model = Sequential()

model.add(Flatten(input_shape=(28,28)))
model.add(Dense(128,activation = 'relu'))
model.add(Dense(10,activation = 'softmax'))

model.compile(optimizer='adam',loss='sparse_categorical_crossentropy',metrics=['accuracy'])

model.summary()



import numpy as np

model.fit(train_x.astype(np.float32),train_y.astype(np.float32),epochs=5,validation_split=0.2)

loss,acc = model.evaluate(test_x,test_y)
print(loss)
print(acc)


