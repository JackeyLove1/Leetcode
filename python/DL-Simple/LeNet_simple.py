import torch
from torch import nn, optim

import sys


class LeNet(nn.Module):
    def __init__(self):
        super(LeNet, self).__init__()
        self.conv = nn.Sequential(
            nn.Conv2d(1, 6, 5),
            nn.Sigmoid(),
            nn.MaxPool2d(2, 3),
            nn.Conv2d(6, 16, 5),
            nn.Sigmoid(),
            nn.MaxPool2d(2, 2)
        )

        self.fc = nn.Sequential(
            nn.Linear(16 * 4 * 4, 120),
            nn.Sigmoid(),
            nn.Linear(120, 64),
            nn.Sigmoid(),
            nn.Linear(64, 10)
        )

    def forward(self, x):
        feature = self.conv(x)
        output = self.fc(feature.view(feature.shape[0], -1))
        return output

net = LeNet()
print(net)