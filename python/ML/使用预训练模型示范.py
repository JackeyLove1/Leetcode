import torchvision.models as models
import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.datasets as datasets
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import io
import sys
import os
from tqdm import tqdm

# 超参数定义
DATAPATH = "./data"
EPOCH = 100
BATCH_SIZE = 64
LR = 0.001
# 数据集加载
# 对训练集及测试集数据的不同处理组合
transform_train = transforms.Compose([
    transforms.RandomHorizontalFlip(),
    transforms.RandomGrayscale(),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
transform_test = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
# 将数据加载进来，本地已经下载好， root=os.getcwd()为自动获取与源码文件同级目录下的数据集路径
train_data = datasets.CIFAR10(root=DATAPATH, train=True, transform=transform_train, download=True)
test_data = datasets.CIFAR10(root=DATAPATH, train=False, transform=transform_test, download=True)

# 数据分批
from torch.utils.data import DataLoader

# 使用DataLoader进行数据分批，dataset代表传入的数据集，batch_size表示每个batch有多少个样本
# shuffle表示在每个epoch开始的时候，对数据进行重新排序
# 数据分批之前：torch.Size([3, 32, 32])：Tensor[[32*32][32*32][32*32]],每一个元素都是归一化之后的RGB的值；数据分批之后：torch.Size([64, 3, 32, 32])
# 数据分批之前：train_data([50000[3*[32*32]]])
# 数据分批之后：train_loader([50000/64*[64*[3*[32*32]]]])
train_loader = DataLoader(dataset=train_data, batch_size=BATCH_SIZE, shuffle=True, num_workers=2)
test_loader = DataLoader(dataset=test_data, batch_size=BATCH_SIZE, shuffle=True, num_workers=2)

# 模型加载，有多种内置模型可供选择
model = torchvision.models.resnet18(pretrained=False)

# 定义损失函数，分类问题使用交叉信息熵，回归问题使用MSE
criterion = nn.CrossEntropyLoss()
# torch.optim来做算法优化,该函数甚至可以指定每一层的学习率，这里选用Adam来做优化器，还可以选其他的优化器
optimizer = optim.Adam(model.parameters(), lr=LR)
scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=1)
# 设置GPU
device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
# 模型和输入数据都需要to device
mode = model.to(device)

# 模型训练
from torch.utils.tensorboard import SummaryWriter

# writer = SummaryWriter('cifar-10')
for epoch in range(EPOCH):
    model.train()
    total_loss = 0
    scheduler.step()
    with tqdm(total=EPOCH, desc=f'Epoch {epoch + 1}/{EPOCH}', unit='it') as pbar:
        for i, data in enumerate(train_loader):
            inputs, labels = data
            inputs, labels = inputs.to(device), labels.to(device)

            outputs = model(inputs)
            loss = criterion(outputs, labels)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
        print('epoch{} loss:{:.4f}'.format(epoch + 1, total_loss))
    correct, total = 0, 0
    # 测试函数
    model.eval()
    with torch.no_grad():
        for j, data in enumerate(test_loader):
            inputs, labels = data
            inputs, labels = inputs.to(device), labels.to(device)
            outputs = model(inputs)
            _, predicted = torch.max(outputs.data, 1)
            total = total + labels.size(0)
            correct = correct + (predicted == labels).sum().item()
        print('准确率：{:.4f}%'.format(100.0 * correct / total))

# 保存模型参数
torch.save(model, 'cifar10_densenet161.pt')
print('cifar10_densenet161.pt saved')

# 模型加载
model = torch.load('cifar10_densenet161.pt')
# 测试
# model.eval()
# model.train()

correct, total = 0, 0
for j, data in enumerate(test_loader):
    inputs, labels = data
    inputs, labels = inputs.to(device), labels.to(device)
    # 前向传播
    outputs = model(inputs)
    _, predicted = torch.max(outputs.data, 1)
    total = total + labels.size(0)
    correct = correct + (predicted == labels).sum().item()
print('准确率：{:.4f}%'.format(100.0 * correct / total))

# https://pytorch.org/vision/stable/models.html

import torchvision.models as models
resnet18 = models.resnet18(pretrained=True)
alexnet = models.alexnet(pretrained=True)
squeezenet = models.squeezenet1_0(pretrained=True)
vgg16 = models.vgg16(pretrained=True)
densenet = models.densenet161(pretrained=True)
inception = models.inception_v3(pretrained=True)
googlenet = models.googlenet(pretrained=True)
shufflenet = models.shufflenet_v2_x1_0(pretrained=True)
mobilenet_v2 = models.mobilenet_v2(pretrained=True)
mobilenet_v3_large = models.mobilenet_v3_large(pretrained=True)
mobilenet_v3_small = models.mobilenet_v3_small(pretrained=True)
resnext50_32x4d = models.resnext50_32x4d(pretrained=True)
wide_resnet50_2 = models.wide_resnet50_2(pretrained=True)
mnasnet = models.mnasnet1_0(pretrained=True)
efficientnet_b0 = models.efficientnet_b0(pretrained=True)
efficientnet_b1 = models.efficientnet_b1(pretrained=True)
efficientnet_b2 = models.efficientnet_b2(pretrained=True)
efficientnet_b3 = models.efficientnet_b3(pretrained=True)
efficientnet_b4 = models.efficientnet_b4(pretrained=True)
efficientnet_b5 = models.efficientnet_b5(pretrained=True)
efficientnet_b6 = models.efficientnet_b6(pretrained=True)
efficientnet_b7 = models.efficientnet_b7(pretrained=True)
regnet_y_400mf = models.regnet_y_400mf(pretrained=True)
regnet_y_800mf = models.regnet_y_800mf(pretrained=True)
regnet_y_1_6gf = models.regnet_y_1_6gf(pretrained=True)
regnet_y_3_2gf = models.regnet_y_3_2gf(pretrained=True)
regnet_y_8gf = models.regnet_y_8gf(pretrained=True)
regnet_y_16gf = models.regnet_y_16gf(pretrained=True)
regnet_y_32gf = models.regnet_y_32gf(pretrained=True)
regnet_x_400mf = models.regnet_x_400mf(pretrained=True)
regnet_x_800mf = models.regnet_x_800mf(pretrained=True)
regnet_x_1_6gf = models.regnet_x_1_6gf(pretrained=True)
regnet_x_3_2gf = models.regnet_x_3_2gf(pretrained=True)
regnet_x_8gf = models.regnet_x_8gf(pretrained=True)
regnet_x_16gf = models.regnet_x_16gf(pretrainedTrue)
regnet_x_32gf = models.regnet_x_32gf(pretrained=True)
vit_b_16 = models.vit_b_16(pretrained=True)
vit_b_32 = models.vit_b_32(pretrained=True)
vit_l_16 = models.vit_l_16(pretrained=True)
vit_l_32 = models.vit_l_32(pretrained=True)
convnext_tiny = models.convnext_tiny(pretrained=True)
convnext_small = models.convnext_small(pretrained=True)
convnext_base = models.convnext_base(pretrained=True)
convnext_large = models.convnext_large(pretrained=True)

import torchvision.models as models
googlenet = models.quantization.googlenet()
inception_v3 = models.quantization.inception_v3()
mobilenet_v2 = models.quantization.mobilenet_v2()
mobilenet_v3_large = models.quantization.mobilenet_v3_large()
resnet18 = models.quantization.resnet18()
resnet50 = models.quantization.resnet50()
resnext101_32x8d = models.quantization.resnext101_32x8d()
shufflenet_v2_x0_5 = models.quantization.shufflenet_v2_x0_5()
shufflenet_v2_x1_0 = models.quantization.shufflenet_v2_x1_0()
shufflenet_v2_x1_5 = models.quantization.shufflenet_v2_x1_5()
shufflenet_v2_x2_0 = models.quantization.shufflenet_v2_x2_0()

import torchvision.models as models
model = models.quantization.mobilenet_v2(pretrained=True, quantize=True)
model.eval()
# run the model with quantized inputs and weights
out = model(torch.rand(1, 3, 224, 224))

