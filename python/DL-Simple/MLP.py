import torch
from torch import nn
from torch.nn import init


class CenterLayer(nn.Module):
    def __init__(self, **kwargs):
        super(CenterLayer, self).__init__(**kwargs)

    def forward(self, x):
        return x - x.mean()


layer = CenterLayer()
print(layer(torch.tensor([1, 2, 3, 4, 5], dtype=torch.float)))

net = nn.Sequential(
    nn.Linear(8, 24),
    CenterLayer()
)

x = torch.rand(4, 8)
y = net(x)
print(y)


class MLP(nn.Module):
    def __init__(self):
        super(MLP, self).__init__()
        self.hidden = nn.Linear(3, 2)
        self.act = nn.ReLU()
        self.output = nn.Linear(2, 1)

    def forward(self, x):
        x = self.act(self.hidden(x))
        return self.output(x)


net = MLP()
print(net.state_dict())
