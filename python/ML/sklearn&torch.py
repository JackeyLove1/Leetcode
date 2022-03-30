import numpy as np
import torch
from torch.utils import data
from d2l import torch as d2l
import torch.nn as nn
from tqdm import tqdm
from sklearn.preprocessing import StandardScaler  # 数据标准化
import warnings

warnings.filterwarnings("ignore")

# 初始数据集，设置初始参数
from sklearn.datasets import load_boston

X, y = load_boston(return_X_y=True)
# 数据预处理
ss = StandardScaler(copy=True, with_mean=True, with_std=True)
Xs = ss.fit_transform(X)

lr = 0.001
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

batch_size = 10
num_epochs = 150
features, labels = torch.tensor(Xs, dtype=torch.float), torch.tensor(y, dtype=torch.float)


# 将tensor转换为torch迭代器
def load_array(data_arrays, batch_size, is_train=True):  # @save
    """构造一个PyTorch数据迭代器"""
    dataset = data.TensorDataset(*data_arrays)
    return data.DataLoader(dataset, batch_size, shuffle=is_train)


data_iter = load_array((features, labels), batch_size)

# 定制神经网络模型
hidden1 = 30
hidden2 = 10
net = nn.Sequential(nn.Linear(features.size()[1], hidden1),
                    nn.ReLU(),
                    nn.Linear(hidden1, hidden2),
                    nn.ReLU(),
                    nn.Linear(hidden2, 1))


# 初始还权重参数
def weight_init(m):
    classname = m.__class__.__name__
    if classname.find('Conv2d') != -1:
        torch.nn.init.normal_(m.weight.data)
        torch.nn.init.constant_(m.bias.data, 0.0)
    elif classname.find('Linear') != -1:
        torch.nn.init.normal_(m.weight)
        torch.nn.init.constant_(m.bias, 0.0)
    elif classname.find('BatchNorm2d') != -1:
        torch.nn.init.normal_(m.weight.data, 1.0, 0.02)
        torch.nn.init.constant_(m.bias.data, 0.0)


net.apply(weight_init)
net = net.to(device)

# 损失函数
loss = nn.MSELoss()

trainer = torch.optim.SGD(net.parameters(), lr=lr)


# 训练器
def train(net, loss, trainer, num_epochs):
    net.train()
    for epoch in range(num_epochs):
        for X, y in data_iter:
            X, y = X.to(device), y.to(device)
            output = net(X).flatten()  # y为一维向量，故X需要展平
            l = loss(output, y)
            trainer.zero_grad()
            l.backward()
            trainer.step()
        train_loss = loss(net(features).flatten(), labels)
        print(f'epoch {epoch + 1}, loss {train_loss:f}')


def train2(net, loss, trainer, num_epochs):
    net.train()
    for epoch in range(num_epochs):
        for X, y in data_iter:
            X, y = X.to(device), y.to(device)
            # output = net(X).flatten()  # y为一维向量，故X需要展平
            output = net(X)
            y = y.reshape(y.size()[0], -1)
            y.requires_grad_()
            l = loss(output, y)
            trainer.zero_grad()
            l.backward()
            trainer.step()
        train_loss = loss(net(features).flatten(), labels)
        print(f'epoch {epoch + 1}, loss {train_loss:f}')


# 函数评估

if __name__ == "__main__":
    train2(net, loss, trainer, num_epochs)
