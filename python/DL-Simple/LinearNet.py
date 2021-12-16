import torch
import numpy as np

# 定义参数
lr = 0.003  # learning rate
num_inputs = 2
num_epochs = 10

# 创建数据集
num_examples = 1000
true_w = [2, -3.4]
true_b = 4.2
features = torch.tensor(np.random.normal(0, 1, (num_examples, num_inputs)), dtype=torch.float)
labels = true_w[0] * features[:, 0] + true_w[1] * features[:, 1] + true_b
labels += torch.tensor(np.random.normal(0, 0.01, size=labels.size()), dtype=torch.float)

import torch.utils.data as Data

batch_size = 10
# 将训练数据的特征和标签组合
dataset = Data.TensorDataset(features, labels)
# 随机读取小批量
data_iter = Data.DataLoader(dataset, batch_size, shuffle=True)

import torch.nn as nn
import torch.nn.functional as F


class LinearNet(nn.Module):
    def __init__(self, n_features):
        super(LinearNet, self).__init__()
        self.linear = nn.Linear(n_features, 1)

    def forward(self, x):
        y = self.linear(x)
        return y


net = LinearNet(num_inputs)
print(net)
# 初始化网络参数
'''
from torch.nn import init
init.normal_(net[0].weight, mean=0, std=0.01)
init.constant_(net[0].bias, val=0)  # 也可以直接修改bias的data: net[0].bias.data.fill_(0)
'''

# 定义损失函数
loss = nn.MSELoss()

# 定义优化器
import torch.optim as optim

optimizer = optim.SGD(net.parameters(), lr=lr)

for epoch in range(1, num_epochs + 1):
    for X, y in data_iter:
        output = net(X)
        net_loss = loss(output, y.view(-1, 1))
        optimizer.zero_grad()
        net_loss.backward()
        optimizer.step()
    print("epoch %d, loss %f" %(epoch, net_loss.item()))

