# 通用
def weight_init(m):
    classname = m.__class__.__name__
    if classname.find('Conv2d') != -1:
        torch.nn.init.normal_(m.weight.data)
        torch.nn.init.constant_(m.bias.data, 0.0)
    elif classname.find('Linear') != -1:
        torch.nn.init.normal_(m.weight)
        torch.nn.init.constant_(m.bias, 0.0)
    elif classname.find('BatchNorm2d'):
        torch.nn.init.normal_(m.weight.data, 1.0, 0.02)
        torch.nn.init.constant_(m.bias.data, 0.0)


# Xavier 均匀分布:torch.nn.init.xavier_uniform_(tensor, gain = 1), 服从均匀分布U(-a, a)， 
# 分布参数a=gain * sqrt(6 / (fan_in + fan_out)), gain的大小由激活函数的类型来决定。
# 其中fan_in是指第i层神经元的个数，fan_out是指第i + 1层神经元的个数
for m in net.modules():
     if isinstance(m, (torch.nn.Linear, torch.nn.Conv1d, torch.nn.Conv2d)):
         torch.nn.init.xavier_uniform_(m.weight)

for m in net.modules():
     if isinstance(m, torch.nn.Conv2d):
         torch.nn.init.xavier_uniform_(m.weight, gain = torch.nn.init.calculate_gain('relu'))

# Xavier 正态分布: torch.nn.init.xavier_normal_(tensor, gain = 1) 服从正态分布N(mean = 0, std)，
# 其中 std = gain * sqrt(2 / (fan_in + fan_out))
# kaiming均匀分布
# torch.nn.init.kaiming_uniform_(tensor, a=0, mode='fan_in', nonlinearity='leaky_relu')
# 服从 U(-a, a), a = sqrt(6 / (1 + b ^2) * fan_in), 其中b为激活函数的负半轴的斜率， relu是0
# model 可以是fan_in或者fan_out。fan_in 表示使正向传播时，方差一致； fan_out使反向传播时， 方差一致
# nonlinearity 可选为relu和leaky_relu， 默认是leaky_relu

# kaiming正态分布,  N～ (0,std)，其中std = sqrt(2/(1+b^2)*fan_in)
# torch.nn.init.kaiming_normal_(tensor, a=0, mode='fan_in', nonlinearity='leaky_relu')

for m in net.modules():
     if isinstance(m, torch.nn.Conv2d):
          torch.nn.kaiming_normal_(m.weight, mode = 'fan_in')

# 多层网络初始化
# 使用apply函数的方式进行初始化

# 在weight_init中通过判断模块的类型来进行不同的参数初始化定义类型
def weight_init(m):
    classname = m.__class__.__name__
    if classname.find('Conv2d') != -1:
         torch.nn.init.xavier_normal_(m.weight.data)
         torch.nn.init.constant_(m.bias.data, 0.0)
    elif classname.find('Linear') != -1:
         torch.nn.init.xavier_normal_(m.weight)
         torch.nn.init.constant_(m.bias, 0.0)

model= Model();
model.apply(weight_init)
# 这里apply函数会递归搜索网络中所有Module， 并将weight_init函数应用在这些Module上

# 权重初始化函数
def weights_init(net, init_type='normal', init_gain=0.02):
    def init_func(m):
        classname = m.__class__.__name__
        if hasattr(m, 'weight') and classname.find('Conv') != -1:
            if init_type == 'normal':
                torch.nn.init.normal_(m.weight.data, 0.0, init_gain)
            elif init_type == 'xavier':
                torch.nn.init.xavier_normal_(m.weight.data, gain=init_gain)
            elif init_type == 'kaiming':
                torch.nn.init.kaiming_normal_(m.weight.data, a=0, mode='fan_in')
            elif init_type == 'orthogonal':
                torch.nn.init.orthogonal_(m.weight.data, gain=init_gain)
            else:
                raise NotImplementedError('initialization method [%s] is not implemented' % init_type)
        elif classname.find('BatchNorm2d') != -1:
            torch.nn.init.normal_(m.weight.data, 1.0, 0.02) # 均匀分布初始化
            torch.nn.init.constant_(m.bias.data, 0.0) # 常数初始化
    print('initialize network with %s type' % init_type)
    net.apply(init_func)

