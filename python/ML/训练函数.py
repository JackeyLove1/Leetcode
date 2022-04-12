from tqdm import tqdm


def train_epoch(DataLoader, model, criterion, optimizer):
    if torch.cuda.is_available():
        model.cuda()

        # 指定为train模式
        model.train()
    total_loss = 0
    for i, (X, y) in tqdm(enumerate(DataLoader)):
        if torch.cuda.is_available():
            X = X.cuda()
            y = y.cuda()
        # 计算网络输出
        output = model(X)

        # 计算损失
        loss = criterion(output, y)
        total_loss = loss.sum()

        # 计算梯度和做反向传播
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
    print("total_loss: ", total_loss)


%matplotlib inline
import matplotlib.pyplot as plt
from torchvision import datasets, models, transforms
import torch.optim as optim
import torch.nn as nn
from torchvision.transforms import *
from torch.utils.data import DataLoader
import torch
import numpy as np
from collections import namedtuple
import pandas as pd

def train(dataloader, model, criterion, optimizer, scheduler, num_epochs=20):
    results = []
    for epoch in range(num_epochs):
        optimizer.step()
        scheduler.step()
        model.train()

        running_loss = 0.0
        running_corrects = 0

        n = 0
        for inputs, labels in dataloader:
            inputs = inputs.to(device)
            labels = labels.to(device)

            optimizer.zero_grad()

            with torch.set_grad_enabled(True):
                outputs = model(inputs)
                loss = criterion(outputs, labels)
                _, preds = torch.max(outputs, 1)

                loss.backward()
                optimizer.step()

            running_loss += loss.item() * inputs.size(0)
            running_corrects += torch.sum(preds == labels.data)
            n += len(labels)

        epoch_loss = running_loss / float(n)
        epoch_acc = running_corrects.double() / float(n)

        print(f'epoch {epoch}/{num_epochs} : {epoch_loss:.5f}, {epoch_acc:.5f}')
        results.append(EpochProgress(epoch, epoch_loss, epoch_acc.item()))
    return pd.DataFrame(results)

def plot_results(df, figsize=(10, 5)):
    fig, ax1 = plt.subplots(figsize=figsize)

    ax1.set_xlabel('epoch')
    ax1.set_ylabel('loss', color='tab:red')
    ax1.plot(df['epoch'], df['loss'], color='tab:red')

    ax2 = ax1.twinx()
    ax2.set_ylabel('accuracy', color='tab:blue')
    ax2.plot(df['epoch'], df['accuracy'], color='tab:blue')

    fig.tight_layout()

np.random.seed(37)
torch.manual_seed(37)
torch.backends.cudnn.deterministic = True
torch.backends.cudnn.benchmark = False

num_classes = 3
pretrained = True
device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')

EpochProgress = namedtuple('EpochProgress', 'epoch, loss, accuracy')

transform = transforms.Compose([Resize(224), ToTensor()])
image_folder = datasets.ImageFolder('./shapes/train', transform=transform)
dataloader = DataLoader(image_folder, batch_size=4, shuffle=True, num_workers=4)

model = models.resnet18(pretrained=pretrained)
model.fc = nn.Linear(model.fc.in_features, num_classes)
model = model.to(device)

params_to_update = model.parameters()

criterion = nn.CrossEntropyLoss()
optimizer = optim.Rprop(params_to_update, lr=0.01)

scheduler = optim.lr_scheduler.LambdaLR(optimizer, lr_lambda=[lambda epoch: 0.95 ** epoch])

results = train(dataloader, model, criterion, optimizer, scheduler)
# plot_results(results)