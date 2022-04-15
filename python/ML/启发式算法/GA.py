import numpy as np
import matplotlib.pylab as plt
from typing import List

"""
参数集合 - 编码 - 初始化种群 - 计算适应度 - 
选择适应度搞得染色体进行复制 - 交叉 - 
变异 - 新种群 - 判断新种群是否满足终止条件，不满足返回计算适应度步骤 - 
解码 - 输出结果
"""

# 设置随机种子,自定义种子
np.random.seed(1)


# 计算适应度，即为需要优化的函数
# 此处求区间的最大值
def fitness(x):
    return x + 16 * np.sin(5 * x) + 10 * np.cos(4 * x)


# 个体类
class individual(object):
    def __init__(self):
        self.x = 0  # 染色体编码
        self.fitness = 0  # 个体适应度

    def __eq__(self, other):
        self.x = other.x
        self.fitness = other.fitness

    def __str__(self):
        return "x:{}, y:{}".format(self.x, self.fitness)


# 初始化种群
# pop 为种群适应度存储数组，N为个体数
def initPopulation(pop: List, N: int):
    for i in range(N):
        ind = individual()  # 个体初始化
        ind.x = np.random.uniform(-10, 10)  # 在求解范围内随机采样
        ind.fitness = fitness(ind.x)  # 求解种群适应度
        pop.append(ind)  # 将个体加入采样数组


# 选择过程
def selection(N):
    # 种群中随机选择两个进行变异（此处未使用轮盘方法）
    return np.random.choice(N, 2)


# 结合/交叉过程
def crosser(parent1, parent2):
    children1, children2 = individual(), individual()  # 父母初始化
    children1.x = 0.9 * parent1.x + 0.1 * parent2.x  # 交叉0.9 ,0.1均为超参数
    children2.x = 0.9 * parent2.x + 0.1 * parent1.x
    children1.fitness = fitness(children1.x)  # 计算子代适应度
    children2.fitness = fitness(children2.x)
    return children1, children2


# 变异过程
def mutation(pop):
    # 种群中随机选择一个进行变异
    ind = np.random.choice(pop)
    # 使用赋值的方法进行随机变异
    ind.x = np.random.uniform(-10, 10)
    ind.fitness = fitness(ind.x)


# 最终执行
def iteration():
    # 种群中个体数量
    N = 40
    # 种群
    pop = []
    # 迭代次数
    iter_N = 40
    # 初始化种群
    initPopulation(pop, N)

    # 进化过程, 遍历每一代
    for it in range(iter_N):
        a, b = selection(N)  # 随机选择个体
        # 以0.65的概率进行结合，结合超参数
        if np.random.random() < 0.65:
            child1, child2 = crosser(pop[a], pop[b])
            # 将父母和子代进行比较，保留最好的两个
            new = sorted([pop[a], pop[b], child1, child2], key=lambda ind: ind.fitness, reverse=True)
            # 更新种群
            pop[a], pop[b] = new[0], new[1]
        # 以0.1的概率进行变异，变异超参数0.1
        if np.random.random() < 0.1:
            mutation(pop)
        pop.sort(key=lambda ind: ind.fitness, reverse=True)
    return pop


if __name__ == "__main__":
    pop = iteration()
    x = np.linspace(-10, 10, 1000)
    y = fitness(x)
    print(np.max(y))
    for ind in pop:
        print(ind)
