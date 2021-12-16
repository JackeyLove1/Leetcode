import torch
import torch.nn as nn
import torch.nn.functional as F


class Net(nn.Module):

    def __init__(self):
        super(Net, self).__init__()
        # 1 input image channel, 6 output channels, 5x5 square convolution
        # kernel
        self.conv1 = nn.Conv2d(1, 6, 5)
        self.conv2 = nn.Conv2d(6, 16, 5)
        # an affine operation: y = Wx + b
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        # Max pooling over a (2, 2) window
        x = F.max_pool2d(F.relu(self.conv1(x)), (2, 2))
        print(x.shape)
        # If the size is a square you can only specify a single number
        x = F.max_pool2d(F.relu(self.conv2(x)), 2)
        print(x.shape)
        x = x.view(-1, self.num_flat_features(x))
        print(x.shape)
        x = F.relu(self.fc1(x))
        print(x.shape)
        x = F.relu(self.fc2(x))
        print(x.shape)
        x = self.fc3(x)
        print(x.shape)
        return x

    def num_flat_features(self, x):
        size = x.size()[1:]  # all dimensions except the batch dimension
        num_features = 1
        for s in size:
            num_features *= s
        return num_features


# 查看网络
net = Net()
print(net)

# 查看输出
x = torch.randn(1, 1, 32, 32)
y = net(x)
print(y)

# 把所有参数梯度缓存器置零，用随机的梯度来反向传播
net.zero_grad()
y.backward(torch.randn(1, 10))
print(y)

'''
1.计算损失值
2.更新网络中的权重

损失函数
一个损失函数需要一对输入：
模型输出和目标，然后计算一个值来评估输出距离目标有多远。
有一些不同的损失函数在 nn 包中。一个简单的损失函数就是 nn.MSELoss ，
这计算了均方误差。
'''

y = net(x)
target = torch.randn(10)  # a dummy target, for example
target = target.view(1, -1)  # make it the same shape as output
criterion = nn.MSELoss()

loss = criterion(y, target)
print(loss)

# 反向传播
# 现在我们调用 loss.backward() ，然后看一下 con1 的偏置项在反向传播之前和之后的变化。
net.zero_grad()     # zeroes the gradient buffers of all parameters

print('conv1.bias.grad before backward')
print(net.conv1.bias.grad)

loss.backward()

print('conv1.bias.grad after backward')
print(net.conv1.bias.grad)

# 更新神经网络参数：
# 最简单的更新规则就是随机梯度下降。
# weight = weight - learning_rate * gradient
learning_rate = 0.01
for f in net.parameters():
    f.data.sub_(f.grad.data * learning_rate)

#尽管如此，如果你是用神经网络，你想使用不同的更新规则，
# 类似于 SGD, Nesterov-SGD, Adam, RMSProp, 等。
# 为了让这可行，我们建立了一个小包：torch.optim 实现了所有的方法。
# 使用它非常的简单。

import torch.optim as optim
# create your optimizer
optimizer = optim.SGD(net.parameters(), lr=0.01)


# in your training loop:
optimizer.zero_grad()   # zero the gradient buffers
output = net(input)
loss = criterion(output, target)
loss.backward()
optimizer.step()    # Does the update