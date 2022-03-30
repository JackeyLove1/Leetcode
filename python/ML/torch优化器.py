import torch    
# Adam 
optimizer = torch.optim.SGD(model.parameters(), lr = 0.01, momentum=0.9)

# SGD 就是随机梯度下降
opt_SGD         = torch.optim.SGD(net_SGD.parameters(), lr=LR)
# momentum 动量加速,在SGD函数里指定momentum的值即可
opt_Momentum    = torch.optim.SGD(net_Momentum.parameters(), lr=LR, momentum=0.8)
# RMSprop 指定参数alpha
opt_RMSprop     = torch.optim.RMSprop(net_RMSprop.parameters(), lr=LR, alpha=0.9)
# Adam 参数betas=(0.9, 0.99)
opt_Adam        = torch.optim.Adam(net_Adam.parameters(), lr=LR, betas=(0.9, 0.99))

