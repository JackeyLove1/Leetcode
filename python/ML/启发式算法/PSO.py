import numpy as np


# 求解目标函数的最大值
def func(x):
    return x + 16 * np.sin(5 * x) + 10 * np.cos(4 * x)


# 粒子（鸟）
class particle:
    def __init__(self):
        self.pos = 0  # 粒子当前位置
        self.speed = 0
        self.pbest = 0  # 粒子最好位置
        self.fitness = 0  # 粒子适应度


class PSO:
    def __init__(self):
        self.w = 0.5  # 惯性因子
        self.c1 = 1  # 自我认知学习因子
        self.c2 = 1  # 社会认知学习因子
        self.gbest = 0  # 种群中最好的位置
        self.N = 20  # 种群中粒子的数量
        self.pop = []  # 种群ß
        self.num_iter = 100  # 迭代次数

    def fitness(self, x):  # 种群适应度，即为目标函数
        return func(x)

    # 找到全局最优解
    def g_best(self):
        for bird in self.pop:
            if bird.fitness > self.fitness(self.gbest):
                self.gbest = bird.pos

    # 初始化种群
    def initPopulation(self):
        for i in range(self.N):
            bird = particle()
            bird.pos = np.random.uniform(-10, 10)  # 随机取样位置
            bird.fitness = self.fitness(bird.pos)
            bird.pbest = bird.pos
            self.pop.append(bird)
        self.g_best()

    # 更新速度和位置
    def update(self):
        for bird in self.pop:
            speed = self.w * bird.speed + self.c1 * np.random.random() * (
                    bird.pbest - bird.pos) + self.c2 * np.random.random() \
                    * (self.gbest - bird.pos)

            # 位置更新
            pos = bird.pos + speed

            if -10 < pos < 10:  # 必须在搜索空间内
                bird.pos = pos
                bird.speed = speed
                # 更新适应度
                bird.fitness = self.fitness(bird.pos)
                # 是否更新粒子最好位置
                if bird.fitness > self.fitness(bird.pbest):
                    bird.pbest = bird.pos

    # 迭代执行
    def iteration(self):
        # 初始化种群
        self.initPopulation()
        # 迭代
        for i in range(self.num_iter):
            # 更新速度和位置
            self.update()
            # 更新种群中最好的位置
            self.g_best()


if __name__ == "__main__":
    pso = PSO()
    pso.iteration()

    best_x, best_y = 0, 0
    for ind in pso.pop:
        if ind.fitness > best_y:
            best_x, best_y = ind.pos, ind.fitness
    print("pos: {}, value:{}".format(best_x, best_y))
    x = np.linspace(-10, 10, 10000)
    y = np.max(func(x))
    print("best: ", y)

