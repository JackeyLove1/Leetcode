import numpy as np

# set random seed
np.random.seed(1)

# 初始化搜索参数
D = 10  # 变量维度
Xs = 20  # 上限
Xx = -20  # 下限

# 冷却表参数
L = 200  # 马尔可夫链长度，在温度t下迭代的次数
K = 0.998  # 衰减参数
S = 0.01  # 步长因子
T = 100  # 初始温度
YZ = 1e-7  # 容差
P = 0  # Metropolis过程中总接受点

# 随机选定初始之
PreX = np.random.uniform(size=(D, 1)) * (Xs - Xx) + Xx
PreBestX = PreX  # t-1代的全局最有X
PreX = np.random.uniform(size=(D, 1)) * (Xs - Xx) + Xx
BestX = PreX

# target function,求最小值
func = lambda x: np.sum([i ** 2 for i in x])

# 没迭代一次退火一次，直到满足迭代条件为止

deta = np.abs((func(BestX) - func(PreBestX)))  # 前后能量差
trace = []  # 记录

# 如果能量差大雨允许能量差，或者温度大于阈值
while deta > YZ and T > 0.1:
    T = K * T  # 降温
    print(T)

    for i in range(L):
        # 在此点附近选择下一个点
        NextX = PreX + S * (np.random.uniform(size=(D, 1)) * (Xs - Xx) + Xx)
        # 边界条件处理
        for j in range(D):  # 遍历每一个维度
            while NextX[j] > Xs or NextX[j] < Xx:
                NextX[j] = PreX[j] + S * (np.random.random() * (Xs - Xx) + Xx)

        # 是否是全局最优解
        if func(BestX) > func(NextX):
            # 保留上一个最优解
            PreBestX = BestX
            BestX = NextX

        # Metropolis 过程
        if func(PreX) - func(NextX) > 0:  # 后一个比前一个好
            # 接受新解
            PreX = NextX
            P = P + 1
        else:
            changer = -1 * (func(NextX) - func(PreX)) / T
            p1 = np.exp(changer)
            # 接受更差的解
            if p1 > np.random.random():
                PreX = NextX
                P = P + 1
        trace.append(func(BestX))
    deta = np.abs(func(BestX) - func(PreBestX))  # modify the energy difference

print("min point: ", BestX)
print("min value: ", func(BestX))
