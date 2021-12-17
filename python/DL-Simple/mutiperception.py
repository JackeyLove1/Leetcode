import torch
import torch.nn
import torch.optim
import torchvision
import torchvision.transforms as transforms
from torch import nn
from torch.nn import init

# parameters
num_inputs = 784
num_hiddens = 256
num_outputs = 10
num_examples = 100
batch_size = 256
learning_rate = 0.1
num_epochs = 10

# load dataset
mnist_train = torchvision.datasets.FashionMNIST(
    root='./FashionMNIST',
    train=True,
    transform=transforms.ToTensor()
)

mnist_test = torchvision.datasets.FashionMNIST(
    root='./FashionMNIST',
    train=False,
    transform=transforms.ToTensor()
)

print(type(mnist_train))
print(len(mnist_train), len(mnist_test))

# create dataset iterator
train_iter = torch.utils.data.DataLoader(mnist_train, batch_size=batch_size, shuffle=True)
test_iter = torch.utils.data.DataLoader(mnist_test, batch_size=batch_size, shuffle=False)


# define the network
def FlattenLayer(x):
    return x.view(x.shape[0], -1)


class LinearNet(nn.Module):
    def __init__(self):
        super(LinearNet, self).__init__()
        self.linear1 = nn.Linear(num_inputs, num_hiddens)
        self.linear2 = nn.Linear(num_hiddens, num_outputs)
        self.relu = nn.ReLU()

    def forward(self, x):
        x = FlattenLayer(x)
        x = self.linear1(x)
        x = self.relu(x)
        x = self.linear2(x)
        return x


net = LinearNet()
print(net)

# initialize the parameters
for param in net.parameters():
    init.normal_(param, mean=0, std=0.01)

# define the loss function
loss = nn.CrossEntropyLoss()

# define the optimizer
optimizer = torch.optim.SGD(net.parameters(), lr=learning_rate)


# define the evaluate function
def evaluate_accuracy(data_iter, net):
    acc_sum, n = 0.0, 0
    for X, y in data_iter:
        # functional programming
        acc_sum += (net(X).argmax(dim=1) == y).float().sum().item()
        n += y.shape[0]
    return acc_sum / n


# train the model
for epoch in range(1, num_epochs + 1):
    for X, y in train_iter:
        # X.shape [256, 1, 28, 28]
        # y.shape [256]
        output = net(X)
        net_loss = loss(output, y).sum()
        optimizer.zero_grad()
        net_loss.backward()
        optimizer.step()
    if epoch % 2 == 0:
        print("epoch %d, loss %f" % (epoch, net_loss.item()))
        test_acc = evaluate_accuracy(test_iter, net)
        print("accuracy: ", test_acc)
