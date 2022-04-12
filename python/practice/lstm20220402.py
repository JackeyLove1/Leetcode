import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader

import pandas as pd
import numpy as np
from einops import rearrange, reduce, repeat
from einops.layers.torch import Rearrange, Reduce
from sklearn.preprocessing import MinMaxScaler as mms

import warnings

warnings.filterwarnings("ignore")

path = "/Users/arexiusvan/PycharmProjects/PyStudy211209/work/flights.csv"
seq_len = 11
hidden_size = 20
input_size = 1
num_directions = 1
output_size = 1
batch_size = 1
num_layers = 1
epochs = 10
lr = 0.01
device = torch.device('cuda' if torch.cuda.is_available() else "cpu")


# 数据归一化处理
def get_scaler():
    return mms(feature_range=(-1, 1))


class flightDataset(Dataset):
    def __init__(self):
        self.flight = pd.read_csv(path)
        self.flight = self.flight["passengers"].values
        scaler = get_scaler()
        self.flight = scaler.fit_transform(self.flight.reshape(-1, 1))
        self.flight = torch.FloatTensor(self.flight).reshape(-1, 12)
        self.x = self.flight[:, :-1]
        self.y = self.flight[:, -1]

    def __len__(self):
        return self.x.size()[0]

    def __getitem__(self, item):
        return self.x[item], self.y[item]


dataset = flightDataset()

dataloader = DataLoader(dataset=dataset,
                        batch_size=batch_size,
                        shuffle=False)


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.lstm = nn.LSTM(input_size=input_size, hidden_size=hidden_size)
        self.fc = nn.Linear(hidden_size * seq_len, output_size)
        self.size = (input_size, batch_size, hidden_size)
        # h, c: [input_size, batch_size, hidden_size]
        self.h, self.c = torch.zeros(size=self.size), torch.zeros(size=self.size)

    def forward(self, x):
        # x [batch_size, seq_len] -> [seq_len, batch_size, input_size]
        # x_lstm -> [seq_len, batch_size, hidden_size]
        # x_lstm -> x_fc : [batch_size, seq_len*hidden_size]
        # x_fc -> [batch_size, output_size]
        # y [output_size] -> [batch_size, output_size]
        x = x.unsqueeze(-1).repeat(1, 1, input_size)
        x = torch.einsum("b s i -> s b i", x)
        x, (self.h, self.c) = self.lstm(x, (self.h, self.c))
        self.h, self.c = self.h.data, self.c.data
        x = x.view(-1)
        x = self.fc(x)
        return x.squeeze(0)


net_s = nn.Sequential(nn.LSTM(seq_len, hidden_size, num_layers),
                      nn.Linear(seq_len, output_size))
net = Net()

optimizer = torch.optim.SGD(net.parameters(), lr)
criteria = nn.MSELoss()

from tqdm import tqdm

for epoch in range(epochs):
    total_loss = 0
    for i, (x, y) in enumerate(dataloader):
        optimizer.zero_grad()
        y_hat = net(x)
        l = criteria(y, y_hat)
        total_loss += l.item()
        l.backward()
        optimizer.step()
    print("Epoch{}, total_loss:{}".format(epoch, total_loss))
