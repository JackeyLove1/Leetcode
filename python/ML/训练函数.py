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
