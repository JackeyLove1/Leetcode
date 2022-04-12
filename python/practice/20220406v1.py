import torch
import torch.nn as nn
from torch.autograd import Variable
import numpy as np

# Hyper-parameters
input_size = 1
output_size = 1
hidden_size = 10
epochs = 60
lr = 0.001

# Toy dataset
x_train = np.array([[3.3], [4.4], [5.5], [6.71], [6.93], [4.168],
                    [9.779], [6.182], [7.59], [2.167], [7.042],
                    [10.791], [5.313], [7.997], [3.1]], dtype=np.float32)

y_train = np.array([[1.7], [2.76], [2.09], [3.19], [1.694], [1.573],
                    [3.366], [2.596], [2.53], [1.221], [2.827],
                    [3.465], [1.65], [2.904], [1.3]], dtype=np.float32)

model = nn.Sequential(
    nn.Linear(input_size, hidden_size),
    nn.Linear(hidden_size, output_size),
)

optimizer = torch.optim.SGD(model.parameters(), lr=lr)
criterion = nn.MSELoss()

for epoch in range(epochs):
    X = Variable(torch.FloatTensor(x_train))
    y = Variable(torch.FloatTensor(y_train))
    optimizer.zero_grad()
    outputs = model(X)
    loss = criterion(y, outputs)
    if epoch % 5 == 0:
        print("loss: {}".format(loss.item()))
    loss.backward()
    optimizer.step()
