import torchvision
from torch.utils.data import DataLoader
import torch
from torch import nn
import time
import torch.nn.functional as F

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

# 准备数据集
train_data = torchvision.datasets.CIFAR10(root="./data", train=True,
                                          transform=torchvision.transforms.ToTensor(),
                                          download=True)

test_data = torchvision.datasets.CIFAR10(root="./data", train=False,
                                         transform=torchvision.transforms.ToTensor(),
                                         download=True)

# 查看数据集的长度
train_data_size = len(train_data)
test_data_size = len(test_data)

# 查看训练集的长度
print("训练数据集的长度为{}".format(train_data_size))
print('**' * 20)
print("测试数据集的长度为{}".format(test_data_size))

# 加载数据集
train_dataloader = DataLoader(train_data, batch_size=64)
test_dataloader = DataLoader(test_data, batch_size=64)


class MyNet(nn.Module):
    def __init__(self):
        super(MyNet, self).__init__()
        self.model = nn.Sequential(nn.Conv2d(3, 32, 5, 1, 2),
                                   nn.MaxPool2d(2),
                                   nn.Conv2d(32, 32, 5, 1, 2),
                                   nn.MaxPool2d(2),
                                   nn.Conv2d(32, 64, 5, 1, 2),
                                   nn.MaxPool2d(2),
                                   nn.Flatten(),
                                   nn.Linear(64 * 4 * 4, 64),
                                   nn.Dropout(0.3),
                                   nn.Linear(64, 10))

    def forward(self, x):
        x = self.model(x)
        return x


class ResidualBlock(nn.Module):
    def __init__(self, inchannel, outchannel, stride=1):
        super(ResidualBlock, self).__init__()

        # 这里的即为两个3*3 conv
        self.left = nn.Sequential(
            nn.Conv2d(inchannel, outchannel, kernel_size=3, stride=stride, padding=1, bias=False),
            # bias为偏置，False表示不添加偏置
            nn.BatchNorm2d(outchannel),
            nn.ReLU(),
            nn.Conv2d(outchannel, outchannel, kernel_size=3, stride=1, padding=1, bias=False),
            nn.BatchNorm2d(outchannel)
        )
        self.shortcut = nn.Sequential()  # shortcut connections
        if stride != 1 or inchannel != outchannel:  # 判断入通道和出通道是否一样，不一样的话进行卷积操作
            self.shortcut = nn.Sequential(
                nn.Conv2d(inchannel, outchannel, kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(outchannel)
            )
        self.relu = nn.ReLU()

    def forward(self, x):
        out = self.left(x)
        out += self.shortcut(x)
        out = self.relu(out)
        return out


class ResNet(nn.Module):
    def __init__(self, ResidualBlock=ResidualBlock):
        super(ResNet, self).__init__()

        # 图片处理，也就是白色方框内的3*3 conv
        self.conv1 = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=3, stride=1, padding=1, bias=False),
            nn.BatchNorm2d(64),
            nn.ReLU(),
        )

        # 中间的残差网络部分，与图上的结构一一对应
        self.layer1 = self.make_layer(ResidualBlock, 64, 64, 2, stride=1)
        self.layer2 = self.make_layer(ResidualBlock, 64, 128, 2, stride=2)
        self.layer3 = self.make_layer(ResidualBlock, 128, 256, 2, stride=2)
        self.layer4 = self.make_layer(ResidualBlock, 256, 512, 2, stride=2)
        self.avg_pool2d = nn.AvgPool2d(4)
        self.fc = nn.Linear(512, 10)

    # 相当于看处理几次，18的是每个处理两次
    def make_layer(self, block, inchannel, outchannel, num_blocks, stride):
        layers = []
        for i in range(1, num_blocks):
            layers.append(block(inchannel, outchannel, stride))
        return nn.Sequential(*layers)

    def forward(self, x):
        out = self.conv1(x)
        out = self.layer1(out)
        out = self.layer2(out)
        out = self.layer3(out)
        out = self.layer4(out)
        out = self.avg_pool2d(out)
        out = out.view(out.size(0), -1)
        out = self.fc(out)
        return out


# 调用 test网络
# model = ResNet().to(device)
model = MyNet().to(device)
model.to(device)

# 损失函数
loss_fn = nn.CrossEntropyLoss()
loss_fn.to(device)

# 优化器
learning_rate = 0.0001
# optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

# 设置训练网络的参数
# 记录训练的次数
total_train_step = 0
# 训练的轮次
epoch = 1
start_time = time.time()
for i in range(epoch):
    print("-----Epoch{} starting ----".format(i + 1))

    # 这里是直接弄了一个训练步骤，不像之前的编程，单独弄个train的函数
    train_start_time = time.time()
    for data in train_dataloader:
        imgs, targets = data
        imgs = imgs.to(device)
        targets = targets.to(device)

        outputs = model(imgs)
        loss = loss_fn(outputs, targets)

        # 优化模型
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        total_train_step = total_train_step + 1
        if total_train_step % 100 == 0:
            print("test_step: {}，loss:{}".format(total_train_step, loss.item()))
    train_cost_time = time.time() - start_time
    print("Epoch{} cost time: {} ".format(i, train_cost_time))
    # 测试步骤开始
    total_test_loss = 0
    correct = 0
    total = 0
    with torch.no_grad():
        for data in test_dataloader:
            imgs, targets = data
            imgs = imgs.to(device)
            targets = targets.to(device)
            outputs = model(imgs)
            # print("output size: ", outputs.size())
            # print("targets size: ", targets.size())
            preds = (torch.argmax(outputs, dim=-1) == targets).sum()
            correct += preds
            total += targets.size()[0]
            total_test_loss = total_test_loss + loss.item()
    print("test_accuracy:{}".format(100 * correct.item() / total))
    print("test_total_loss: {}".format(total_test_loss))
    # exit()

end_time = time.time()
print("Cost time: {}s ".format(end_time - start_time))

