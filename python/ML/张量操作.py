# Shuffle the first dimension
# 张量扰动
tensor = tensor[torch.randperm(tensor.size(0))]  

# 张量变形
tensor = torch.reshape(tensor, shape)

# one-hot 编码， 从零开始
N = tensor.size(0)
one_hot = torch.zeros(N, num_classes).long()
one_hot.scatter_(dim=1, index=torch.unsqueeze(tensor, dim=1), src=torch.ones(N, num_classes).long())

# 判断两个张量相等
torch.allclose(tensor1, tensor2)  # float tensor
torch.equal(tensor1, tensor2)     # int tensor

# 张量扩展
# Expand tensor of shape 64*512 to shape 64*512*7*7.
torch.reshape(tensor, (64, 512, 1, 1)).expand(64, 512, 7, 7)

# 矩阵乘法
# Matrix multiplication: (m*n) * (n*p) -> (m*p).
result = torch.mm(tensor1, tensor2)

# Batch matrix multiplication: (b*m*n) * (b*n*p) -> (b*m*p).
result = torch.bmm(tensor1, tensor2)

# Element-wise multiplication.
result = tensor1 * tensor2

# 计算两组数据间欧氏距离
# X1 is of shape m*d, X2 is of shape n*d.
dist = torch.sqrt(torch.sum((X1[:,None,:] - X2) ** 2, dim=2))

# 常见卷积层操作
conv = torch.nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=True)
conv = torch.nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=1, padding=0, bias=True)

