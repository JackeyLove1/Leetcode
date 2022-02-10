import torch

# 线性回归
# data_iter
# 我们定义一个data_iter函数
# 该函数接收批量大小、特征矩阵和标签向量作为输入，生成大小为batch_size的小批量。 
# 每个小批量包含一组特征和标签。
def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))
    # 这些样本是随机读取的，没有特定的顺序
    random.shuffle(indices)
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(
            indices[i: min(i + batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]

# 定义损失函数
def squared_loss(y_hat, y):  #@save
    """均方损失"""
    return (y_hat - y.reshape(y_hat.shape)) ** 2 / 2

# SGD损失函数
# 在每一步中，使用从数据集中随机抽取的一个小批量，然后根据参数计算损失的梯度。 
# 接下来，朝着减少损失的方向更新我们的参数。 下面的函数实现小批量随机梯度下降更新。
# 该函数接受模型参数集合、学习速率和批量大小作为输入。
# 每一步更新的大小由学习速率lr决定。 因为我们计算的损失是一个批量样本的总和，
# 所以我们用批量大小（batch_size） 来规范化步长，这样步长大小就不会取决于我们对批量大小的选择。
def sgd(params, lr, batch_size):  #@save
    """小批量随机梯度下降"""
    with torch.no_grad():
        for param in params:
            # 梯度反向传播
            param -= lr * param.grad / batch_size
            # 梯度清零
            param.grad.zero_()

# 训练
lr = 0.03
num_epochs = 3
net = linreg
loss = squared_loss

for epoch in range(num_epochs):
    for X, y in data_iter(batch_size, features, labels):
        l = loss(net(X, w, b), y)  # X和y的小批量损失
        # 因为l形状是(batch_size,1)，而不是一个标量。l中的所有元素被加到一起，
        # 并以此计算关于[w,b]的梯度
        l.sum().backward()
        sgd([w, b], lr, batch_size)  # 使用参数的梯度更新参数
    with torch.no_grad():
        train_l = loss(net(features, w, b), labels)
        print(f'epoch {epoch + 1}, loss {float(train_l.mean()):f}')

# 线性回归简洁实现
